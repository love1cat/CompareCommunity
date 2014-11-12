//
//  cluster_comp_base.cpp
//  CompareCommunity
//
//  Created by Yuan on 11/3/14.
//  Copyright (c) 2014 Yuan. All rights reserved.
//
#include <vector>
#include <sstream>
#include <algorithm>

#include "cluster_comp_base.h"

namespace {
  const char *DETAIL_OUTFILE = "matching_result.txt";
  const char *SIM_OUTFILE = "simi_result.txt";
  
  const char COMMENT_CHAR = '#';
  
  bool is_comment(const char *line)
  {
    // find first charactor
    while (isspace(*line)) {
      ++line;
    }
    return *line == COMMENT_CHAR;
  }
}

void ClusterCompareBase::read_file(const char *input, CommunityVector_t &comm_vec) const {
  std::ifstream infile(input);
  if (!infile) {
    throw "Cannot open input file.";
  }
  
  std::string line;
  Community_t comm;
  while (std::getline(infile, line)) {
    if (is_comment(line.c_str())) {
      continue;
    }
    std::istringstream ssline(line);
    int id;
    comm.clear();
    while (ssline >> id) {
      comm.push_back(id);
    }
    // Sort community for print later.
    std:sort(comm.begin(), comm.end());
    
    comm_vec.push_back(comm);
  }
}

bool ClusterCompareBase::on_blacklist(int id, const BlackList_t &bl) const {
  BlackList_t::const_iterator cit = bl.find(id);
  return cit != bl.end();
}

void ClusterCompareBase::add_to_blacklist(int id, BlackList_t &bl) {
  bl.insert(id);
}

void ClusterCompareBase::community_matching(const char *input1, const char *input2, Result &res) {
  CommunityVector_t comm_vec1, comm_vec2;
  read_file(input1, comm_vec1);
  read_file(input2, comm_vec2);
  assert(comm_vec1.size() == comm_vec2.size() && "Currently only consider equally sized community set.");
  
  std::cout << "Computing all similarities..." << std::endl;
  long long count = 0;
  for (int i = 0; i < comm_vec1.size(); ++i) {
    for (int j = 0; j < comm_vec2.size(); ++j) {
      if (++count % 100 == 0) {
        std::cout << "Computed " << count << " pairs." << std::endl;
      }
      double sim = compute_similarity(comm_vec1[i], comm_vec2[j]);
      q_.push(Similarity_t(std::make_pair(i, j), sim));
    }
  }
  
  std::cout << "Start matching process..." << std::endl;
  int min_size = std::min(comm_vec1.size(), comm_vec2.size());
  res.clear();
  while (!q_.empty() && res.similarities.size() < min_size) {
    Similarity_t sim_pr = q_.top();
    int id1 = sim_pr.first.first;
    int id2 = sim_pr.first.second;
    double sim = sim_pr.second;
    if (!on_blacklist(id1, blist1_) &&
        !on_blacklist(id2, blist2_)) {
      std::cout << "The pair with maximum similarity is (" << id1 << ", " << id2 << ") with similarity: " << sim << std::endl;
      res.similarities.push_back(sim_pr);
      add_to_blacklist(id1, blist1_);
      add_to_blacklist(id2, blist2_);
    }
    q_.pop();
  }
  
  std::cout << "Writing result..." << std::endl;
  write_result(res, comm_vec1, comm_vec2);
}

void ClusterCompareBase::write_community(const Community_t &comm, std::ofstream &of) const {
  for (int i = 0; i < comm.size(); ++i) {
    of << comm[i] << " ";
  }
  of << "\n";
}

void ClusterCompareBase::write_result(const Result &res, const CommunityVector_t &comm_vec1, const CommunityVector_t &comm_vec2) const{
  std::ofstream dof(DETAIL_OUTFILE, std::ios_base::trunc);
  std::ofstream sof(SIM_OUTFILE, std::ios_base::trunc);
  const std::vector<Similarity_t> &si = res.similarities;
  for (int i = 0; i < si.size(); ++i) {
    Similarity_t sim_pr = si[i];
    int id1 = sim_pr.first.first;
    int id2 = sim_pr.first.second;
    double sim = sim_pr.second;
    dof << "Match " << i << ": (" << id1 << ", " << id2 << ") with similarity: " << sim << std::endl;
    dof << "Community " << id1 << ":" << std::endl;
    write_community(comm_vec1[id1], dof);
    dof << "Community " << id2 << ":" << std::endl;
    write_community(comm_vec2[id2], dof);
    
    sof << id1 << " " << id2 << " " << sim << std::endl;
  }
}

double ClusterCompareBase::compute_similarity(const Community_t &cls1, const Community_t &cls2) const {
  assert(!cls1.empty() && !cls2.empty());
  // assume sorted
  int p1 = 0, p2 = 0;
  int res = 0;
  while (p1 < cls1.size() && p2 < cls2.size()) {
    int id1 = cls1[p1];
    int id2 = cls2[p2];
    if (id1 == id2) {
      ++res;
      ++p1, ++p2;
    } else if (id1 > id2) {
      ++p2;
    } else {
      ++p1;
    }
  }
  
  size_t max_size = std::max(cls1.size(), cls2.size());
  
  return (double)res / (double)max_size;
}











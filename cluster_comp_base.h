//
//  cluster_comp_base.h
//  CompareCommunity
//
//  Created by Yuan on 11/3/14.
//  Copyright (c) 2014 Yuan. All rights reserved.
//

#ifndef __CompareCommunity__cluster_comp_base__
#define __CompareCommunity__cluster_comp_base__

#include <queue>
#include <fstream>
#include <boost/unordered_set.hpp>

typedef std::pair<int, int> Pair_t;
typedef std::pair<Pair_t, double> Similarity_t;

struct Result {
  std::vector<Similarity_t> similarities;
  void clear() {
    similarities.clear();
  }
};

class ClusterCompareBase {
public:
  void community_matching(const char *input1, const char *input2, Result &res);
private:
  class Compare {
  public:
    bool operator()(const Similarity_t &s1, const Similarity_t &s2) const {
      return s1.second < s2.second;
    }
  };
  typedef std::vector<int> Community_t;
  typedef std::vector<Community_t> CommunityVector_t;
  
  typedef boost::unordered_set<int> BlackList_t;
  
  virtual double compute_similarity(const Community_t &cls1, const Community_t &cls2) const;
  
  void read_file(const char *input, CommunityVector_t &comm_vec) const;
  
  bool on_blacklist(int id, const BlackList_t &bl) const;
  void add_to_blacklist(int id, BlackList_t &bl);
  
  void write_result(const Result &res, const CommunityVector_t &comm_vec1, const CommunityVector_t &comm_vec2) const;
  
  void write_community(const Community_t &comm, std::ofstream &of) const;
  
  std::priority_queue<Similarity_t, std::vector<Similarity_t>, Compare> q_;
  BlackList_t blist1_, blist2_;
  
};

#endif /* defined(__CompareCommunity__cluster_comp_base__) */

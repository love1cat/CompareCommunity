//
//  main.cpp
//  CompareCommunity
//
//  Created by Yuan on 11/3/14.
//  Copyright (c) 2014 Yuan. All rights reserved.
//

#include <iostream>
#include "cluster_comp_base.h"

namespace {
  const char * INPUT1 = "test1.txt";
  const char * INPUT2 = "test2.txt";
}

int main(int argc, const char * argv[]) {
  ClusterCompareBase ccb;
  Result res;
  ccb.community_matching(INPUT1, INPUT2, res);
  
  return 0;
}

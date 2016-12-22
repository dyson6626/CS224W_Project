//
//  CS224w_graph_utils.hpp
//  CS224w_project
//
//  Created by Shen Dai on 12/7/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#ifndef CS224w_graph_utils_hpp
#define CS224w_graph_utils_hpp

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <random>

using namespace std;

unordered_map<int, vector<int> > read_graph(char* filename);

unordered_set<int> getBfsTree(unordered_map<int, vector<int> > G, unordered_set<int> seedset);


#endif /* CS224w_graph_utils_hpp */

//
//  CS224w_marginal_influence.hpp
//  CS224w_project
//
//  Created by Shen Dai on 12/8/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#ifndef CS224w_marginal_influence_hpp
#define CS224w_marginal_influence_hpp

#include <stdio.h>
#include "CS224w_graph_utils.hpp"
#include <random>
#include <cstdarg>


typedef vector<int> VI;

typedef unordered_map<int, VI> Graph;


int montecarlo_one_iter(Graph &G, unordered_set<int> S, int u, double p);


double montecarlo_marginal_influence(Graph & G, unordered_set<int>& S, int u, double p, int numIter=10000);


double deterministic_marginal_influence(Graph & G, unordered_set<int>& S, int u, double p, int numIter=10000);

double getInfluence(Graph & G, unordered_set<int>& S, double p, int numIter);


#endif /* CS224w_marginal_influence_hpp */

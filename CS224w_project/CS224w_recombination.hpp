//
//  CS224w_recombination.hpp
//  CS224w_project
//
//  Created by Shen Dai on 12/10/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#ifndef CS224w_recombination_hpp
#define CS224w_recombination_hpp

#include <stdio.h>
#include <random>
#include "CS224w_graph_utils.hpp"
#include "CS224w_marginal_influence.hpp"
#include <time.h>
#include "CS224w_CELF.hpp"



VI naiveNodeSelect(vector<topRanks> & ranks, int k);



VI Boris_recombination(Graph & G, double p, int k, int numIter, VI (*select)(vector<topRanks>&, int));

VI linearNodeSelect(vector<topRanks>& ranks, int k);


#endif /* CS224w_recombination_hpp */




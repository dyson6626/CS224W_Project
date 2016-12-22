//
//  CS224w_clustering_store_graphs.hpp
//  CS224w_project
//
//  Created by Shen Dai on 12/10/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#ifndef CS224w_clustering_store_graphs_hpp
#define CS224w_clustering_store_graphs_hpp

#include <stdio.h>
#include <random>
#include "CS224w_graph_utils.hpp"
#include "CS224w_marginal_influence.hpp"
#include <time.h>
#include "CS224w_CELF.hpp"


vector<Graph> Boris_generate_graphlist(Graph & G, double p, int numIter=10000);


topRanks Boris_CELF(Graph & G, double p, int k, int numIter=10000, bool toTime=false, bool Verbose=false);


#endif /* CS224w_clustering_store_graphs_hpp */


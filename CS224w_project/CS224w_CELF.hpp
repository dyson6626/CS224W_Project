//
//  CS224w_CELF.hpp
//  CS224w_project
//
//  Created by Shen Dai on 12/8/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#ifndef CS224w_CELF_hpp
#define CS224w_CELF_hpp

#include <stdio.h>
#include "CS224w_graph_utils.hpp"
#include "CS224w_marginal_influence.hpp"
#include <time.h>

typedef struct Influence{
    int node;
    double influence;
    size_t iter;
    Influence(int node, double influence, size_t iter):node(node), influence(influence), iter(iter){
    }
    inline bool operator < (Influence const other) const{
        return influence < other.influence;
    }
    
} Influence;


typedef struct topRanks{
    unordered_set<int> S;
    vector<int> nodes;
    vector<time_t> times;
} topRanks;


topRanks CELF(Graph & G, double p, int k, bool toTime, bool Verbose=false);


#endif /* CS224w_CELF_hpp */

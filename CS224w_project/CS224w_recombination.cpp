//
//  CS224w_recombination.cpp
//  CS224w_project
//
//  Created by Shen Dai on 12/10/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#include "CS224w_recombination.hpp"
#include "CS224w_marginal_influence.hpp"
#include "CS224w_clustering_store_graphs.hpp"
#include <iostream>
#include <queue>


VI Boris_recombination(Graph & G, double p, int k, int numIter, VI (*select)(vector<topRanks>&, int)){
    
    
    vector<topRanks> Q;
    Q.resize(numIter);
    
    
    for (int i=0; i<numIter; ++i){
        
        topRanks ranks = CELF(Boris_generate_graphlist(G, p, 1)[0], 1, k, false, false);
        Q.push_back(ranks);
    }
    
    VI res = select(Q, k);
    
    return res;
}


VI naiveNodeSelect(vector<topRanks> & ranks, int k){
    
    VI res;
    res.resize(k);
    
    unordered_map<int, int> map;
    
    auto cmp = [&map](int x, int y){return map[x]<map[y];};
    
    priority_queue<int, VI, decltype(cmp)> pq(cmp);
    
    for (auto& toprank : ranks){
        for (int node : toprank.S){
            if (map.find(node) == map.end()){
                map[node] = 1;
            }else {
                map[node] += 1;
            }
        }
    }
    
    for (auto& item : map){
        pq.push(item.first);
    }
    
    for (int i=0; i<k; ++i){
        res[i] = pq.top();
        pq.pop();
    }
    
    return res;
}


VI linearNodeSelect(vector<topRanks>& ranks, int k){
    VI res;
    res.resize(k);
    
    unordered_map<int, int> map;
    
    auto cmp = [&map](int x, int y){return map[x]<map[y];};
    
    priority_queue<int, VI, decltype(cmp)> pq(cmp);
    
    for (auto& toprank : ranks){
        int count = 5;
//        cout<<"the vector of nodes"<<endl;
        for (int node : toprank.nodes){
           
            if (map.find(node) == map.end()){
                map[node] = count;
            }else {
                map[node] += count;
            }
            --count;
        }
    }
    
    for (auto& item : map){
        pq.push(item.first);
    }
    
    for (int i=0; i<k; ++i){
        res[i] = pq.top();
        pq.pop();
    }
    
    return res;
}







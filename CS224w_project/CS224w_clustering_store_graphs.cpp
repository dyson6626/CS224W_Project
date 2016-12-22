//
//  CS224w_clustering_store_graphs.cpp
//  CS224w_project
//
//  Created by Shen Dai on 12/10/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#include "CS224w_clustering_store_graphs.hpp"
#include "CS224w_marginal_influence.hpp"
#include <iostream>


vector<Graph> Boris_generate_graphlist(Graph & G, double p, int numIter){
    vector<Graph> graphs;
    graphs.resize(numIter);
    for (int i=0; i<numIter; ++i){
        
        Graph& newG = graphs[i];
//        Graph newG;
        
        for (auto& node : G){
            VI& edges = node.second;
            for (int nbr : edges){
                if ((double)rand()/RAND_MAX <= p) newG[node.first].push_back(nbr);
            }
        }
        
        //graphs.push_back(newG);
    }
    return graphs;
}


double Boris_one_iter(Graph& Gnew, unordered_set<int>& S, int u, double p){
    return deterministic_marginal_influence(Gnew, S, u, p);
}


double Boris_nondeterministic_marginal_influence(unordered_set<int>& S, int u, double p, vector<Graph>& graphList, int numIter){
    
    double gain = 0;
    for (auto& G : graphList){
        gain += Boris_one_iter(G, S, u, p);
    }
    return gain/numIter;
}

topRanks Boris_CELF(Graph & G, double p, int k, int numIter, bool toTime, bool Verbose){
    topRanks res;
    
    vector<Influence> Q;
    Q.reserve(G.size());
    
    res.times.push_back(time(NULL));
    
    double current_influence = 0;
    double new_influence = 0;
    
    vector<Graph> graphList = Boris_generate_graphlist(G, p);
    
    for (auto& item: G){
        current_influence = Boris_nondeterministic_marginal_influence(res.S, item.first, p, graphList, numIter);
        Q.push_back(Influence(item.first, current_influence, 0));
        push_heap(Q.begin(), Q.end());
    }
    time_t t;
    while (res.S.size() < k){
        Influence top = Q.front();
        if (top.iter == res.S.size()){
            res.S.insert(top.node);
            res.nodes.push_back(top.node);
            pop_heap(Q.begin(), Q.end());
            Q.pop_back();
            t = time(NULL);
            res.times.push_back(t);
            if (toTime){
                
                cout<<difftime(t,res.times[0])<<endl;
            }
            if (Verbose)
                printf("(Node chosen, marginal influence) = (%d, %f)\n", top.node, top.influence);
            
        }else{
            new_influence = Boris_nondeterministic_marginal_influence(res.S, top.node, p, graphList, numIter);
            pop_heap(Q.begin(), Q.end());
            Q.pop_back();
            Q.push_back(Influence(top.node, new_influence, res.S.size()));
            push_heap(Q.begin(), Q.end());
        }
    }
    return res;
}



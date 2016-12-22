//
//  CS224w_CELF.cpp
//  CS224w_project
//
//  Created by Shen Dai on 12/8/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#include "CS224w_CELF.hpp"
#include "CS224w_marginal_influence.hpp"
#include <iostream>

using namespace std;

topRanks CELF(Graph & G, double p, int k, bool toTime, bool Verbose){
    topRanks res;
    double (*marginal_influence)(Graph &, unordered_set<int> &, int, double, int);
    
    marginal_influence = (p==1)?deterministic_marginal_influence:montecarlo_marginal_influence;
    
//    if (p==1) cout<<"using deterministic marginal influence"<<endl;
//    else cout<<"using montecarlo_marginal_influence"<<endl;
    
    vector<Influence> Q;
    
    res.times.push_back(time(NULL));
    
    double current_influence = 0;
    double new_influence = 0;
    for (auto item : G){
        current_influence = marginal_influence(G, res.S, item.first, p, 10000);
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
            new_influence = marginal_influence(G, res.S, top.node, p, 10000);
            pop_heap(Q.begin(), Q.end());
            Q.pop_back();
            Q.push_back(Influence(top.node, new_influence, res.S.size()));
            push_heap(Q.begin(), Q.end());
        }
    }
    return res;
}

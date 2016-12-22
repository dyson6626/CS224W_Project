//
//  CS224w_graph_utils.cpp
//  CS224w_project
//
//  Created by Shen Dai on 12/7/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#include "CS224w_graph_utils.hpp"
#include <stdio.h>
#include <fstream>
#include <queue>
#include <iostream>


typedef vector<int> VI;

unordered_map<int, vector<int> > read_graph(char* filename){
    unordered_map<int, vector<int>> map;
    //freopen(filename, "r", stdin);
    ifstream infile(filename, ifstream::in);
    int src, dst;
    while (infile>>dst>>src){
        if (map.find(src) != map.end()){
            map[src].push_back(dst);
        }else {
            vector<int> edges;
            edges.push_back(dst);
            map[src] = edges;
        }
    }
    return map;
}

unordered_set<int> getBfsTree(unordered_map<int, vector<int>>& G, unordered_set<int> seedset){
    VI infected(seedset.begin(), seedset.end());
    int cur;
    while (!infected.empty()){
        cur = infected.back();
        infected.pop_back();
        if (G.find(cur) != G.end()){
            for (int nbr : G[cur]){
                if (seedset.find(nbr)==seedset.end()){
                    seedset.insert(nbr);
                    infected.push_back(nbr);
                }
            }
        }
    }
    return seedset;
    
}


















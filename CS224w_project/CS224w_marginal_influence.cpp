
//  CS224w_marginal_influence.cpp
//  CS224w_project
//
//  Created by Shen Dai on 12/8/16.
//  Copyright © 2016 Shen Dai. All rights reserved.
//

#include "CS224w_marginal_influence.hpp"

using namespace std;



double getInfluence(Graph & G, unordered_set<int>& S, double p, int numIter){
    int influence = 0;
    for (int i=0; i<numIter; ++i){
        unordered_set<int> infected_set(S);
        VI infected_queue(S.begin(), S.end());
        while (!infected_queue.empty()){
            int cur = infected_queue.back();
            infected_queue.pop_back();
            if (G.find(cur) != G.end()){
                for (int nbr : G.at(cur)){
                    if (infected_set.find(nbr) == infected_set.end()){
                        if (((double)rand()/RAND_MAX) < p){
                            infected_queue.push_back(nbr);
                            infected_set.insert(nbr);
                        }
                    }
                }
            }
        }
        influence += infected_set.size();
    }
    return ((double)influence)/numIter;
}


int montecarlo_one_iter(Graph &G, unordered_set<int> depleted, int u, double p){
//    double lower_bound = 0;
//    double upper_bound = 1;
//    uniform_real_distribution<double> unif(lower_bound,upper_bound);
//    default_random_engine re;
    
    
    if (depleted.find(u)!=depleted.end()) return 0;
    VI infected_queue(depleted.begin(), depleted.end());
    while (!infected_queue.empty()){
        int cur = infected_queue.back();
        infected_queue.pop_back();
                
        if (G.find(cur) != G.end()){
            for (int nbr : G.at(cur)){
                if (depleted.find(nbr) == depleted.end()){
                    double prob = ((double)rand())/RAND_MAX;
                    if (prob <= p){
                        if (nbr==u) return 0;
                        depleted.insert(nbr);
                        infected_queue.push_back(nbr);
                        
                    }
                }
            }
        }
    }
    int num_infected_by_S = depleted.size();
    depleted.insert(u);
    infected_queue.clear();
    infected_queue.push_back(u);
    while (!infected_queue.empty()){
        int cur = infected_queue.back();
        infected_queue.pop_back();
        if (G.find(cur) != G.end()){
            for (int nbr : G.at(cur)){
                if (depleted.find(nbr) == depleted.end()){
                    double prob = ((double)rand())/RAND_MAX;
                    if (prob <= p){
                        depleted.insert(nbr);
                        infected_queue.push_back(nbr);
                        
                    }
                }
            }
        }
    }
    
    return depleted.size() - num_infected_by_S;
}


double montecarlo_marginal_influence(Graph & G, unordered_set<int> &S, int u, double p, int numIter){
    int total_gain = 0;
    for (int i=0; i<numIter; ++i){
        total_gain += montecarlo_one_iter(G, S, u, p);
    }
    
    return ((double) total_gain)/numIter;
}

double deterministic_marginal_influence(Graph & G, unordered_set<int> &S, int u, double p, int numIter){
    // run bfs on S
    unordered_set<int> influenced_S(S);
    VI infected(S.begin(), S.end());
    int cur;
    while (!infected.empty()){
        cur = infected.back();
        infected.pop_back();
        
        if (G.find(cur) != G.end()){
            for (int nbr : G.at(cur)){
                if (influenced_S.find(nbr)==influenced_S.end()){
                    influenced_S.insert(nbr);
                    infected.push_back(nbr);
                }
            }
        }
    }

    
    if (influenced_S.find(u) != influenced_S.end()) return 0;
    int size_influenced_S = influenced_S.size();
    
    // influenced_S becomes influenced S_u
    unordered_set<int> influenced_u;
    influenced_u.insert(u);
    
    //run bfs on u
    VI infected_u(influenced_u.begin(), influenced_u.end());
    
    while (!infected_u.empty()){
        cur = infected_u.back();
        infected_u.pop_back();
        if (G.find(cur) != G.end()){
            for (int nbr : G.at(cur)){
                if (influenced_u.find(nbr)==influenced_u.end()){
                    influenced_u.insert(nbr);
                    infected_u.push_back(nbr);
                }
            }
        }
    }

    
    for (auto e : influenced_u)
        influenced_S.insert(e);
    return double(influenced_S.size()- size_influenced_S);
}






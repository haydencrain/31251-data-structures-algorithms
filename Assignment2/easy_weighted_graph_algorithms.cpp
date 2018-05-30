#ifndef E_GRAPH_ALG
#define E_GRAPH_ALG

#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include "weighted_graph.hpp"

template <typename vertex> 
std::vector<vertex> depth_first(const weighted_graph<vertex>& g, const vertex& start_vertex) {

	std::vector<vertex> df_order;
	std::unordered_set<vertex> visited;
	std::stack<vertex> unprocessed;
	
	unprocessed.push(start_vertex);
	
	while (!unprocessed.empty()){
		
		vertex u = unprocessed.top();
		unprocessed.pop();
		if (visited.count(u) == 0){
			visited.insert(u);
			df_order.push_back(u);
			std::priority_queue<vertex> pq;
			
			for (auto n_it = g.cneighbours_begin(u); n_it != g.cneighbours_end(u); ++n_it){
				pq.push(n_it->first);
			}
			
			while (!pq.empty()){
				unprocessed.push(pq.top());
				pq.pop();
			}
		}
		
	}
	
	return df_order;
}

template <typename vertex> 
std::vector<vertex> breadth_first(const weighted_graph<vertex>& g, const vertex& start_vertex) {

	std::vector<vertex> bf_order;
	std::unordered_set<vertex> visited;
	std::queue<vertex> unprocessed;
	
	unprocessed.push(start_vertex);
	
	while (!unprocessed.empty()){
		
		vertex u = unprocessed.front();
		unprocessed.pop();
		if (visited.count(u) == 0){
			visited.insert(u);
			bf_order.push_back(u);
			std::priority_queue<vertex, std::vector<vertex>, std::greater<vertex> > pq;
			
			for (auto n_it = g.cneighbours_begin(u); n_it != g.cneighbours_end(u); ++n_it){
				pq.push(n_it->first);
			}
			
			while (!pq.empty()){
				unprocessed.push(pq.top());
				pq.pop();
			}
		}
		
	}
	
	return bf_order;
}

#endif

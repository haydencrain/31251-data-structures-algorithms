#ifndef GRAPH_ALGS
#define GRAPH_ALGS

#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <algorithm>
#include <limits>
#include "weighted_graph.hpp"
#include "easy_weighted_graph_algorithms.cpp"

//Returns true if the graph is connected, false otherwise.
template <typename vertex>
bool is_connected(const weighted_graph<vertex>& g){
	// if the graph is empty, of if a depth first traversal returns every vertex in the graph
	if (g.num_vertices() == 0 || depth_first(g, *(g.cbegin())).size() == g.num_vertices()) 
		return true;
	return false;
}

//Returns a vector of weighted graphs, where each weighted graph is a connected
//component of the input graph.
template <typename vertex>
std::vector<weighted_graph<vertex>> connected_components(const weighted_graph<vertex>& g){
	std::vector<weighted_graph<vertex> > components;
	std::unordered_set<vertex> visited;
	int index = 0;

	//While not all vertices have been visited:
	for (auto g_it = g.cbegin(); g_it != g.cend(); ++g_it) {
		// 1 Pick an unvisited vertex.
		if (visited.count(*g_it) == 0) {
			// 2 Start a traversal there.
			auto vertices = depth_first(g, *g_it);
			//3 All the vertices you can reach from there form a component,
			components.push_back(weighted_graph<vertex>());
			index = components.size() - 1;
			//record this and mark them as visisted.
			for (auto v : vertices) {
				components.at(index).add_vertex(v);
				visited.insert(v);
			}
			// rebuild each of the vertices' edges
			for (auto v : vertices) {
				for (auto n_it = g.cneighbours_begin(v); n_it != g.cneighbours_end(v); ++n_it) {
					components.at(index).add_edge(v, n_it->first, n_it->second);
				}
			}
		}
	}
	return components;
}

template <typename vertex> 
vertex min_distance(const std::map<vertex, int>& dijkstras, const std::unordered_set<vertex>& spt_set, const weighted_graph<vertex>& g) {
	vertex min_vertex;
	// set to max int value
	int min = std::numeric_limits<int>::max();
	// for each vertex
	for (auto g_it = g.cbegin(); g_it != g.cend(); ++g_it) {
		vertex v = *g_it;
		// if it is not apart of the spt_set yet, and it is less than the current distance
		if (spt_set.count(v) == 0 && dijkstras.at(v) <= min) {
			// set the vertex as the current minimum
			min = dijkstras.at(v); 
			min_vertex = v;
		}
	}
	return min_vertex;
}


//Returns a map of the vertices of the weighted graph g and their distances from
//the given starting vertex v.
template <typename vertex> 
std::map<vertex, int> dijkstras(const weighted_graph<vertex>& g, const vertex& v){
	std::map<vertex, int> dijkstras; // map of vertices and weights to be outputted
	std::unordered_set<vertex> spt_set; // shortest path tree set. this will be true if the vertex is included in the shortest path tree, or if the shortest distance from the source vertex to the vertex is finalised
	
	// if empty graph, return empty dijkstras
	if (g.num_vertices() == 0) return dijkstras;
	
	for (auto g_it = g.cbegin(); g_it != g.cend(); ++g_it) {
		// Initialise all vertex distances as infinite
		dijkstras.insert(std::pair<vertex, int>(*g_it, std::numeric_limits<int>::max()));	
	}
  // Distance of source vertex from itself is always 0
	dijkstras[v] = 0;
	
  // Find shortest path for all vertices
	for (auto g_it1 = g.cbegin(); g_it1 != g.cend(); ++g_it1) {
		// Pick the minimum distance vertex from the set of vertices not yet processed.
		vertex u = min_distance(dijkstras, spt_set, g);
		// mark the picked vertex as processed
		spt_set.insert(u);
		// update the distance value of the adjacent vertices of the picked vertex
		for (auto g_it2 = g.cbegin(); g_it2 != g.cend(); ++g_it2) {
			vertex v = *g_it2;
			// update only if it is not yet in the shortest path tree set, if there is an edge from u to the iterator vertex, and the total weight between the two is smaller than the current value stored.
			if (spt_set.count(v) == 0
				&& g.are_adjacent(u, v)
				&& dijkstras.at(u) != std::numeric_limits<int>::max()
				&& dijkstras.at(u) + g.get_edge_weight(u, v) < dijkstras.at(v)
			) {
				dijkstras[v] = dijkstras.at(u) + g.get_edge_weight(u, v);
			}
		}
	}
	
	return dijkstras;
}

//Returns a vector containing all the articulation points of the
//input weighted graph g.
template <typename vertex>
std::vector<vertex> articulation_points(const weighted_graph<vertex>& g){
	std::vector<vertex> articulation_points;
	// make a copy of the graph to test with
	weighted_graph<vertex> test_graph;
	// if empty graph, return empty articulation point vector
	if (g.num_vertices() == 0) return articulation_points;
	
	// simple, but n^2 time complexity approach:
	for (auto g_it = g.cbegin(); g_it != g.cend(); ++g_it) {
		// reset the test graph
		test_graph = g;
		vertex v = *g_it;
		// remove the vertex from the graph
		test_graph.remove_vertex(v);
		// if the graph is no longer connected
		if (!is_connected(test_graph)) {
			// the vertex is an articulation point
			articulation_points.push_back(v);
		}
	}
	return articulation_points;
}

#endif

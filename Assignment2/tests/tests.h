#define CXXTEST_HAVE_EH
#define CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <unordered_set>

#include "weighted_graph.hpp"
#include "test_helper.cpp"
#include "graph_algorithms.cpp"

class Management : public CxxTest::GlobalFixture{

public:

  bool setUpWorld(){
	std::srand(std::time(0));
	return true;
  }

  bool tearDownWorld(){
	return true;
  }
  
};

static Management management;

class Assignment1Tests : public CxxTest::TestSuite{

public:

 	void testIsConnnectedEmptyGraph(){
	 
		 weighted_graph<int> g;
	 
		 TS_ASSERT(is_connected(g));
	 
 	}
	
	void testIsConnectedConnectedGraph(){
		
		weighted_graph<int> g;
		
		auto r = (std::rand()%20) + 5;
		
		for (auto i = 0; i < r; ++i){
			g.add_vertex(i);
		}
		
		std::vector<int> vertices(g.begin(), g.end());
		
		auto min_edges = random_tree(vertices);
		
		for (auto e : min_edges){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		}
		
		auto extra_edges = random_tree(vertices);
		
		for (auto e : extra_edges){
			if (!g.are_adjacent(e.first, e.second)){
				g.add_edge(e.first, e.second, (std::rand()%10) + 1);
			}
		}
		
		TS_ASSERT(is_connected(g));
		
	}
	
	void testIsConnectedSimpleDisconnectedGraph(){
		
		weighted_graph<int> g;
		
		int r = std::rand()%20 + 2;
		
		for (int i = 0; i < r; ++i){
			g.add_vertex(i);
		}
		
		TS_ASSERT(!is_connected(g));
		
	}
	
	void testIsConnectedDisconnectedGraph(){
		
		weighted_graph<int> g;
		
		int r = std::rand()%10 + 2;
		int s = std::rand()%10 + 2;
		int t = std::rand()%10 + 2;
		
		int i = 0;
		std::vector<int> c1;
		std::vector<int> c2;
		std::vector<int> c3;
		
		for (; i < r; ++i){
			c1.push_back(i);
			g.add_vertex(i);
		}
		
		for (; i < s + r; ++i){
			c2.push_back(i);
			g.add_vertex(i);
		}
		
		for (; i < t + s + r; ++i){
			c3.push_back(i);
			g.add_vertex(i);
		}
		
		auto e1 = random_tree(c1);
		auto e2 = random_tree(c2);
		auto e3 = random_tree(c3);
		
		for (auto e : e1){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		}
		
		for (auto e : e2){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		} 
		
		for (auto e : e3){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		}
		
		TS_ASSERT(!is_connected(g));
		
	}
	
	void testConnectedComponentsEmptyGraph(){
		
		weighted_graph<int> g;
	 	TS_ASSERT_EQUALS(connected_components(g).size(), 0);
		
	}
	
	void testConnectedComponentsSimpleDisconnectedGraph(){
		
		weighted_graph<int> g;
		
		int r = std::rand()%20 + 1;
		
		for (int i = 0; i < r; ++i){
			g.add_vertex(i);
		}
		
		std::vector<bool> found(r, false);
		
		for (auto h : connected_components(g)){
			found[*h.begin()] = true;
		}
		
		TS_ASSERT(connected_components(g).size() == g.num_vertices());
		
		for (auto i = 0; i < r; ++i){
			TS_ASSERT(found[i]); //Vertex i found.
		}
		
	}
	
	void testConnectedComponentsConnectedGraph(){
		
		weighted_graph<int> g;
		
		auto r = (std::rand()%20) + 5;
		
		for (auto i = 0; i < r; ++i){
			g.add_vertex(i);
		}
		
		std::vector<int> vertices(g.begin(), g.end());
		
		auto min_edges = random_tree(vertices);
		
		for (auto e : min_edges){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		}
		
		auto extra_edges = random_tree(vertices);
		
		for (auto e : extra_edges){
			if (!g.are_adjacent(e.first, e.second)){
				g.add_edge(e.first, e.second, (std::rand()%10) + 1);
			}
		}
		
		auto computed_components = connected_components(g);
		
		TS_ASSERT_EQUALS(computed_components.size(), 1);
		auto component = computed_components[0];
		TS_ASSERT_EQUALS(component.num_vertices(), g.num_vertices());
		
		for (auto v : g) TS_ASSERT(component.has_vertex(v));
		for (auto v : component) TS_ASSERT(g.has_vertex(v));
		
		TS_ASSERT_EQUALS(component.num_edges(), g.num_edges());
		for (auto e : min_edges) TS_ASSERT(component.are_adjacent(e.first, e.second));
		
	}
	
	void testConnectedComponentsDisconnectedGraph(){
		
		weighted_graph<int> g;
		int vert_total = 0;
		
		std::vector<std::vector<int>> components;
		
		auto num_components = std::rand()%10 + 2;
		
		for (auto i = 0; i < num_components; ++i){
			
			std::vector<int> component;
			auto r = std::rand()%5 + 2;
			for (auto j = vert_total; j < vert_total + r; ++j){
				component.push_back(j);
			}
			vert_total += component.size();
			components.push_back(component);
			
		}
		
		std::vector<std::vector<std::pair<int, int>>> edges;
		for (auto i = 0; i < num_components; ++i){

			std::vector<std::pair<int, int>> component_edges = random_tree(components[i]);
			edges.push_back(component_edges);
			
		}
		
		for (auto c : components){
			for (auto v : c){
				g.add_vertex(v);
			}
		}
		
		for (auto c_e : edges){
			for (auto e : c_e){
				g.add_edge(e.first, e.second, std::rand()%5 + 1);
			}
		}
		
		auto computed_components = connected_components(g);
		
		for (auto h : computed_components){
			auto source_component = component_index(h, components);
			for (auto v : components[source_component]){
				TS_ASSERT(h.has_vertex(v));
			}
			
			TS_ASSERT_EQUALS(h.num_vertices(), components[source_component].size());
			
			for (auto e : edges[source_component]){
				TS_ASSERT(h.are_adjacent(e.first, e.second));
			}
			
			TS_ASSERT_EQUALS(h.num_edges(), edges[source_component].size());
			
		}
		
	}
	
	void testDijkstrasEmptyGraph(){
		
		weighted_graph<int> g;
		auto distances = dijkstras(g, 0); //The 0 shouldn't really do anything here, it's just standing in for the parameter.
		TS_ASSERT(distances.empty());
		
	}
	
	void testDijkstras(){
		
		weighted_graph<int> g;
		
		auto r = (std::rand()%20) + 5;
		
		for (auto i = 0; i < r; ++i){
			g.add_vertex(i);
		}
		
		std::vector<int> vertices(g.begin(), g.end());
		
		auto min_edges = random_tree(vertices);
		
		for (auto e : min_edges){
			g.add_edge(e.first, e.second, (std::rand()%10) + 1);
		}
		
		auto shortest_path_tree_weight = g.total_weight();
		
		auto start_vertex = vertices[std::rand()%vertices.size()];
		
		auto actual_distances = compute_tree_distances(g, start_vertex);
				
		auto extra_edges = random_tree(vertices);
		
		for (auto e : extra_edges){
			if (!g.are_adjacent(e.first, e.second)){
				g.add_edge(e.first, e.second, (std::rand()%10) + shortest_path_tree_weight + 1);
			}
		}
		
		auto computed_shortest_paths = dijkstras(g, start_vertex);
		
		TS_ASSERT_EQUALS(actual_distances, computed_shortest_paths);
		
		for (auto p : actual_distances){
			TS_ASSERT_EQUALS(computed_shortest_paths[p.first], p.second);
		}
		
	}
	
	void testArticulationPointsEmptyGraph(){
		
		weighted_graph<int> g;
		
		auto points = articulation_points(g);
		
		TS_ASSERT(points.empty());
	}
	
	void testArticulationPoints(){
		
		weighted_graph<int> g;
		auto vert_total = 0;
		
		std::vector<std::vector<int>> components;
		
		auto num_components = std::rand()%10 + 2;	
		for (auto i = 0; i < num_components; ++i){
			
			std::vector<int> component;
			auto r = std::rand()%5 + 3;
			for (auto j = vert_total; j < vert_total + r; ++j){
				component.push_back(j);
			}
			vert_total += component.size();
			components.push_back(component);
			
		}
		
		for (auto c : components){
			for (auto v : c) {
				g.add_vertex(v);
			}
			
			for (int i = 0; i < c.size(); ++i) g.add_edge(c[i], c[(i+1)%c.size()], std::rand()%10 + 1);
			auto extra_edges = random_tree(c);
			for (auto e : extra_edges){
				if (!g.are_adjacent(e.first, e.second)) g.add_edge(e.first, e.second, std::rand()%10 + 1);
			}
		}
		

		auto block_cut_tree = random_block_cut_tree(components);
		std::unordered_set<int> cuts;

		for (auto v : block_cut_tree){
			if (v.isCut){
				g.add_vertex(vert_total);
				cuts.insert(vert_total);
				std::vector<int> connections;
				
				for (auto n = block_cut_tree.neighbours_begin(v); n != block_cut_tree.neighbours_end(v); ++n){
					auto component = n->first.v;
					auto rand1 = std::rand()%component.size();
					auto rand2 = rand1;
					while (rand2 == rand1) rand2 = std::rand()%component.size();
					
					connections.push_back(component[rand1]);
					connections.push_back(component[rand2]);
				}
				
				for (auto u : connections) g.add_edge(u, vert_total, std::rand()%10 + 1);
				
				++vert_total;
			}
		}
		
		auto computed_articulation_points = articulation_points(g);

		TS_ASSERT_EQUALS(computed_articulation_points.size(), cuts.size());
		for (auto v : computed_articulation_points){
			TS_ASSERT(cuts.count(v) > 0)
		}
		
		for (auto v : cuts){
			bool articulation_point_found = false;
			for (auto u : computed_articulation_points){
				if (u == v) articulation_point_found = true;
			}
			TS_ASSERT(articulation_point_found);
		}
	}

};


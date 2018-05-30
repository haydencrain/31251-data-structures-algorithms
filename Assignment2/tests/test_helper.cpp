#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cstdlib>

#include "weighted_graph.hpp"
#include "graph_algorithms.cpp"

template <typename vertex>
std::vector<std::pair<vertex, vertex> > random_tree(const std::vector<vertex>& vertices){

	std::vector<std::pair<vertex, vertex> > tree_edges;
	if (!vertices.empty()){
		std::vector<vertex> connected;
		std::vector<vertex> unconnected;
		connected.push_back(vertices[0]);
	
		for (int i = 1; i < vertices.size(); ++i) unconnected.push_back(vertices[i]);
	
		while (connected.size() < vertices.size()){
	
			int index1 = std::rand()%connected.size();
			int index2 = std::rand()%unconnected.size();
			vertex u = connected[index1];
			vertex v = unconnected[index2];
			tree_edges.push_back({u,v});
			unconnected.erase(unconnected.begin() + index2);
			connected.push_back(v);
	
		}
	}
	return tree_edges;

}

template <typename vertex>
unsigned component_index(const weighted_graph<vertex>& graph, const std::vector<std::vector<int>>& components){

	for (int i = 0; i < components.size(); ++i){
		if (graph.has_vertex(*components[i].begin())){
			return i;
		}
	}
	
	return -1;

}

template <typename vertex>
std::map<vertex, int> compute_tree_distances(const weighted_graph<vertex>& t, const vertex& start_vertex){

	std::map<vertex, int> distances;
	
	distances[start_vertex] = 0;
	auto bfs_order = breadth_first(t, start_vertex);
	
	auto parent = bfs_order.begin();
	auto child = bfs_order.begin();
	++child;
	
	while (child != bfs_order.end()){
		if (t.are_adjacent(*child, *parent)){ 
			distances[*child] = distances[*parent] + t.get_edge_weight(*child, *parent);
			++child;
		}
		else {
			++parent;
		}
	}
	
	return distances;

}

template <typename vertex_t>
struct bc_vertex{
	vertex_t v;
	bool isCut;
	unsigned _id;
	
	bc_vertex(vertex_t vertex, bool is_cut, unsigned id) : v(vertex), isCut(is_cut), _id(id){}
	
	inline bool operator==(const bc_vertex<vertex_t>& other) const {
	    return other.v == v && _id == other._id;
    }
};

namespace std {
    template <typename vertex>
    struct hash<bc_vertex<vertex>> {
        inline size_t operator()(const bc_vertex<vertex>& x) const {
            return x.v.size() + 1;
        }
    };
}

template<typename vertex>
weighted_graph<bc_vertex<vertex>> random_block_cut_tree(const std::vector<vertex>& components){

	weighted_graph<bc_vertex<vertex>> bc_tree;
	std::vector<bc_vertex<vertex>> cut_vertices;
	std::vector<bc_vertex<vertex>> block_vertices;
	
	size_t count = 0;
	size_t cut_vertex_count = 0;

	while (count < components.size()){

		auto next = bc_vertex<vertex>(components[count], false, count);
		bc_tree.add_vertex(next);			
		++count;	

		if (block_vertices.size() > 0){

			if (std::rand()%2 && cut_vertex_count > 0){
				//use existing cut vertex
				bc_tree.add_edge(cut_vertices[std::rand()%cut_vertices.size()], next, 1);
			}
			else {
				//add new cut vertex
				auto cut_vertex = bc_vertex<vertex>(vertex(), true, cut_vertex_count);
				bc_tree.add_vertex(cut_vertex);
				bc_tree.add_edge(cut_vertex, next, 1);
				cut_vertices.push_back(cut_vertex);
				++cut_vertex_count;
				bc_tree.add_edge(cut_vertex, block_vertices[std::rand()%block_vertices.size()], 1);
				
			}

		}
		block_vertices.push_back(next);

	}
	
	return bc_tree;

}

#include <iostream>
#include <vector>
#include "weighted_graph.hpp"

int main(){
	weighted_graph<char> g;
	g.add_vertex('a');
	g.add_vertex('b');
	g.add_vertex('c');
	g.add_vertex('d');
	g.add_vertex('e');
		
	g.add_edge('a', 'b', 1);
	g.add_edge('a', 'b', 6);
	g.add_edge('a', 'b', 1);
	g.add_edge('a', 'e', 10);
	g.add_edge('b', 'c', 2);
	g.add_edge('c', 'd', 3);
	g.add_edge('d', 'e', 4);
	g.add_edge('d', 'f', 4);
	g.print();
	std::cout << std::endl;
	weighted_graph<char> mst = g.mst();
	mst.print();
		
	for (auto u : g.get_vertices()){

			for (auto n = g.neighbours_begin(u); n != g.neighbours_end(u); ++n){
				std::cout << (n->first) << ":" << (n->second) << " ";
			}
		}
}



#include <iostream>
#include <vector>
#include "weighted_graph.hpp"

int main(){
	weighted_graph<int> g;
	int r = 5;
	for (int i = 0; i < r; ++i)
		g.add_vertex(i);
	std::vector<int> vertices = g.get_vertices();
	g.add_edge(0, 1, 1);
	g.add_edge(1, 2, 2);
	g.add_edge(2, 3, 3);
	g.add_edge(3, 4, 4);
	g.remove_vertex(0);
	g.add_vertex(0);
	g.add_edge(0, 4, 5);
	g.print();
}



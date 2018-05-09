template <typename vertex>	
weighted_graph<vertex> kruskal() {
	weighted_graph<vertex> mst_graph;
	disjoint_set ds;
	std::vector<std::pair<int, std::pair<int, int> > edges; 
		
	for (auto v : vertices) {
			mst_graph.add_vertex(v);
	}
	for (unsigned i = 0; i < adj_matrix.size(); i++) {
			for (unsigned j = i; j < adj_matrix.size(); j++) {
					if (adj_matrix[i][j] > 0) {
							edge e;
							e.u_index = i;
							e.v_index = j;
							e.weight = adj_matrix[i][j];
							edges.push_back(e);
					}
			}
	}
	
	// sorting algorithm, which iterates through the graph
	sort_edges(edges);
		
	int edges_count = num_edges();
	ds.make_set(edges_count);
		
	while (mst_graph.num_edges() != edges_count - 1) {
		edge next_edge = edges.back();
		edges.pop_back();
			
		int x = ds.find(next_edge.u_index);
		int y = ds.find(next_edge.v_index);
			
		if (x != y) {
			mst_graph.add_edge(
				vertices[next_edge.u_index], 
				vertices[next_edge.v_index], 
				next_edge.weight
			);
		}
	}
	return mst_graph;
}

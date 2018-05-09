struct edge {
		int u_index, v_index, weight;
	};
	
	void sort_edges(std::vector<std::pair<int, std::pair<int, int> > >&);
	
	class disjoint_set {
	private:
		std::unordered_map<int, int> parent;
		
	public:
		void make_set(int); 
		int find(int);
		void make_union(int, int);
	};

template <typename vertex>	void weighted_graph<vertex>::disjoint_set::make_set(int size) {
		for (int i = 0; i < size; i++) {
				parent[i] = i;
		}
}

template <typename vertex>	int weighted_graph<vertex>::disjoint_set::find(int k) {
		if (parent[k] == k)
				return k;
		return find(parent[k]);
}

template <typename vertex>	void weighted_graph<vertex>::disjoint_set::make_union(int u, int v) {
		int x = find(u);
		int y = find(v);
		parent[x] = y;
}

template <typename vertex> void weighted_graph<vertex>::sort_edges(std::vector<std::pair<int, std::pair<int, int> >& edges) {
		int max_index;    
		for(unsigned int i = 0; i<edges.size()-1;i++){
   			max_index = i;
				for(unsigned int j = i+1; j<edges.size();j++)
						if(edges[j].weight > edges[max_index].weight)
								max_index = j;
        // swap values
        if( max_index != i ){
					edge temp = edges[i];
					edges[i] = edges[max_index];
					edges[max_index] = temp;
				}
    }    
}

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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#define INT_MAX 2147483647

//A large selection of data structures from the standard
//library. You need not feel compelled to use them all,
//but as you can't add any, they're all here just in case.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>

template <typename vertex>
class weighted_graph {

private:
	std::vector<std::vector<int> > adj_matrix;
	std::vector<vertex> vertices;
	int edges_count;
	int weight_total;
	
	int get_index(const vertex&) const;
	bool index_are_valid(const int&, const int&) const;
	int get_min_key(std::vector<int>, std::vector<bool>) const;
	//The graph_iterator class provides an iterator
	//over the vertices of the graph.
	//This is one of the harder parts, so if you're
	//not too comfortable with C++ leave this for last.
	//If you are, there are many ways of doing this,
	//as long as it passes the tests, it's okay.
	class graph_iterator {
		
	private:
		
	//You may need data members here.
				
	public:
		graph_iterator(const weighted_graph &);
		graph_iterator(const weighted_graph &, size_t);
		~graph_iterator();
		graph_iterator operator=(const graph_iterator&);
		bool operator==(const graph_iterator&) const;
		bool operator!=(const graph_iterator&) const;
		graph_iterator operator++();
		graph_iterator operator++(int);
		const vertex operator*();
		const vertex* operator->();
	};
	
	//The neighbour_iterator class provides an iterator
	//over the neighbours of a given vertex. This is
	//probably harder (conceptually) than the graph_iterator.
	//Unless you know how iterators work.
	class neighbour_iterator {
			
		private:
		
		//You may need data members here.
				
		public:
			neighbour_iterator(const neighbour_iterator&);
			neighbour_iterator(const weighted_graph &, const vertex&);
			neighbour_iterator(const weighted_graph &, const vertex&, size_t);
			~neighbour_iterator();
			neighbour_iterator operator=(const neighbour_iterator& it);
			bool operator==(const neighbour_iterator&) const;
			bool operator!=(const neighbour_iterator&) const;
			neighbour_iterator operator++();
			neighbour_iterator operator++(int);			
			const std::pair<vertex, int> operator*();
			const std::pair<const vertex, int>* operator->();
	};
	
	public:
	
	void print() const;
	
	weighted_graph(); //A constructor for weighted_graph. It should start empty.
	~weighted_graph(); //A destructor. Depending on how you do things, this may
					   //not be necessary.
	
	bool are_adjacent(const vertex&, const vertex&) const; //Returns true if the two vertices are
														   //adjacent, false otherwise.
	bool has_vertex(const vertex&) const; //Returns true if the passed in vertex is 
										  //a vertex of the graph, false otherwise.
	
	void add_vertex(const vertex&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex&, const vertex&, const int&); //Adds an edge between the two vertices
															 //with the given weight (as an int).
	
	void remove_vertex(const vertex&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex&, const vertex&); //Removes the edge between the two vertices, if it exists.
	void set_edge_weight(const vertex&, const vertex&, const int&); //Changes the edge weight between the two
																	//vertices to the new weight (the int).
	
	int get_edge_weight(const vertex&, const vertex&) const; //Returns the weight on the edge between the two vertices.
	int degree(const vertex&) const; //Returns the degree of the vertex. (e.g. the number of edges it has)
	int weighted_degree(const vertex&); //Returns the sum of the weights on all the edges incident to the vertex.
	int num_vertices() const; //Returns the total number of vertices in the graph.
	int num_edges() const; //Returns the total number of edges in the graph (just the count, not the weight).
	int total_weight(); //Returns the sum of all the edge weights in the graph.
	
	std::vector<vertex> get_vertices(); //Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex&); //Returns a vector containing the neighbours of the given vertex.
	
	graph_iterator begin(); //Returns a graph_iterator pointing to the start of the vertex set.
	graph_iterator end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.
	
	neighbour_iterator neighbours_begin(const vertex&); //Returns a neighbour_iterator pointing to the start
														//of the neighbour set for the given vertex.
	neighbour_iterator neighbours_end(const vertex&); //Returns a neighbour_iterator pointing to one-past-the-end
													  //of the neighbour set for the given vertex.

	std::vector<vertex> depth_first(const vertex&); //Returns the vertices of the graph in the order they
													//are visited in by a depth-first traversal starting at
													//the given vertex.
	std::vector<vertex> breadth_first(const vertex&); //Returns the vertices of the graph in the order they
													  //are visisted in by a breadth-first traversal starting
													  //at the given vertex.
	
	weighted_graph<vertex> mst(); //Returns a minimum spanning tree of the graph.
	
	
	
};

//Define all your methods down here (or move them up into the header, but be careful you don't double up).
//Although these are just the same names copied from above, you may find a few more clues in the full
//method headers. Note also that C++ is sensitive to the order you declare and define things in - you
//have to have it available before you use it.


/****************************************************************************************
																		GRAPH ITERATOR
****************************************************************************************/

template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g) {
	
}

template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g, size_t start_pos) {
		
}

template <typename vertex> weighted_graph<vertex>::graph_iterator::~graph_iterator() {
		
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator=(const graph_iterator& it) { 
		auto g = graph_iterator(weighted_graph<vertex>()); 
		return g; 
}

template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator==(const graph_iterator& it) const { 
		return false; 
}

template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator!=(const graph_iterator& it) const { 
		return false; 
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++() { 
		auto g = graph_iterator(weighted_graph<vertex>()); 
		return g; 
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++(int) { 
		auto g = graph_iterator(weighted_graph<vertex>()); 
		return g; 
}

template <typename vertex> const vertex weighted_graph<vertex>::graph_iterator::operator*() { 
		auto v = vertex(); return v; 
}

template <typename vertex> const vertex* weighted_graph<vertex>::graph_iterator::operator->() { 
		return nullptr; 
}


/****************************************************************************************
																		NEIGHBOUR ITERATOR
****************************************************************************************/

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u) {
		
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u, size_t start_pos) {
		
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::~neighbour_iterator() {
		
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator=(const neighbour_iterator& it) { 
		auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
		return n; 
}

template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator==(const neighbour_iterator& it) const { 
		return false; 
}

template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator!=(const neighbour_iterator& it) const { 
		return false; 
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++() { 
		auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
		return n; 
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++(int) { 
		auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
		return n; 
}

template <typename vertex> const std::pair<vertex, int> weighted_graph<vertex>::neighbour_iterator::operator*() { 
		auto p = std::pair<vertex,int>(); 
		return p; 
}

template <typename vertex> const std::pair<const vertex, int>* weighted_graph<vertex>::neighbour_iterator::operator->() { 
		return nullptr; 
}

template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::begin() {
	return graph_iterator(weighted_graph<vertex>());
}

template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::end() {
	return graph_iterator(weighted_graph<vertex>());
}
	
template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_begin(const vertex& u) {
	return neighbour_iterator(*this, vertex());
}

template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_end(const vertex& u) {
	return neighbour_iterator(weighted_graph<vertex>(), vertex());
}

/****************************************************************************************
																		WEIGHTED GRAPH
****************************************************************************************/


// DELETE AFTER LOL
template <typename vertex> void weighted_graph<vertex>::print() const {
	std::cout << "    ";
	for (auto v : vertices)	{
		std::cout << v << "  ";
	}
	std::cout << "\n   ";
	for (auto v : vertices)	{
		std::cout << "---";
	}
	std::cout << "\n";
	for (unsigned i = 0; i < num_vertices(); i++) {
		std::cout << vertices[i] << " | ";
		for (unsigned j = 0; j < num_vertices(); j++) {
			std::cout << adj_matrix[i][j] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

/******************************
 			 Private Methods
*******************************/

template <typename vertex> int weighted_graph<vertex>::get_index(const vertex& u) const {
	// for each vertex in vertices
	for (unsigned i = 0; i < vertices.size(); i++) { 
		// if is equal to the vertex we are looking for
		if (vertices[i] == u)
			// vertex has been found, and return the index of the vertex position
			return i;
	}
	// else return "vertex does not exist" flag
	return -1;
}

template <typename vertex> bool weighted_graph<vertex>::index_are_valid(const int& u, const int& v) const {
	// the two indexes must be greater than or equal to zero, and not equal each other.
	return (u >= 0) && (v >= 0) && (u != v);
}

/******************************
 			 Public Methods
*******************************/

template <typename vertex> weighted_graph<vertex>::weighted_graph(){
	// reset edges and weight counts
	edges_count = 0;
	weight_total = 0;
}

template <typename vertex> weighted_graph<vertex>::~weighted_graph(){ 
}

template <typename vertex> bool weighted_graph<vertex>::has_vertex(const vertex& u) const {
	// for each vertex in vertices
	for (vertex v : vertices) {
		// if it is equal to the vertex we are looking for
		if (v == u)
			// return true, to signifiy it has been found
			return true;
	}
	// else return false, to signify it has not been found
	return false;
}

	
template <typename vertex> bool weighted_graph<vertex>::are_adjacent(const vertex& u, const vertex& v) const {
	// if vertices are valid, return whether or not it contains an edge, else return false
	return (has_vertex(u) && has_vertex(v))
		? adj_matrix[get_index(u)][get_index(v)] > 0
		: false;
}

template <typename vertex> void weighted_graph<vertex>::add_vertex(const vertex& v) {
	// if vertex does not exist
	if(!has_vertex(v)) {
		// add new vertex to vertices list
		vertices.push_back(v);
		// add a new 0 value to the end of each row
		for (auto& row : adj_matrix){
			row.push_back(0);
		}	
		// create a new vector row with default 0 values, and add it to the graph
		adj_matrix.push_back(std::vector<int>(vertices.size(), 0));
	}
}

template <typename vertex> void weighted_graph<vertex>::add_edge(const vertex& u, const vertex& v, const int& weight) {
	// get the indexes of the two vertices
	int u_pos = get_index(u),
			v_pos = get_index(v);
	// if indexes are valid, and an edge does not exist, add an edge
	if(index_are_valid(u_pos, v_pos) && adj_matrix[u_pos][v_pos] == 0 && weight > 0) { 
		// set the weight at the coordinates that correspond to the index
		adj_matrix[u_pos][v_pos] = adj_matrix[v_pos][u_pos] = weight;
		// increment edge count and weight total
		edges_count++;
		weight_total += weight;
	}
}
	
template <typename vertex> void weighted_graph<vertex>::remove_vertex(const vertex& u) {
	// get index of vertex
	int u_pos = get_index(u);
	// if index is valid
	if (u_pos >= 0) {
		// remove edges and edge weights from edge and weight count variables
		for (unsigned i = 0; i < adj_matrix[u_pos].size(); i++) {
			if (adj_matrix[u_pos][i] > 0) edges_count--;
			weight_total -= adj_matrix[u_pos][i];
		}
		// remove vertex from vertex list
		vertices.erase(vertices.begin() + u_pos);
		// remove vertex row from adj_matrix
		adj_matrix.erase(adj_matrix.begin() + u_pos);
		// remove corresponding vertex values from each row
		for (unsigned i = 0; i < adj_matrix.size(); i++) {
			adj_matrix[i].erase(adj_matrix[i].begin() + u_pos);
		}
	}
}


template <typename vertex> void weighted_graph<vertex>::remove_edge(const vertex& u, const vertex& v) {
	// get indexes of the vertices
	int u_pos = get_index(u),
			v_pos = get_index(v);
	if(index_are_valid(u_pos, v_pos)) { 
		// decrease edge count and weight total
		edges_count--;
		weight_total -= adj_matrix[u_pos][v_pos];
		// set weights correpsonding to the two indexes to 0
		adj_matrix[u_pos][v_pos] = adj_matrix[v_pos][u_pos] = 0;
		
	}
}

template <typename vertex> void weighted_graph<vertex>::set_edge_weight(const vertex& u, const vertex& v, const int& weight) {
	// get indexes of the vertices
	int u_pos = get_index(u),
			v_pos = get_index(v);
	// if there isn't an edge already, we can't set the edge weight because it doesn't exist
	if(index_are_valid(u_pos, v_pos) && adj_matrix[u_pos][v_pos] > 0 && weight > 0) { 
		// the new weight total is equal to the difference between the new weight and old weight
		weight_total += weight - adj_matrix[u_pos][v_pos];
		// set the new weight to the coordinates representing the edge
		adj_matrix[u_pos][v_pos] = adj_matrix[v_pos][u_pos] = weight;
	}
}

template <typename vertex> int weighted_graph<vertex>::get_edge_weight(const vertex& u, const vertex& v) const {
	// if vertices are valid, return the weight, otherwise return 0
	return (has_vertex(u) && has_vertex(v)) 
		? adj_matrix[get_index(u)][get_index(v)] 
		: 0; 
}

template <typename vertex> int weighted_graph<vertex>::degree(const vertex& u) const {
	int degree = 0;
	int u_pos = get_index(u);
	// if index is valid
	if (u_pos >= 0) {
		for (unsigned i = 0; i < adj_matrix[u_pos].size(); i++) {
			// if the weight is greater than zero, increment degree by 1, otherwise increment by 0
			degree += adj_matrix[u_pos][i] > 0 ? 1 : 0;
		}
	}
	return degree;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	int weighted_degree = 0;
	int u_pos = get_index(u);
	// if index is valid
	if (u_pos >= 0) {
		for (unsigned i = 0; i < adj_matrix[u_pos].size(); i++) {
			// incrememnt the weighted_degree by the weight at the coordinate position
			weighted_degree += adj_matrix[u_pos][i];
		}
	}
	return weighted_degree;
}

template <typename vertex> int weighted_graph<vertex>::num_vertices() const {
	return vertices.size(); // number of vertices is the size of the vertices array
} 

template <typename vertex> int weighted_graph<vertex>::num_edges() const {
	return edges_count;
}

template <typename vertex> int weighted_graph<vertex>::total_weight() {
	return weight_total;
}
	
template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_vertices() {
	return vertices;
}

template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_neighbours(const vertex& u) {
	std::vector<vertex> neighbours;
	int u_pos = get_index(u);
	// if index is valid
	if (u_pos >= 0) {
		for (unsigned i = 0; i < adj_matrix[u_pos].size(); i++) {
			// if the coordinate position contains an edge
			if (adj_matrix[u_pos][i] > 0) 
				// add it to the neigbours list
				neighbours.push_back(vertices[i]);
		}
	}
	return neighbours;
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::depth_first(const vertex& start_vertex){
	bool visited[vertices.size()];
	std::stack<vertex> unprocessed;
	std::vector<vertex> ordered;
	// if the index of the start_vertex is valid
	if (get_index(start_vertex) >= 0) {
		// set all index values to represent that they have not been visited yet 
		for (unsigned i = 0; i < vertices.size(); i++){
			visited[i] = false;
		}
		// push the start_vertex to the unprocessed vertices stack
		unprocessed.push(start_vertex);
		// while there is still values in the unprocessed stack
		while (!unprocessed.empty()){
			// get the index of the top vertex and remove it from the stack	
			int index = get_index(unprocessed.top());
			unprocessed.pop();
			// if it hasn't been visted yet
			if (!visited[index]){
				// set it to visited
				visited[index] = true;
				// add the vertex to the ordered list
				ordered.push_back(vertices[index]);
				for (unsigned i = vertices.size(); i != 0; i--){
					// if the vertex contains a neighbour
					if (adj_matrix[index][i-1] > 0){
						// add the neighbour to the unprocessed stack
						unprocessed.push(vertices[i-1]);
					}
				}
			}
		}
	}
	return ordered;
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::breadth_first(const vertex& start_vertex){
	bool visited[vertices.size()];
	std::queue<vertex> unprocessed;
	std::vector<vertex> ordered;
	// if the index of the start_vertex is valid
	if (get_index(start_vertex) >= 0) {
		// set all index values to represent that they have not been visited yet 
		for (unsigned i = 0; i < vertices.size(); i++){
			visited[i] = false;
		}
		// add the start_vertex to the unprocessed queue
		unprocessed.push(start_vertex);
		// while there is still values in the unprocessed stack
		while (!unprocessed.empty()){
			// get the index of the vertex at the front of the queue and remove it
			int index = get_index(unprocessed.front());
			unprocessed.pop();
			// if it hasn't been visited yet
			if (!visited[index]){
				// set it to visited
				visited[index] = true;
				// add the vertex to the ordered list
				ordered.push_back(vertices[index]);
				for (unsigned i = 0; i < vertices.size(); i++){
					// if the vertex contains a neighbour
					if (adj_matrix[index][i] > 0){
						// add the neighbour to the end of the unprocessed queue.
						unprocessed.push(vertices[i]);
					}
				}
			}
		}
	}
	return ordered;
}
	
template <typename vertex>	weighted_graph<vertex> weighted_graph<vertex>::mst() {
	weighted_graph<vertex> mst_graph;
	std::vector<int> parent(vertices.size());
	std::vector<int> key(vertices.size(), INT_MAX);
	std::vector<bool> mst_set(vertices.size(), false);
	
	key[0] = 0;
	parent[0] = -1;
	
	for (unsigned count = 0; count < vertices.size()-1; count++) {
		int i = get_min_key(key, mst_set);
		
		mst_set[i] = true;
		
		for(unsigned j = 0; j < vertices.size(); j++) {
			if (adj_matrix[i][j] && !mst_set[j] && adj_matrix[i][j] < key[j]) {
				parent[j] = i;
				key[j] = adj_matrix[i][j];
			}
		}
	}
	
	for (unsigned i = 0; i < vertices.size(); i++) {
		mst_graph.add_vertex(vertices[i]);
	}
	
	for (unsigned i = 0; i < vertices.size(); ++i) {
		mst_graph.add_edge(
			vertices[parent[i]],
			vertices[i],
			adj_matrix[i][parent[i]]
		);
	}
	
	return mst_graph;
}

template <typename vertex> int weighted_graph<vertex>::get_min_key(std::vector<int> key, std::vector<bool> mst_set) const {
	int min = INT_MAX,
			min_index;
	
	for (unsigned i = 0; i < vertices.size(); i++) {
		if (!mst_set[i] && key[i] < min) {
			min = key[i];
			min_index = i;
		}
	}
	return min_index;
}

#endif

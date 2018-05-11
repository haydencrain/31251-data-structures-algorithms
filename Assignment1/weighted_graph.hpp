#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

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
#include <limits>

template <typename vertex>
class weighted_graph {

private:
	std::vector<std::vector<int> > adj_matrix; // stores the adjacency matrix for the graph
	std::vector<vertex> vertices; // stores the vertices of the graph
	int edges_count; // stores the total number of edges within the graph
	int weight_total; // stores the total weight of the graph
	
	int get_index(const vertex&) const; // gets the vertex's index within the adjacency matrix
	bool index_are_valid(const int&, const int&) const; // checks to see if the two chosen indexes are valid
	int get_min_key(std::vector<int>, std::vector<bool>) const; // finds the next lowest weight to be included in the mst	
	
	class graph_iterator {
	private:
		weighted_graph<vertex> owner; // the owner of the iterator
		int position; // the current iterator position
				
	public:
		graph_iterator(const weighted_graph &); // constructor
		graph_iterator(const weighted_graph &, size_t); // constructor 
		~graph_iterator(); // destructor
		graph_iterator operator=(const graph_iterator&); // sets LHS = RHS
		bool operator==(const graph_iterator&) const; // checks if two iterators are equal
		bool operator!=(const graph_iterator&) const; // checks if two iterators are not equal 
		graph_iterator operator++(); // increments the iterator in the grpah for any prefix increments
		graph_iterator operator++(int); // increments the iterator in the grpah for any postfix increments
		const vertex operator*(); // returns the value of the vertex at the current position
		const vertex* operator->(); // returns a pointer to the vertex at the current position
	};
	
	class neighbour_iterator {	
	private:
		weighted_graph<vertex> owner; // the owner of the neighbour iterator
		int row_index; // the index within the adjacency matrix that we will be iterating through
		int position; // the current iterator position
		bool is_valid_neighbour(int) const; // determines whether the current position is a neighbour of the vertex
		int get_next(int); // gets the next neighbour

	public:
		neighbour_iterator(const weighted_graph &, const vertex&); // constructor
		neighbour_iterator(const weighted_graph &, const vertex&, size_t); // constructor
		~neighbour_iterator(); // destructor
		neighbour_iterator operator=(const neighbour_iterator& it); // sets LHS = RHS
		bool operator==(const neighbour_iterator&) const; // checks if the two iterators are equal
		bool operator!=(const neighbour_iterator&) const; // checks if the two iterators are not equal
		neighbour_iterator operator++(); // increments throughout the neighbours of the vertex, pre-incrememntation
		neighbour_iterator operator++(int);	// incrememnts throughout the neighbours of the vertex, post incremementation
		const std::pair<vertex, int> operator*(); // returns a pair of values, the first being the neighbour vertex, the second being the weight
		const std::pair<const vertex, int>* operator->(); // returns a pointer of a pair of values, the first being the neighbour vertex, the second being the weight
	};
	
	public:
	
	void print() const; // prints the adjacency matrix, used for debugging
	
	weighted_graph(); // A constructor for weighted_graph.
	~weighted_graph(); // A destructor for weighted_graph.
	
	bool are_adjacent(const vertex&, const vertex&) const; // Returns true if the two vertices are adjacent, false otherwise.
	bool has_vertex(const vertex&) const; // Returns true if the passed in vertex is a vertex of the graph, false otherwise.
	
	void add_vertex(const vertex&); // Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex&, const vertex&, const int&); // Adds an edge between the two vertices with the given weight .
	
	void remove_vertex(const vertex&); // Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex&, const vertex&); // Removes the edge between the two vertices, if it exists.
	void set_edge_weight(const vertex&, const vertex&, const int&); // Changes the edge weight between the two vertices to the new weight (the int).
	
	int get_edge_weight(const vertex&, const vertex&) const; // Returns the weight on the edge between the two vertices.
	int degree(const vertex&) const; // Returns the degree of the vertex. (e.g. the number of edges it has)
	int weighted_degree(const vertex&); // Returns the sum of the weights on all the edges incident to the vertex.
	int num_vertices() const; // Returns the total number of vertices in the graph.
	int num_edges() const; // Returns the total number of edges in the graph (just the count, not the weight).
	int total_weight(); // Returns the sum of all the edge weights in the graph.
	
	std::vector<vertex> get_vertices(); // Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex&); // Returns a vector containing the neighbours of the given vertex.
	
	graph_iterator begin(); // Returns a graph_iterator pointing to the start of the vertex set.
	graph_iterator end(); // Returns a graph_iterator pointing to one-past-the-end of the vertex set.
	
	neighbour_iterator neighbours_begin(const vertex&); // Returns a neighbour_iterator pointing to the start of the neighbour set for the given vertex.
	neighbour_iterator neighbours_end(const vertex&); // Returns a neighbour_iterator pointing to one-past-the-end of the neighbour set for the given vertex.

	std::vector<vertex> depth_first(const vertex&); // Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
	std::vector<vertex> breadth_first(const vertex&); // Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.
	
	weighted_graph<vertex> mst(); //Returns a minimum spanning tree of the graph.
};

//////////////////////////////////////////
//                              				//
// 						GRAPH ITERATOR						//
//                              				//
//////////////////////////////////////////

template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g) {
		// constructor, set initial values
		owner = g;
		position = 0;
}

template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g, size_t start_pos) {
		// constructor set initial values, make sure position is equal to the passed in position
		owner = g;
		position = start_pos;
}

template <typename vertex> weighted_graph<vertex>::graph_iterator::~graph_iterator() {
		// destructor
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator=(const graph_iterator& it) { 
		// copy values from R.H.S iterator
		this->position = it.position;
		return this; 
}

template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator==(const graph_iterator& it) const { 
		// check if iterator positions are equal
		return this->position == it.position; 
}

template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator!=(const graph_iterator& it) const { 
		// check if iterator positions are not equal
		return this->position != it.position; 
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++() { 
		// post-increment
		position++;
		return *this; 
}

template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++(int) {
		// pre-increment
		++position;
		return *this; 
}

template <typename vertex> const vertex weighted_graph<vertex>::graph_iterator::operator*() { 
		// return value of the vertex at the current position
		auto v = owner.vertices[position];
		return v;
}

template <typename vertex> const vertex* weighted_graph<vertex>::graph_iterator::operator->() { 
		// returns a pointer of the vertex at the current position
		auto v = owner.vertices[position]; 
		return &v;
}

//////////////////////////////////////////
//                              				//
// 					NEIGHBOUR ITERATOR					//
//                              				//
//////////////////////////////////////////

template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::is_valid_neighbour(int pos) const {
		// neighbour is valid if there is an edge present, also prevents from iterating past the end of the adjacency matrix
		return !(owner.adj_matrix[row_index][pos] == 0 && pos < owner.adj_matrix[row_index].size());
}

template <typename vertex> int weighted_graph<vertex>::neighbour_iterator::get_next(int current_position) {
		// keep incrementing the position until we find a valid neighbour
		while(!is_valid_neighbour(current_position))
				current_position++;
		return current_position;
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u) {
		// constructor, set initial values
		owner = g;
		row_index = owner.get_index(u);
		position = get_next(0); // get the next valid neighbour, passing in index '0' as the current position
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u, size_t start_pos) {
		// constructor, set initial values
		owner = g; 
		row_index = owner.get_index(u);
		position = start_pos; 
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::~neighbour_iterator() {
		// destructor
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator=(const neighbour_iterator& it) {
		// copy values from the R.H.S iterator
		this->row_index = it.row_index; 
		this->position = it.position;
		return *this; 
}

template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator==(const neighbour_iterator& it) const {
		// check if iterator positions are equal
		return this->row_index == it.row_index && this->position == it.position; 
}

template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator!=(const neighbour_iterator& it) const { 
		// check if iterator positions are not equal
		return this->row_index != it.row_index && this->position != it.position; 
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++() { 
		// post-increment, find the next neighbour
		position = get_next(++position);
		return *this; 
}

template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++(int) { 
		// pre-increment, find the next neighbour
		position = get_next(++position);
		return *this;
}

template <typename vertex> const std::pair<vertex, int> weighted_graph<vertex>::neighbour_iterator::operator*() { 
		// return a pair of values: the second neighbour index, as well as the weight
		std::pair<vertex,int> p(owner.vertices[position], owner.adj_matrix[row_index][position]); 
		return p; 
}

template <typename vertex> const std::pair<const vertex, int>* weighted_graph<vertex>::neighbour_iterator::operator->() { 
		// return a reference of a pair of values: the second neighbour index, as well as the weight
		std::pair<const vertex,int> p(owner.vertices[position], owner.adj_matrix[row_index][position]); 
		return &p; 
}

//////////////////////////////////////////
//                              				//
// 				ITERATOR BEGIN AND ENDS				//
//                              				//
//////////////////////////////////////////

template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::begin() {
	// construct the beginning graph iterator
	return graph_iterator(*this);
}

template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::end() {
	// construct the ending graph iterator
	return graph_iterator(*this, vertices.size());
}
	
template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_begin(const vertex& u) {
	// construct the beginning neighbour iterator
	return neighbour_iterator(*this, u);
}

template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_end(const vertex& u) {
	// construct the ending neighbour iterator
	return neighbour_iterator(weighted_graph<vertex>(), u, adj_matrix[get_index(u)].size());
}

//////////////////////////////////////////
//                              				//
// 						WEIGHTED GRAPH						//
//                              				//
//////////////////////////////////////////

template <typename vertex> void weighted_graph<vertex>::print() const {
	// Print statement used for debugging
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

/********************************/
/* 			 Private Methods			 	*/
/********************************/

template <typename vertex> int weighted_graph<vertex>::get_index(const vertex& u) const {
	// for each vertex
	for (unsigned i = 0; i < vertices.size(); i++) { 
		// if the vertex equal to the vertex we are looking for
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

template <typename vertex> int weighted_graph<vertex>::get_min_key(std::vector<int> key, std::vector<bool> mst_set) const {
	// this function finds the next lowest weight to be included in the mst	
	// set the initial min to the maximum integer value
	int min = std::numeric_limits<int>::max(),
			min_index;
	// for each vertex
	for (unsigned i = 0; i < vertices.size(); i++) {
		// the vertex becomes the nex max if:
		// - the vertex is apart of the mst
		// - and its weight is less than the max
		if (!mst_set[i] && key[i] < min) {
			min = key[i];
			min_index = i;
		}
	}
	return min_index;
}

/********************************/
/* 			 	Public Methods			 	*/
/********************************/

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
			degree += adj_matrix[u_pos][i] > 0 
					? 1 
					: 0;
		}
	}
	return degree;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	int weighted_degree = 0;
	// if index is valid
	if (has_vertex(u)) {
		for (auto n = neighbours_begin(u); n != neighbours_end(u); ++n) {
			// incrememnt the weighted_degree by the weight at the coordinate position
			weighted_degree += n->second;
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
	// if index is valid
	if (has_vertex(u)) {
		for (auto n = neighbours_begin(u); n != neighbours_end(u); ++n) {
				// add it to the neigbours list
				neighbours.push_back(n->first);
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
	// graph to return
	weighted_graph<vertex> mst_graph;
	// new vector with size equal to the number of vertices
	// used to store the constructed mst
	std::vector<int> parent(vertices.size()); 
	// new vector with size equal to the number of vertices, set all values to the maximum integer value
	// used to store and pick the minimum weights
	std::vector<int> key(vertices.size(), std::numeric_limits<int>::max());
	// new vector with size equal to the number of vertices, set all values to false;
	// used to represent the vertices that still do not belong to the mst
	std::vector<bool> mst_set(vertices.size(), false);
	
	// use the first vertex to start the mst
	key[0] = 0;
	// first node will be the root of the vertex
	parent[0] = -1;
	
	for (unsigned count = 0; count < vertices.size()-1; count++) {
		// find the next lowest weight from the vertices that have not been included in the mst
		int i = get_min_key(key, mst_set);
		// add it to the mst
		mst_set[i] = true;
		
		for(unsigned j = 0; j < vertices.size(); j++) {
			// iterate through its neighbours and add its weights to the key,
			// so that the edges can be considered for the next minimum value
			if (adj_matrix[i][j] && !mst_set[j] && adj_matrix[i][j] < key[j]) {
				parent[j] = i;
				key[j] = adj_matrix[i][j];
			}
		}
	}
	
	// add the existing vertices to the new graph
	for (unsigned i = 0; i < vertices.size(); i++) {
		mst_graph.add_vertex(vertices[i]);
	}
	
	// add the chosen mst edges and weights to the new graph
	for (unsigned i = 0; i < vertices.size(); ++i) {
		mst_graph.add_edge(
			vertices[parent[i]],
			vertices[i],
			adj_matrix[i][parent[i]]
		);
	}
	
	return mst_graph;
}

#endif
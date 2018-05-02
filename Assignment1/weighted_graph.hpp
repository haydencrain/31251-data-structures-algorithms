#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

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
	
	// 2D vector which stores the weight of each edge.
	std::vector<std::vector<int>> adj_matrix;
	std::vector<vertex> vertices;
	size_t size;
	
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
	int degree(const vertex&) const; //Returns the degree of the vertex.
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


/********************************************************************************************************************************************************************
																GRAPH ITERATOR
*********************************************************************************************************************************************************************/

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


/********************************************************************************************************************************************************************
																NEIGHBOUR ITERATOR
*********************************************************************************************************************************************************************/

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

/********************************************************************************************************************************************************************
																WEIGHTED GRAPH
*********************************************************************************************************************************************************************/

template <typename vertex> weighted_graph<vertex>::weighted_graph(){
	
}

template <typename vertex> weighted_graph<vertex>::~weighted_graph(){
	
}

template <typename vertex> bool weighted_graph<vertex>::has_vertex(const vertex& u) const {
	for (unsigned i=0; i < vertices.size(); i++) {
		if (vertices[i] == u)
			return true;
	}
	return false;
}
	
template <typename vertex> bool weighted_graph<vertex>::are_adjacent(const vertex& u, const vertex& v) const {
	return false;
}

template <typename vertex> void weighted_graph<vertex>::add_vertex(const vertex& v) {

}

template <typename vertex> void weighted_graph<vertex>::add_edge(const vertex& u, const vertex& v, const int& weight) {

}
	
template <typename vertex> void weighted_graph<vertex>::remove_vertex(const vertex& u) {
		// make a new adj_matrix
		// for each value
			// if is the vertex, skip it
			// otherwise, add its values to the new adj_matrix
		// remove the vertex from the vertex list
}


template <typename vertex> void weighted_graph<vertex>::remove_edge(const vertex& u, const vertex& v) {

}

template <typename vertex> void weighted_graph<vertex>::set_edge_weight(const vertex& u, const vertex& v, const int& weight) {

}

template <typename vertex> int weighted_graph<vertex>::get_edge_weight(const vertex& u, const vertex& v) const {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::degree(const vertex& u) const {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::num_vertices() const {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::num_edges() const {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::total_weight() {
	return 0;
}
	
template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_vertices() {
	return std::vector<vertex>();
}

template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_neighbours(const vertex& u) {
	return std::vector<vertex>();
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::depth_first(const vertex& start_vertex){
	return std::vector<vertex>();
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::breadth_first(const vertex& start_vertex){
	return std::vector<vertex>();
}
	
template <typename vertex>	weighted_graph<vertex> weighted_graph<vertex>::mst() {
	return weighted_graph<vertex>();
}


#endif

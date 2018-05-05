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
	std::vector<std::vector<int> > adj_matrix;
	std::vector<vertex> vertices;
	int edges_count;

	int get_index(const vertex &) const;
	void reset_weights(const int &);

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

	weighted_graph();	//A constructor for weighted_graph. It should start empty.
	~weighted_graph(); //A destructor. Depending on how you do things, this may
										 //not be necessary.

	bool are_adjacent(const vertex &, const vertex &) const; //Returns true if the two vertices are
																													 //adjacent, false otherwise.
	bool has_vertex(const vertex &) const;									 //Returns true if the passed in vertex is
																													 //a vertex of the graph, false otherwise.

	void add_vertex(const vertex &);														//Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex &, const vertex &, const int &); //Adds an edge between the two vertices
																															//with the given weight (as an int).

	void remove_vertex(const vertex &);																 //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex &, const vertex &);									 //Removes the edge between the two vertices, if it exists.
	void set_edge_weight(const vertex &, const vertex &, const int &); //Changes the edge weight between the two
																																		 //vertices to the new weight (the int).

	int get_edge_weight(const vertex &, const vertex &) const; //Returns the weight on the edge between the two vertices.
	int degree(const vertex &) const;													 //Returns the degree of the vertex. (e.g. the number of edges it has)
	int weighted_degree(const vertex &);											 //Returns the sum of the weights on all the edges incident to the vertex.
	int num_vertices() const;																	 //Returns the total number of vertices in the graph.
	int num_edges() const;																		 //Returns the total number of edges in the graph (just the count, not the weight).
	int total_weight();																				 //Returns the sum of all the edge weights in the graph.

	std::vector<vertex> get_vertices();									//Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex &); //Returns a vector containing the neighbours of the given vertex.

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

// DELETE AFTER LOL
template <typename vertex>
void weighted_graph<vertex>::print() const
{
	std::cout << "    ";
	for (auto v : vertices)
	{
		std::cout << v << "  ";
	}
	std::cout << "\n   ";
	for (auto v : vertices)
	{
		std::cout << "---";
	}
	std::cout << "\n";
	for (unsigned i = 0; i < num_vertices(); i++)
	{
		std::cout << vertices[i] << " | ";
		for (unsigned j = 0; j < num_vertices(); j++)
		{
			std::cout << adj_matrix[i][j] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

template <typename vertex>
weighted_graph<vertex>::weighted_graph()
{
	edges_count = 0;
}

template <typename vertex> weighted_graph<vertex>::~weighted_graph(){
	
}

template <typename vertex>
bool weighted_graph<vertex>::has_vertex(const vertex &u) const
{
	for (auto i : vertices)
	{
		if (i == u)
			return true;
	}
	return false;
}

template <typename vertex>
void weighted_graph<vertex>::reset_weights(const int &index)
{
	for (unsigned i = 0; i < num_vertices(); i++)
	{
		adj_matrix[index][i] = 0;
		adj_matrix[i][index] = 0;
	}
}

template <typename vertex>
int weighted_graph<vertex>::get_index(const vertex &u) const
{
	for (unsigned i = 0; i < num_vertices(); i++)
	{
		if (vertices[i] == u)
			return i;
	}
	return -1;
}

template <typename vertex>
bool weighted_graph<vertex>::are_adjacent(const vertex &u, const vertex &v) const
{
	if (!(has_vertex(u) && has_vertex(v)))
		return false;
	return adj_matrix[get_index(u)][get_index(v)] > 0;
}

template <typename vertex>
void weighted_graph<vertex>::add_vertex(const vertex &v)
{
	if (!has_vertex(v))
	{
		vertices.push_back(v);
		// resize adj_matrix and set initial weights for new row/column
		adj_matrix.resize(num_vertices());
		for (unsigned i = 0; i < adj_matrix.size(); i++)
		{
			adj_matrix[i].resize(adj_matrix.size());
		}
		reset_weights(num_vertices() - 1);
	}
}

template <typename vertex>
void weighted_graph<vertex>::add_edge(const vertex &u, const vertex &v, const int &weight)
{
	if (has_vertex(u) && has_vertex(v))
	{
		int u_pos = get_index(u);
		int v_pos = get_index(v);
		// if there's already and edge, don't add an edge
		if (adj_matrix[u_pos][v_pos] == 0 && u_pos != v_pos)
		{
			adj_matrix[u_pos][v_pos] = weight;
			adj_matrix[v_pos][u_pos] = weight;
			edges_count++;
		}
	}
}

template <typename vertex>
void weighted_graph<vertex>::remove_vertex(const vertex &u)
{
	if (has_vertex(u))
	{
		int u_pos = get_index(u);
		vertices.erase(vertices.begin() + u_pos);
		adj_matrix.erase(adj_matrix.begin() + u_pos);
		for (unsigned i = 0; i < adj_matrix.size(); i++)
		{
			adj_matrix[i].erase(adj_matrix[i].begin() + u_pos);
		}
	}
}

template <typename vertex>
void weighted_graph<vertex>::remove_edge(const vertex &u, const vertex &v)
{
	adj_matrix[u][v] = 0;
	adj_matrix[v][u] = 0;
	edges_count--;
}

template <typename vertex>
void weighted_graph<vertex>::set_edge_weight(const vertex &u, const vertex &v, const int &weight)
{
	if (has_vertex(u) && has_vertex(v))
	{
		int u_pos = get_index(u);
		int v_pos = get_index(v);
		// if there isn't an edge already, we can't set the edge weight because it doesn't exist
		if (adj_matrix[u_pos][v_pos] > 0 && u_pos != v_pos)
		{
			adj_matrix[u_pos][v_pos] = weight;
			adj_matrix[v_pos][u_pos] = weight;
			edges_count++;
		}
	}
}

template <typename vertex>
int weighted_graph<vertex>::get_edge_weight(const vertex &u, const vertex &v) const
{
	if (has_vertex(u) && has_vertex(v))
	{
		return adj_matrix[get_index(u)][get_index(v)];
	}
	else
		return -1; // if vertices don't exist, return error flag
}

template <typename vertex> int weighted_graph<vertex>::degree(const vertex& u) const {
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	return 0;
}

template <typename vertex>
int weighted_graph<vertex>::num_vertices() const
{
	return vertices.size();
}

template <typename vertex>
int weighted_graph<vertex>::num_edges() const
{
	return edges_count;
}

template <typename vertex> int weighted_graph<vertex>::total_weight() {
	return 0;
}

template <typename vertex>
std::vector<vertex> weighted_graph<vertex>::get_vertices()
{
	return vertices;
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

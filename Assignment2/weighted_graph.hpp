#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

template <typename vertex>
class weighted_graph {

	using graph_iterator = typename std::unordered_set<vertex>::iterator;
	using const_graph_iterator = typename std::unordered_set<vertex>::const_iterator;

	using neighbour_iterator = typename std::unordered_map<vertex, int>::iterator;
	using const_neighbour_iterator = typename std::unordered_map<vertex, int>::const_iterator;

	private:

	std::unordered_set<vertex> vertices;
	std::unordered_map<vertex, std::unordered_map<vertex, int>> adj_list;
	size_t n{0};
	size_t m{0};
	
	public:
	
	bool are_adjacent(const vertex&, const vertex&) const;
	bool has_vertex(const vertex&) const;
	
	void add_vertex(const vertex&);
	void add_edge(const vertex&, const vertex&, const int&);
	
	void remove_vertex(const vertex&);
	void remove_edge(const vertex&, const vertex&);
	void set_edge_weight(const vertex&, const vertex&, const int&);
	
	int get_edge_weight(const vertex&, const vertex&) const;
	int degree(const vertex&) const;
	int weighted_degree(const vertex&) const;
	int num_vertices() const;
	int num_edges() const;
	int total_weight() const;
	
	graph_iterator begin();
	graph_iterator end();
	const_graph_iterator begin() const;
	const_graph_iterator end() const;
	const_graph_iterator cbegin() const;
	const_graph_iterator cend() const;
	
	neighbour_iterator neighbours_begin(const vertex&);
	neighbour_iterator neighbours_end(const vertex&);
	const_neighbour_iterator neighbours_begin(const vertex&) const;
	const_neighbour_iterator neighbours_end(const vertex&) const;
	const_neighbour_iterator cneighbours_begin(const vertex&) const;
	const_neighbour_iterator cneighbours_end(const vertex&) const;
	
};
	
template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::begin() { return vertices.begin(); }
template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::end() { return vertices.end(); }
template <typename vertex>	typename weighted_graph<vertex>::const_graph_iterator weighted_graph<vertex>::begin() const { return vertices.cbegin(); }
template <typename vertex>	typename weighted_graph<vertex>::const_graph_iterator weighted_graph<vertex>::end() const { return vertices.cend(); }
template <typename vertex>	typename weighted_graph<vertex>::const_graph_iterator weighted_graph<vertex>::cbegin() const { return vertices.cbegin(); }
template <typename vertex>	typename weighted_graph<vertex>::const_graph_iterator weighted_graph<vertex>::cend() const { return vertices.cend(); }
	
template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_begin(const vertex& u) { return adj_list.at(u).begin(); }
template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_end(const vertex& u) { return adj_list.at(u).end(); }
template <typename vertex>	typename weighted_graph<vertex>::const_neighbour_iterator weighted_graph<vertex>::neighbours_begin(const vertex& u) const { return adj_list.at(u).cbegin(); }
template <typename vertex>	typename weighted_graph<vertex>::const_neighbour_iterator weighted_graph<vertex>::neighbours_end(const vertex& u) const { return adj_list.at(u).cend(); }
template <typename vertex>	typename weighted_graph<vertex>::const_neighbour_iterator weighted_graph<vertex>::cneighbours_begin(const vertex& u) const { return adj_list.at(u).cbegin(); }
template <typename vertex>	typename weighted_graph<vertex>::const_neighbour_iterator weighted_graph<vertex>::cneighbours_end(const vertex& u) const { return adj_list.at(u).cend(); }

template <typename vertex> bool weighted_graph<vertex>::has_vertex(const vertex& u) const { return vertices.count(u) > 0; }
	
template <typename vertex> bool weighted_graph<vertex>::are_adjacent(const vertex& u, const vertex& v) const {
	if (!(has_vertex(u) && has_vertex(v))) return false;
	return adj_list.at(u).count(v) > 0;
}

template <typename vertex>	void weighted_graph<vertex>::add_vertex(const vertex& v) {
	if (!has_vertex(v)){
		vertices.insert(v);
		adj_list.insert({v, std::unordered_map<vertex,int>()});
		n++;
	}
}

template <typename vertex>	void weighted_graph<vertex>::add_edge(const vertex& u, const vertex& v, const int& weight) {
	if (has_vertex(u) && has_vertex(v) && adj_list[u].count(v) == 0){
		adj_list[u][v] = weight;
		adj_list[v][u] = weight;
		m++;
	}
}
	
template <typename vertex>	void weighted_graph<vertex>::remove_vertex(const vertex& u) {
	if (has_vertex(u)){ 
		n--;
		m -= degree(u);
	}
	
	for (auto itr = neighbours_begin(u); itr != neighbours_end(u); ++itr){
		adj_list.at(itr->first).erase(u);
	}
	
	vertices.erase(u);
	adj_list.erase(u);
}


template <typename vertex>	void weighted_graph<vertex>::remove_edge(const vertex& u, const vertex& v) {
	if (has_vertex(u) && has_vertex(v)){
		if (adj_list.at(u).count(v) > 0) m--;
		adj_list.at(u).erase(v);
		adj_list.at(v).erase(u);
	}
}

template <typename vertex>	void weighted_graph<vertex>::set_edge_weight(const vertex& u, const vertex& v, const int& weight) {
	if (has_vertex(u) && has_vertex(v)){
		adj_list[u][v] = weight;
		adj_list[v][u] = weight;
	}
}

template <typename vertex>	int weighted_graph<vertex>::get_edge_weight(const vertex& u, const vertex& v) const { return adj_list.at(u).at(v); }

template <typename vertex>	int weighted_graph<vertex>::degree(const vertex& u) const { return adj_list.at(u).size(); }

template <typename vertex>	int weighted_graph<vertex>::weighted_degree(const vertex& u) const {
	int total = 0;
	for (auto itr = cneighbours_begin(u); itr != cneighbours_end(u); ++itr){
		total += itr->second;
	} 
	return total;
}

template <typename vertex>	int weighted_graph<vertex>::num_vertices() const { return n; }
template <typename vertex>	int weighted_graph<vertex>::num_edges() const { return m; }

template <typename vertex>	int weighted_graph<vertex>::total_weight() const {
	int total = 0;
	for (auto v : *this){
		total += weighted_degree(v);
	}
	return total/2;
}

#endif

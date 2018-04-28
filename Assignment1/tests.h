#define CXXTEST_HAVE_EH
#define CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <unordered_set>

#include "weighted_graph.h"
#include "test_helper.cpp"

class Management : public CxxTest::GlobalFixture
{

public:
	bool setUpWorld()
	{
		//std::srand(std::time(0));
		return true;
	}

	bool tearDownWorld()
	{
		return true;
	}
};

static Management management;

class Assignment1Tests : public CxxTest::TestSuite
{

public:
	void testBasicConstructor(void)
	{

		weighted_graph<int> g;
		TS_ASSERT_EQUALS(g.num_vertices(), 0);
		TS_ASSERT_EQUALS(g.num_edges(), 0);

		weighted_graph<std::string> h;
		TS_ASSERT_EQUALS(h.num_vertices(), 0);
		TS_ASSERT_EQUALS(h.num_edges(), 0);

		weighted_graph<double> i;
		TS_ASSERT_EQUALS(i.num_vertices(), 0);
		TS_ASSERT_EQUALS(i.num_edges(), 0);
	}

	void testAddVertex()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		for (int i = 0; i < r; ++i)
			g.add_vertex(i);

		TS_ASSERT_EQUALS(g.num_vertices(), r);
	}

	void testHasVertex()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		for (int i = 0; i < r; ++i)
			g.add_vertex(i);

		for (int i = 0; i < r; i++)
		{
			TS_ASSERT(g.has_vertex(i));
		}
	}

	void testRemoveVertex()
	{

		weighted_graph<int> g;

		int r = std::rand() % 20;
		int s = std::rand() % r;

		for (int i = 0; i < r; ++i)
			g.add_vertex(i);

		TS_ASSERT_EQUALS(g.num_vertices(), r);
		for (int i = 0; i < r; i++)
		{
			TS_ASSERT(g.has_vertex(i));
		}

		for (int i = 0; i < s; ++i)
			g.remove_vertex(i);

		TS_ASSERT_EQUALS(g.num_vertices(), r - s);
		for (int i = 0; i < s; ++i)
		{
			TS_ASSERT(!g.has_vertex(i));
		}
		for (int i = s; i < r; ++i)
		{
			TS_ASSERT(g.has_vertex(i));
		}
	}

	void testAddEdge()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		int m = 0;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
					m++;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		TS_ASSERT_EQUALS(g.num_edges(), m);
	}

	void testAreAdjacent()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		int m = 0;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
					m++;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		TS_ASSERT_EQUALS(g.num_edges(), m);

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					TS_ASSERT(g.are_adjacent(i, j));
					TS_ASSERT(g.are_adjacent(j, i));
				}
				else
				{
					TS_ASSERT(!g.are_adjacent(i, j));
					TS_ASSERT(!g.are_adjacent(j, i));
				}
			}
		}
	}

	void testRemoveEdge()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		int m = 0;
		int total_weight = 0;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
					m++;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		struct PairHash
		{
			size_t operator()(const std::pair<int, int> &key) const
			{
				return std::hash<int>()(key.first) * std::hash<int>()(key.second);
			}
		};

		std::unordered_set<std::pair<int, int>, PairHash> edges;
		std::unordered_set<std::pair<int, int>, PairHash> removed_edges;

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);

					if (std::rand() % 2 == 0)
						removed_edges.insert({i, j});
					else
						edges.insert({i, j});
				}
			}
		}

		TS_ASSERT_EQUALS(g.num_edges(), m);

		for (auto e : removed_edges)
		{
			g.remove_edge(e.first, e.second);
		}

		TS_ASSERT_EQUALS(g.num_edges(), m - removed_edges.size());

		for (auto e : edges)
		{
			TS_ASSERT(g.are_adjacent(e.first, e.second));
			TS_ASSERT(g.are_adjacent(e.second, e.first));
		}

		for (auto e : removed_edges)
		{
			TS_ASSERT(!g.are_adjacent(e.first, e.second));
			TS_ASSERT(!g.are_adjacent(e.second, e.first));
		}
	}

	void testGetEdgeWeight()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					TS_ASSERT_EQUALS(g.get_edge_weight(i, j), re[i][j]);
					TS_ASSERT_EQUALS(g.get_edge_weight(j, i), re[j][i]);
				}
			}
		}
	}

	void testSetEdgeWeight()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					TS_ASSERT_EQUALS(g.get_edge_weight(i, j), re[i][j]);
					TS_ASSERT_EQUALS(g.get_edge_weight(j, i), re[j][i]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					int new_weight = (std::rand() % re[i][j]) + 1;
					g.set_edge_weight(i, j, new_weight);
					TS_ASSERT_EQUALS(g.get_edge_weight(i, j), new_weight);
					TS_ASSERT_EQUALS(g.get_edge_weight(j, i), new_weight);
				}
			}
		}
	}

	void testDegree()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			int edge_count = 0;
			for (int j = 0; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					edge_count++;
				}
			}
			TS_ASSERT_EQUALS(g.degree(i), edge_count);
		}
	}

	void testWeightedDegree()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			int total_edge_weight = 0;
			for (int j = 0; j < r; ++j)
			{
				total_edge_weight += re[i][j];
			}
			TS_ASSERT_EQUALS(g.weighted_degree(i), total_edge_weight);
		}
	}

	void testTotalWeight()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		int total_weight = 0;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
					total_weight += weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		TS_ASSERT_EQUALS(g.total_weight(), total_weight);
	}

	void testGetVertices()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		int s = std::rand() % r;

		for (int i = 0; i < r; ++i)
			g.add_vertex(i);

		std::vector<int> v = g.get_vertices();
		TS_ASSERT_EQUALS(g.num_vertices(), v.size());
		for (int i = 0; i < v.size(); ++i)
		{
			TS_ASSERT(g.has_vertex(v[i]));
		}

		for (int i = 0; i < v.size(); ++i)
		{
			for (int j = i + 1; j < v.size(); ++j)
			{
				TS_ASSERT_DIFFERS(v[i], v[j]);
			}
		}

		for (int i = 0; i < s; ++i)
			g.remove_vertex(i);

		v = g.get_vertices();
		TS_ASSERT_EQUALS(g.num_vertices(), v.size());
		for (int i = 0; i < v.size(); ++i)
		{
			TS_ASSERT(g.has_vertex(v[i]));
		}

		for (int i = 0; i < v.size(); ++i)
		{
			for (int j = i + 1; j < v.size(); ++j)
			{
				TS_ASSERT_DIFFERS(v[i], v[j]);
			}
		}
	}

	void testGetNeighbours()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		std::vector<int> vertices = g.get_vertices();
		for (int i = 0; i < vertices.size(); ++i)
		{
			std::vector<int> n_i = g.get_neighbours(vertices[i]);
			TS_ASSERT_EQUALS(g.degree(vertices[i]), n_i.size());
			for (int j = 0; j < n_i.size(); ++j)
			{
				TS_ASSERT(g.are_adjacent(vertices[i], n_i[j]));
			}

			for (int j = 0; j < n_i.size(); ++j)
			{
				for (int k = j + 1; k < n_i.size(); ++k)
				{
					TS_ASSERT_DIFFERS(n_i[j], n_i[k]);
				}
			}
		}
	}

	void testDepthFirst()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		std::unordered_map<int, std::unordered_set<int>> adj_list;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{

			std::unordered_set<int> n;
			for (int j = 0; j < r; ++j)
			{
				if (re[i][j] > 0)
					n.insert(j);
			}
			adj_list.insert({i, n});
		}

		int start_vertex = std::rand() % r;

		std::vector<int> graph_dfs = g.depth_first(start_vertex);
		std::vector<int> reference_dfs = dfs(adj_list, start_vertex);

		TS_ASSERT_EQUALS(graph_dfs, reference_dfs);
	}

	void testBreadthFirst()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;
		std::unordered_map<int, std::unordered_set<int>> adj_list;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{

			std::unordered_set<int> n;
			for (int j = 0; j < r; ++j)
			{
				if (re[i][j] > 0)
					n.insert(j);
			}
			adj_list.insert({i, n});
		}

		int start_vertex = std::rand() % r;

		std::vector<int> graph_bfs = g.breadth_first(start_vertex);
		std::vector<int> reference_bfs = bfs(adj_list, start_vertex);

		TS_ASSERT_EQUALS(graph_bfs, reference_bfs);
	}

	void testMST()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		std::vector<std::pair<int, int>> tree_edges = random_tree(g.get_vertices());
		std::cout << "here" << std::endl;
		for (auto edge : tree_edges)
		{
			g.add_edge(edge.first, edge.second, 1);
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1 && re[i][j] == 0)
				{
					int weight = (std::rand() % 10) + 2;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 1)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		weighted_graph<int> t = g.mst();

		TS_ASSERT_EQUALS(t.num_edges(), t.num_vertices() - 1);
		TS_ASSERT_EQUALS(t.total_weight(), t.num_vertices() - 1);
		TS_ASSERT(is_connected(t));
	}

	void testGraphIterator()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		std::unordered_set<int> it_vertices;
		for (auto v : g)
		{
			it_vertices.insert(v);
		}

		TS_ASSERT_EQUALS(it_vertices.size(), g.num_vertices());

		for (auto u : g.get_vertices())
		{
			TS_ASSERT_LESS_THAN(0, it_vertices.count(u));
		}
	}

	void testNeighbourIterator()
	{

		weighted_graph<int> g;
		int r = std::rand() % 20;

		int re[r][r];

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				re[i][j] = 0;
			}
		}

		for (int i = 1; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (std::rand() % 2 == 1)
				{
					int weight = (std::rand() % 10) + 1;
					re[i][j] = weight;
					re[j][i] = weight;
				}
			}
		}

		for (int i = 0; i < r; ++i)
		{
			g.add_vertex(i);
		}

		for (int i = 0; i < r; ++i)
		{
			for (int j = i + 1; j < r; ++j)
			{
				if (re[i][j] > 0)
				{
					g.add_edge(i, j, re[i][j]);
				}
			}
		}

		for (auto u : g.get_vertices())
		{

			std::unordered_set<int> it_neighbours;
			for (auto n = g.neighbours_begin(u); n != g.neighbours_end(u); ++n)
			{
				it_neighbours.insert(n->first);
			}

			TS_ASSERT_EQUALS(it_neighbours.size(), g.degree(u));
			for (auto v : g.get_neighbours(u))
			{
				TS_ASSERT_LESS_THAN(0, it_neighbours.count(v));
			}
		}
	}
};

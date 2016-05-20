#pragma once
#include <map>
#include "UAV.h"
#include "Link.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/edge_list.hpp"

using namespace std;
using namespace boost;
class Topology
{
public:
	enum Top {
		GRID, RANDOM, BRUTE
	};

private:
	//typedef property<edge_weight_t, string> EdgeWeightProperty;
	//typedef property<vertex_name_t, std::string,property<vertex_index2_t, node> > VertexProperties;
	//typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeWeightProperty> Graph;
	typedef adjacency_list<vecS, vecS, undirectedS, int, string> Graph;
	property_map<Graph, vertex_name_t>::type node_name = get(vertex_name, *caGraph);
	property_map<Graph, vertex_index2_t>::type node_index2 = get(vertex_index2, *caGraph);
	property_map<Graph, vertex_index_t>::type node_index = get(vertex_index, *caGraph);
	property_map<Graph, edge_index_t>::type edges_index = get(edge_index, *caGraph);

	typedef graph_traits<Graph>::edge_descriptor Edge;	
	typedef graph_traits<Graph>::edge_iterator edge_iter;
	typedef graph_traits<Graph>::vertex_descriptor Vertex;
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	const float MAX_IR = 13.26;
	const float IRTable[6] = { 13.26, 9.08, 7.59, 4.69, 3.21, 0 };
	float dX, dY;
	map<int,node> nodes;
	map<string, Link> *links;
	Top topology;
	Graph *neighborGraph;
	Graph *caGraph;

	void calculateNumOfInterfLinks();
	void graphFactory();
	void createNeighborGraph();

public:
	Topology();
	Topology(Topology::Top t, map<int, node> nodes, float x, float y);
	~Topology();

	Graph* creatLinkTopology();
	float getTwoNodesDistance(int p1, int p2);
	float getTwoNodesDistance(node p1, node p2);
	Graph* getCaGraph();
	Graph* getCaGraphCopy();
	int getGwNode();
	map<string, Link> *getLinkTopology();
	Topology::Graph *getNeighborGraph();
	bool isCAValid();
	string toString(int a);
};


#pragma once
#include <map>
#include "UAV.h"
#include "Link.h"
#include <time.h>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/edge_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"

using namespace std;
using namespace boost;

typedef property<edge_index_t, string> EdgeIndexProperty;
typedef property<vertex_index_t, int> VertexIndexProperty;
typedef adjacency_list<vecS, vecS, undirectedS, VertexIndexProperty, EdgeIndexProperty> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator edge_iter;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertex_iterator vertex_iter;

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
		
	/*
	property_map<Graph, vertex_name_t>::type node_name = get(vertex_name, *caGraph);
	property_map<Graph, vertex_index2_t>::type node_index2 = get(vertex_index2, *caGraph);
	*/

	
	const float MAX_IR = 13.26;
	const float IRTable[6] = { 13.26f, 9.08f, 7.59f, 4.69f, 3.21f, 0 };
	float dX, dY;
	map<int,node> nodes;
	map<string, Link> *links;
	Top topology;
	Graph *neighborGraph;
	Graph *caGraph;

	property_map<Graph, vertex_index_t>::type node_index = get(vertex_index, *caGraph);
	property_map<Graph, edge_index_t>::type edges_index = get(edge_index, *caGraph);

	void calculateNumOfInterfLinks();
	void graphFactory();
	void createNeighborGraph();
	void setGwNode(int id);

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
	bool isValidInterferenceRange(node pA, int chA, node pB, int chB);
	bool setBruteTopology();
	bool setGridTopology(float minX, float minY, float deltaX, float deltaY, int gridWidth);
	bool setGridTopology(int numPlayers, float minX, float minY, float delta);
	bool setRandomTopology();
	string toString(int a);
};


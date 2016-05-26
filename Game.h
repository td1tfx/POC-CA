#pragma once
#include "Topology.h"
#include <list>
#include <fstream>

using namespace std;
class Game
{
private:
	int id = 0;
	int maxIteration = 10;
	float maxUF;
	Topology *topology;
	map<int, node> *nodeVertices;
	map<string, Link> *linkEdges;
	map<int, int> *randomNodeOrder;	
	list<string> *maxUFGraphs;


	void initNodes(int num);
	void initRandomOrder();

public:
	Game();
	Game(int numNodes, int iterations = -1);
	float calculateUtilityFuction();
	~Game();

	float getMaxUF() {
		return maxUF;
	}

	int getNodeCount() {
		return nodeVertices->size();
	}

	map<int, node>* getNodes() {
		return nodeVertices;
	}

	Topology* getTopology() {

		if (topology == NULL) {
			cout << "No instance of Topology." << endl;
			exit(-1);
		}
		return topology;
	}

	void playBetterResponseGame(string prefix, int iterations);

};


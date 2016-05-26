#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}

Game::Game(int numNodes, int iterations = -1)
{
	id ++;
	nodeVertices = new map<int, node>();
	maxUF = 0;
	maxUFGraphs = new list<string>();
	initNodes(numNodes);
	maxIteration = iterations;
}

void Game::initNodes(int num) {

	for (int i = 0; i < num; i++) {
		node *newNode = new node(i);
		nodeVertices->insert(pair<int, node>(i, *newNode));
		nodeVertices->at(i).setGame(this);
	}
}

float Game::calculateUtilityFuction() {

	Graph *chGraph = topology->getCaGraph();
	int gwId = topology->getGwNode();
	Vertex s = vertex(gwId, *chGraph);
	std::vector<Vertex> parent(num_vertices(*chGraph));
	std::vector<int> distMap(num_vertices(*chGraph));
	dijkstra_shortest_paths(*chGraph, s, predecessor_map(boost::make_iterator_property_map(parent.begin(), get(boost::vertex_index, *chGraph))).
		distance_map(boost::make_iterator_property_map(distMap.begin(), get(boost::vertex_index, *chGraph))));

	linkEdges = topology->getLinkTopology();
	Link spLink;
	float sum = 0;

	float *miMetric = new float[nodeVertices->size()];
	map<int, node>::iterator i;
	for (i = nodeVertices->begin(); i != nodeVertices->end(); i++) {
		if (i->second.isGw()) {
			miMetric[i->first] = 0;
		}
		else {
			if (distMap.at(i->first) == NULL) {
				miMetric[i->first] = 0;
			}
			else {
				distMap[i->first];
				string linkId = i->first + "--" + parent[i->first];
				spLink = linkEdges->at(linkId);
				miMetric[i->first] = (6 / (float)spLink.getNumOfIntLinks()) / distMap[i->first];
				cout << "Player=" << i->first << " MCS=6" << " IntLink=" << spLink.getNumOfIntLinks() << " dist=" + distMap[i->first] << endl;
			}
		}
	}
	for (int i = 0; i < sizeof(miMetric); i++) {
		sum += miMetric[i];
	}

	if (sum == maxUF) {
		maxUFGraphs->push_back("chGraph");
		//			logger.debug("New maxUF Topology size=" + maxUFGraphs.size() + " maxUF= " + maxUF);
	}

	if (sum > maxUF) {
		cout << "New maxUF uf=" << sum << endl;
		maxUF = sum;
		maxUFGraphs->clear();
		maxUFGraphs->push_back("chGraph");
		cout << "chGraph" << endl;;
	}
	return sum;
}

void Game::initRandomOrder() {
	srand(time(NULL));
	randomNodeOrder = new map<int, int>();
	int random = rand() % nodeVertices->size();
	map<int, node>::iterator i;
	for (i = nodeVertices->begin(); i != nodeVertices->end(); i++) {
		while (randomNodeOrder->find(random) != randomNodeOrder->end()) {
			random = rand() % nodeVertices->size();
		}
		randomNodeOrder->insert(i->first, random);
	}
}

void Game::playBetterResponseGame(string prefix, int iterations) {

	maxIteration = iterations;
	char *newid;
	printf(newid, "%03", id);
	string fName = "gnuplot/" + prefix + "BRGame[" + newid + "]-Interactions[" + topology->toString(maxIteration) + "].data";
	try {
		fstream file;
		file.open(fName, ios::in | ios::out);
		initRandomOrder();
		map<int, node>::iterator i;
		for (i = nodeVertices->begin(); i != nodeVertices->end(); i++) {
			i->second.setRamdomRadios();
			cout << "Initial assingment: Player[" + topology->toString(i->first) + "] " + i->second.radiosToString() << endl;
		}
		string maxUF_t = topology->toString(maxUF) + "\n";
		file << maxUF_t.c_str() << endl;
		for (int it = 1; it <= maxIteration; it++) {
			cout << "Interaction:" << it << endl;
			map<int, int>::iterator j;
			for (j = randomNodeOrder->begin(); j != randomNodeOrder->end(); j++) {
				nodeVertices->at(j->second).playBetterResponse();
				cout << "Player[" << j->second << "] " << nodeVertices->at(j->second).radiosToString() << endl;
			}
			file << maxUF_t.c_str() << endl;
		}
		file.close();
	}
	catch (std::exception &e) {
		cout << e.what() << endl;
	}
}



Game::~Game()
{
}

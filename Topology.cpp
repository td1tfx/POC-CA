#include "stdafx.h"
#include "Topology.h"


Topology::Topology()
{
}

Topology::Topology(Topology::Top t, map<int, node> nodes, float x, float y) {
	topology = t;
	neighborGraph = new Graph();
	links = new map<string, Link>();
	switch (topology) {
	case RANDOM:
	case GRID:
	case BRUTE:
		dX = x;
		dY = y;
		this->nodes = nodes;
		break;
	default:
		break;
	}
}

void Topology::calculateNumOfInterfLinks() {

	Link linkN, linkM;
	pair<edge_iter, edge_iter> edge1, edge2;
	for (edge1 = edges(*caGraph); edge1.first != edge1.second; edge1.first++) {
		//string edgeM = edge1.first->get_property;
		string edgeM = edges_index[*edge1.first];
		for (edge2 = edges(*caGraph); edge2.first != edge2.second; edge2.first++) {
			//string edgeN = edge2.first->get_property;
			string edgeN = edges_index[*edge2.first];
			if (edgeM != edgeN) {
				linkM = links->at(edgeM);
				linkN = links->at(edgeN);
				if (linkM.getChannelNumber() == linkN.getChannelNumber()) {
					if (getTwoNodesDistance(linkM.getNode1(), linkN.getNode2()) <= MAX_IR
						|| getTwoNodesDistance(linkM.getNode1(), linkN.getNode2()) <= MAX_IR
						|| getTwoNodesDistance(linkM.getNode2(), linkN.getNode1()) <= MAX_IR
						|| getTwoNodesDistance(linkM.getNode2(), linkN.getNode2()) <= MAX_IR) {
						linkM.increaseNumOfIntLinks();
					}
				}
			}
		}
	}
}

Topology::Graph* Topology::creatLinkTopology() {
	graphFactory();
	int chi, chj;
	map<int, node>::iterator i;
	map<int, node>::iterator j;
	for (i = nodes.begin; i != nodes.end; i++) {
		for (j = nodes.begin; j != nodes.end; j++) {
			if (i != j) {
				if (getTwoNodesDistance(i->second, j->second) <= MAX_IR) {
					for (int k = 0; k < nodes.at(i->first).getRadios()->size(); k++) {
						for (int m = 0; m < nodes.at(j->first).getRadios()->size(); m++) {
							chi = nodes.at(i->first).getRadios()->at(k);
							chj = nodes.at(j->first).getRadios()->at(m);
							if (chi == chj && chi != 0 && chj != 0) {
								string iFirst = toString(i->first);
								string jFirst = toString(j->first);
								string chiFF = toString(chi);
								graph_traits<Graph>::edge_iterator ei, ei_end;
								bool isExist = false;
								for (tie(ei, ei_end) = edges(*caGraph); ei != ei_end; ++ei) {
									edges_index[*ei] == jFirst + "--" + iFirst + "_ch:" + chiFF;
									bool isExist = true;
								}
								if (!isExist) {
									string linkId = iFirst +"--" + jFirst + "_ch:" + chiFF;
									Edge ed;
									ed = (add_edge(i->first, j->first, *caGraph)).first;
									edges_index[ed] = linkId;
									Link *linksM = new Link(linkId, chi, i->first, j->first);
									links->insert(map<string, Link>::value_type(linkId, *linksM));
								}
							}
						}
					}
				}
			}
		}
	}

	calculateNumOfInterfLinks();
	return caGraph;

}

void Topology::createNeighborGraph() {
	map<int, node>::iterator i;
	for (i = nodes.begin; i != nodes.end; i++) {
		map<int, node>::iterator j;
		for (j = nodes.begin; j != nodes.end; j++) {
			if (i == j) {
				continue;
			}
			else {
				if (getTwoNodesDistance(i->second, j->second) <= MAX_IR) {
					string iFirst = toString(i->first);
					string jFirst = toString(j->first);
					string linkEdge = iFirst + "==" + jFirst;
					Edge ed;
					ed = (add_edge(i->first, j->first, *neighborGraph)).first;
					edges_index[ed] = linkEdge;
				}
			}
		}
	}
}

int Topology::getGwNode() {

	int gwId = -1;
	map<int, node>::iterator i;
	for (i = nodes.begin; i != nodes.end; i++) {
		if (i->second.isGw()) {
			gwId = i->first;
		}
	}
	return gwId;
}

map<string, Link> *Topology::getLinkTopology() {
	return links;
}

Topology::Graph *Topology::getNeighborGraph() {

	if (neighborGraph == NULL) {

	}
	return neighborGraph;
}

void Topology::graphFactory() {

	caGraph = new Graph();
	
	Vertex u;
	map<int, node>::iterator it;
	for (it = nodes.begin; it != nodes.end; it++) {
		u = add_vertex(*caGraph);
		//node_name[u] = it->first;
		//node_index2[u] = it->second;
	}
	
}

bool Topology::isCAValid() {

	vector<int> *radios_i;
	vector<int> *radios_j;
	float distance;
	bool validCA = true;

	map<int, node>::iterator i;
	map<int, node>::iterator j;
	for (i = nodes.begin; i != nodes.end; i++) {
		for (j = nodes.begin; j != nodes.end; j++) {
			distance = getTwoNodesDistance(i->second, j->second);
			if (distance > 0 && distance <= MAX_IR) {
				radios_i = i->second.getRadios();
				radios_j = j->second.getRadios();
				for (int k = 0; k < radios_i->size(); k++) {
					for (int m = 0; m < radios_j->size(); m++) {
						if (radios_i->at(k) != 0 && radios_j->at(m) != 0) {
							validCA = isValidInterferenceRange(i, radios_i.get(k), j, radios_j.get(m));
							if (!validCA) {
								return false;
							}
						}
					}
				}
			}
		}
	}
	return validCA;
}

Topology::Graph* Topology::getCaGraph() {
	return caGraph;
}

Topology::Graph* Topology::getCaGraphCopy() {
	Graph *nGraph = new Graph();
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(*caGraph); vp.first != vp.second; ++vp.first) {
		add_vertex(*nGraph);
	}
	pair<edge_iter, edge_iter> edge1, edge2;
	for (edge1 = edges(*caGraph); edge1.first != edge1.second; edge1.first++) {
		add_edge(source(*edge1.first, *caGraph), target(*edge1.first, *caGraph), *nGraph);
	}
	return nGraph;
}

float Topology::getTwoNodesDistance(int p1, int p2) {


	pair<float, float> posP1 = nodes.at(p1).getpos();
	pair<float, float> posP2 = nodes.at(p2).getpos();
	float distance = sqrt(pow(posP2.first - posP1.first, 2) + pow(posP2.second - posP1.second, 2));
	return distance;
}

float Topology::getTwoNodesDistance(node p1, node p2) {


	pair<float, float> posP1 = p1.getpos();
	pair<float, float> posP2 = p2.getpos();
	float distance = sqrt(pow(posP2.first - posP1.first, 2) + pow(posP2.second - posP1.second, 2));
	return distance;
}



Topology::~Topology()
{

}

string Topology::toString(int a)
{
	char jF[4];
	printf(jF, "%d", a);
	string jFirst = jF;
	return jFirst;
}
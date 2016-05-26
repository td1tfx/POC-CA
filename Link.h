#pragma once
#include "node.h";

using namespace std;
class Link
{
public:
	typedef pair<int, int> Edge;

private:
	int channelNumber;
	Edge incidentVertices;
	string LinkId;
	int numOfIntLinks;
	float throughput;

public:
	Link();
	Link(string strId, int channel, Edge vertices);
	Link(string strId, int channel, int p1, int p2);
	~Link();

	int getChannelNumber() {
		return channelNumber;
	}

	string getLinkId() {
		return LinkId;
	}

	int getNumOfIntLinks() {
		return numOfIntLinks;
	}

	int getNode1() {
		return incidentVertices.first;
	}

	int getNode2() {
		return incidentVertices.second;
	}

	float getThroughput() {
		return throughput;
	}

	void increaseNumOfIntLinks(){
		numOfIntLinks++;
	}

	void setNumOfIntLinks(int num) {
		numOfIntLinks = num;
	}

	void setThroughput(float put) {
		throughput = put;
	}

};


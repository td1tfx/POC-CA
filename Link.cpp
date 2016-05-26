#include "stdafx.h"
#include "Link.h"


Link::Link()
{
	string id = NULL;
	Link(id, -1, 0, 0);
}

Link::Link(string strId, int channel, Edge vertices)
{
	LinkId = strId;
	channelNumber = channel;
	incidentVertices = vertices;
	numOfIntLinks = 1;
	throughput = 6;
}

Link::Link(string strId, int channel, int p1, int p2)
{
	Edge* vertices = new pair<int, int>;
	Link(strId, channel, *vertices);
}

Link::~Link()
{
}



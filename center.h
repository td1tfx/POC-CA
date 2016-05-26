#pragma once
#include "node.h"
class center :
	public node
{
public:
	center();
	~center();

	float winningBidsList[config::taskNum] = { 0 };
	static center controlCenter;
};


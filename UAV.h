#pragma once

#include "node.h"
#include "task.h"
#include "center.h"

using namespace std;

class UAV : public node
{
public:
	UAV();
	~UAV();

	int times = 0;
	int taskList[config::taskNum] = { 0 };
	float winningBidsList[config::taskNum] = {0};
	float bidsList[config::taskNum] = {0};
	int validTaskList[config::taskNum] = {0};
	void updateValid();
	void auction(int taskNum);
};


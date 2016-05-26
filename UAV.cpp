#include "stdafx.h"
#include "UAV.h"


UAV::UAV()
{

}


UAV::~UAV()
{
}

void UAV::updateValid(){
	for (int i = 0; i < config::taskNum; i++) {
		if (bidsList[i] > winningBidsList[i]) {
			validTaskList[i] = 1;
		}
		else {
			validTaskList[i] = 0;
		}
	}
	
}

void UAV::auction(int taskNum) {
	bool sum = 0;
	for (int i = 0; i < config::taskNum; i++) {
		sum = sum + taskList[i];
	}
	if (sum == 0) {
		updateValid();
		if (validTaskList != NULL) {
			int max = 0;
			int tempNum = -1;
			for (int i = 0; i < config::taskNum; i++) {
				int m = bidsList[i] * validTaskList[i];
				if (max < m) {
					max = m;
					tempNum = i;
				}
			}
			if (tempNum >= 0) {
				taskList[tempNum] = 1;
				winningBidsList[tempNum] = max;
			}
		}
	}
}
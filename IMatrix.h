#pragma once
#include "config.h";
#include <vector>
#include <iostream>

using namespace std;
class IMatrix
{

private:
	vector<vector<float>> iMatrix;
	int numRadios;
	int nodeID;

	bool isChannelAssignable(int ch) {
		return iMatrix[ch][ch] == 0;
	}

	bool isChannelAssigned(int ch) {
		return iMatrix[ch][0] == 0;
	}

	void updatePlayerIMatrix(int ch);
	void updateAllPlayersIMatrices(int ch);

public:
	IMatrix();
	IMatrix(int num,int ID);
	~IMatrix();

	void initIMatrix();
	void printIMatrix();
	vector<int> getRadios();
	bool setIMatrixRadios(vector<int> radios);
	int getNumAssingedRadios();

};


#include "stdafx.h"
#include "IMatrix.h"

IMatrix::IMatrix()
{
	IMatrix(-1, -1);
}

IMatrix::IMatrix(int num, int ID)
{
	numRadios = numRadios;
	nodeID = nodeID;
	for (int i = 0; i<12; ++i)
	{
		vector<float> temp; 
		for (int j = 0; j<13; ++j)
		{
			temp.push_back(-2);
		}
		iMatrix.push_back(temp); 
	}
	initIMatrix();
}


IMatrix::~IMatrix()
{

}

void IMatrix::printIMatrix(){
	for (int i = 0; i < iMatrix.size; i++) {
		for (int j = 0; j < iMatrix[i].size; j++) {
			cout << iMatrix[i][j] << "\t" << endl;
		}
		cout << endl;
	}
}

vector<int> IMatrix::getRadios() {

	vector<int> radios(numRadios);
	for (int i = 1; i < iMatrix.size; i++) {
		if (iMatrix[i][0] == 0) {
			radios.push_back(i);
		}
	}
	return radios;
}

int IMatrix::getNumAssingedRadios() {

	int num = 0;
	for (int i = 1; i < iMatrix.size; i++) {
		if (iMatrix[i][0] == 0) {
			num++;
		}
	}
	return num;
}

void IMatrix::updatePlayerIMatrix(int ch) {

	iMatrix[ch][0] = 0;
	iMatrix[ch][ch] = INFINITY;
	int lCh = (ch > 5) ? 4 : ch - 1;
	int rCh = (ch < 7) ? 4 : 11 - ch;
	// LEFT
	for (int i = ch - lCh; i < ch; i++) {
		iMatrix[ch][i] = INFINITY;
	}
	// RIGHT
	for (int i = ch + 1; i < ch + rCh + 1; i++) {
		iMatrix[ch][i] = INFINITY;
	}
	updateAllPlayersIMatrices(ch);
}

void IMatrix::updateAllPlayersIMatrices(int ch) {
	// TODO Auto-generated method stub

}

bool IMatrix::setIMatrixRadios(vector<int> radios) {

	int i = -1;
	int zeroCh = 0;
	for (int ch : radios) {
		i++;
		if (ch == 0) {
			zeroCh++;
			continue;
		}
		else if (isChannelAssigned(ch)) {
			continue;
		}
		else if (isChannelAssignable(ch)) {
			updatePlayerIMatrix(ch);
		}
		else {
			radios[0] = i;
			zeroCh++;
		}
	}
	printIMatrix();
	if (zeroCh == radios.size()) {
		return false;
	}
	else {
		return true;
	}
}

void IMatrix::initIMatrix() {

	for (int i = 0; i < iMatrix.size; i++) {
		for (int j = 0; j < iMatrix[i].size; j++) {
			if (i == 0) {
				iMatrix[i][j] = -1;
			}
			else if (j == 0) {
				iMatrix[i][j] = INFINITY;
			}
			else {
				iMatrix[i][j] = 0;
			}
		}
	}
}

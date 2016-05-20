#pragma once
#include "IMatrix.h"

using namespace std;
class node
{
private:
	int id;
	int generator;
	vector<int>* radios;
	float x, y, z;
	pair<float, float> pos;
	bool gw = false;
	IMatrix* iMatrix;

	int chSpcArray[35][3] = { { 0, 0, 0 },{ 0, 1, 0 },{ 6, 1, 0 },{ 7, 1, 0 },{ 8, 1, 0 },{ 9, 1, 0 },
	{ 10, 1, 0 },{ 11, 1, 0 },{ 0, 2, 0 },{ 7, 2, 0 },{ 8, 2, 0 },{ 9, 2, 0 },
	{ 10, 2, 0 },{ 11, 2, 0 },{ 0, 3, 0 },{ 8, 3, 0 },{ 9, 3, 0 },{ 10, 3, 0 },
	{ 11, 3, 0 },{ 0, 4, 0 },{ 9, 4, 0 },{ 10, 4, 0 },{ 11, 4, 0 },{ 0, 5, 0 },
	{ 10, 5, 0 },{ 11, 5, 0 },{ 0, 6, 0 },{ 11, 6, 0 },{ 0, 7, 0 },
	{ 0, 8, 0 },{ 0, 9, 0 },{ 0, 10, 0 },{ 0, 11, 0 },{ 1, 6, 11 } };

	void initRadios(int numRadios);
	vector<int>* cloneRadios();


public:
	node();
	node(int id);
	node(int id, int numRadio);
	node(int id, int numRadios, float x, float y, float z = 0);

	~node();
	
	int getId() {
		return id;
	}

	float getx() {
		return x;
	}
	float gety() {
		return y;
	}
	float getz() {
		return z;
	}

	pair <float, float> getpos() {
		return pos;
	}

	vector<int>* getRadios() {
		return radios;
	}

	int increaseRadioFast();
	int increaseRadioSlow();
	bool isGw() {
		return gw;
	}

	void playBetterResponse();
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
};


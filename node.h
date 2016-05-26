#pragma once
#include "IMatrix.h"
#include "Game.h"

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
	Game *game;

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
	node(int id, int numRadios = 3, float x = 0, float y = 0, float z = 0);

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

	void setPos(float x, float y) {
		pos.first = x;
		pos.second = y;
	}
		
	void setRadios(int r0, int r1, int r2) {
		vector<int> v;
		v.push_back(r0);
		v.push_back(r1);
		v.push_back(r2);
		setRadios(v);
	}

	void setRadios(int radios[]) {
		setRadios(radios[0], radios[1], radios[2]);
	}

	void setRadios(vector<int> radios) {
		this->radios = &radios;
	}

	void setGw(bool isGw) {
		gw = isGw;
	}

	void setGame(Game *newGame) {
		game = newGame;
	}

	vector<int>* getRadios() {
		return radios;
	}

	int increaseRadioFast();
	int increaseRadioSlow();
	bool isGw() {
		return gw;
	}

	void setRamdomRadios() {
		srand(time(NULL));
		int rnd = rand()/sizeof(chSpcArray);
		setRadios(chSpcArray[rnd]);
	}

	void playBetterResponse();
	
	int radiosToInteger() {
		return 12 * 12 * radios->at(2) + 12 * radios->at(1) + radios->at(0);
	}

	string radiosToString() {

		return "P[" + toString(id) + "] r=" + toString(*radios);
	}

	string toString() {

		return "Player [id=" + toString(id) + ", pos=" + toString(pos.first) + "," + toString(pos.second) + ", radios="
			+ toString(*radios) + "]";
	}

	string toString(int a);
	string toString(vector<int> a);
};


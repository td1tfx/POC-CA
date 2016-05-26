#include "stdafx.h"
#include "node.h"


node::node() {
	
}

node::node(int id, int numRadios = 3, float x = 0, float y = 0, float z = 0) {
	this->id = id;
	initRadios(numRadios);
	this->x = x;
	this->y = y;
	this->z = z;
	iMatrix = new IMatrix(numRadios, id);
}

vector<int>* node::cloneRadios() {

	vector<int> *clone = new vector<int>(radios->capacity());
	for (int i = 0; i < clone->capacity(); i++) {
		clone->push_back(radios->at(i));
	}
	return clone;
}

int node::increaseRadioFast() {

	int r0 = radios->at(0);
	int r1 = radios->at(1);
	int r2 = radios->at(2);

	// 2 active radio(s)
	if (r2 == 0) {
		if (r0 == 6 && r1 == 11) {
			r0 = 1;
			r1 = 6;
			r2 = 11;
		}
		else if (r1 == 0) {
			r1++;
		}
		else if (r0 == 0 && r1 - 5 < 0 || r0 == r1 - 5) {
			if (r1 + 5 <= 11) {
				r0 = r1 + 5;
				// 1 active radio(s)
			}
			else {
				r0 = 0;
				r1++;
			}
		}
		else if (r0 < r1 - 5 || r0 > r1 + 4) {
			if (r0 == 11) {
				r0 = 0;
				r1++;
			}
			else {
				r0++;
			}
		}
	}
	// 3 active radio(s)
	if (radios->at(0) == 1 && radios->at(1) == 6 && radios->at(2) == 11) {
		radios->assign(2, 0);
		radios->assign(1, 0);
		radios->assign(0, 0);
		return -1;
	}
	else {
		radios->assign(2, r2);
		radios->assign(1, r1);
		radios->assign(0, r0);
		return 12 * 12 * r2 + 12 * r1 + 1 * r0;
	}
}

int node::increaseRadioSlow() {

	int r0 = radios->at(0);
	int r1 = radios->at(1);
	int r2 = radios->at(2);

	if (r0 == 11) {
		r0 = 0;
		if (r1 == 11) {
			r1 = 0;
			if (r2 == 11) {
				r2 = r1 = r0 = 0;
				radios->assign(2, 0);
				radios->assign(1, 0);
				radios->assign(0, 0);
				return -1;
			}
			else {
				r2++;
			}
		}
		else {
			r1++;
		}
	}
	else {
		r0++;
	}

	radios->assign(2, r2);
	radios->assign(1, r1);
	radios->assign(0, r0);
	return 12 * 12 * r2 + 12 * r1 + 1 * r0;
}

void node::initRadios(int numRadios) {

	radios = new vector<int>(numRadios);
	for (int i = 0; i < radios->capacity(); i++) {
		radios->push_back(0);
	}
}

void node::playBetterResponse() {


}

string node::toString(int a)
{
	char jF[4];
	printf(jF, "%d", a);
	string jFirst = jF;
	return jFirst;
}

string node::toString(vector<int> a)
{	
	char jF[100];
	printf(jF, "%d", a);
	string jFirst = jF;
	return jFirst;
}

node::~node()
{
}

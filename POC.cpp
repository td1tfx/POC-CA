// POC.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "config.h"
#include "Topology.h"
#include <fstream>


using namespace std;

void loadFiles() {

	int grid[] = { 9, 12, 16, 20, 25 };
	string protocols[] = { "proposed", "original", "hmcp" };
	Loader loader;

	try {
		ofstream wbuf("gnuplot\\utility-function.data");
		if (!p) {
			cout << "can't open utility-function.data!" << endl;
			exit(-1);
		}		
		string spc = "\t";
		wbuf << "#" << spc << "prop." << spc << "orig." << spc << "hmcp" << endl;
		for (int g : grid) {
			wbuf << g << spc;
			for (string p : protocols) {
				loader = new Loader(p);
				loader.loadFile(g);

				wbuf.write(String.format("%.2f", loader.calculateUtilityFunction()).toString() + spc);
			}
			wbuf.write("\n");
		}
		wbuf.close();
	}
	catch (FileException& fe)
	{
		ExceptionInfo* ef = fe.GetExceptionInfo();
		cout << "some falt has happen when opening files, the reason is£º" << fe << endl;
	}
}

int main()
{
	int G[config::UAVNum][config::UAVNum] = {0};

    return 0;
}


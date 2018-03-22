#pragma once
#include <vector>
#include <string>
#include "Sample.h"
using namespace std;


struct position {
	int open;
	int close;
	int date;
};

class Container {
public:
	Container(string path);
	Container();
	~Container();
	void calcSignal();
	void calcMacd();
	void saveToFile(string path);
	string toString();
	vector<Sample> getList();
	Sample find(string date);
private:
	void addAllToList(string path);
	vector<Sample> lista;
	bool macdFlag;
	bool signalFlag;
	position elementsPositionInFile;
	void calcPosition(string path);
	vector<Sample> copyVector(int amount, int last);
};

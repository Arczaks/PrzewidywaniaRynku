#include "Container.h"
#include "Sample.h"
#include "NotCalculatedYetException.h"
#include <iostream>
#include <fstream>
#include <string>

Container::Container(string path){
	this->addAllToList(path);
	macdFlag = false;
	signalFlag = false;
	reverse(lista.begin(), lista.end());
};

Container::~Container() {
	std::cout << "Container destroy" << std::endl;
};

Container::Container() {};

void Container::calcMacd() {
	for (int i = 0; i < lista.size(); i++) {
		if (i < 26) {
			lista.at(i).calcMacd();
		}
		else {
			vector<Sample> list12 = copyVector(12, i);
			vector<Sample> list26 = copyVector(26, i);
			lista.at(i).calcMacd(list12, list26);
		}
	}
	macdFlag = true;
};

void Container::calcSignal() {
	if (macdFlag) {
		for (int i = 0; i < lista.size(); i++) {
			if (i < 26) {
				lista.at(i).calcSignal();
			}
			else {
				vector<Sample> list9 = copyVector(9, i);
				lista.at(i).calcSignal(list9);
			}
		}
		signalFlag = true;
	}
	else {
		throw new NotCalculatedYetException();
	}
};

vector<Sample> Container::copyVector(int amount, int last) {
	vector<Sample> newVector;
	for (int i = last - amount; i <= last; i++) {
		newVector.push_back(lista.at(i));
	}
	return newVector;
};

void Container::saveToFile(string path) {
	if (macdFlag && signalFlag) {
		fstream file;
		file.open(path, ios::out);
		if (file.good() == true) {
			for (Sample s : lista) {
				file << s.toSaveForm();
			}
		}	
		file.close();
	}
	else {
		throw new NotCalculatedYetException();
	}
};

void Container::addAllToList(string path) {
	calcPosition(path);
//  elementsPositionInFile.date = 19;
//	elementsPositionInFile.open = 31;
//  elementsPositionInFile.close = 61;
	fstream file;
	string line;

	string date;
	string open;
	string close;

	file.open(path, ios::in);
	if (file.good() == true) {
		getline(file, line);
		while (!file.eof()){
			getline(file, line);
			if (line == "") {
				break;
			};

			date.insert(0, line, elementsPositionInFile.date, line.find(";", elementsPositionInFile.date + 1) - elementsPositionInFile.date);
			open.insert(0, line, elementsPositionInFile.open, line.find(";", elementsPositionInFile.open + 1) - elementsPositionInFile.open);
			close.insert(0, line, elementsPositionInFile.close, line.find(";", elementsPositionInFile.close + 1) - elementsPositionInFile.close);

			double openD = std::stod(open, 0);
			double closeD = std::stod(close, 0);
			Sample* s = new Sample(date, openD, closeD);
			lista.push_back(*s);
			date = "";
			open = "";
			close = "";
		}
	}
};

void Container::calcPosition(string path) {
	fstream file;
	file.open(path, ios::in);
	string firstLine, secondLine;
	if (file.good() == true) {
		getline(file, firstLine);
		getline(file, secondLine);
	}
	file.close();
	int counter = 0;
	int index = firstLine.find(";");
	int indexSecond = secondLine.find(";");
	while (counter < 3 || index != std::string::npos) {
		index = firstLine.find(";", index + 1);
		indexSecond = secondLine.find(";", indexSecond + 1);
		string tempString;
		tempString.insert(0, firstLine, index + 1, 4);
		if (tempString == "Date" || tempString == "Open" || tempString == "Clos") {
			counter++;
			if (tempString == "Date") {
				elementsPositionInFile.date = indexSecond + 1;
			}
			else {
				if (tempString == "Open") {
					elementsPositionInFile.open = indexSecond + 1;
				}
				else {
					if (tempString == "Clos") {
						elementsPositionInFile.close = indexSecond + 1;
					}
				}
			}
		}
	}
	if (counter != 3) {
		// err TODO
	}
};

string Container::toString() {
	string ret;
	for (Sample s : lista) {
		ret += s.toString();
	}
	return ret;
}

vector<Sample> Container::getList() {
	return lista;
}

Sample Container::find(string date) {
	for (Sample s : lista) {
		if (s.getDate() == date) {
			return s;
		}
	} 
};
#include "Sample.h"
#include <iostream>

Sample::Sample(string date, double open, double close) {
	this->close = close;
	this->date = date;
	this->open = open;
	calcAverage();
};

void Sample::calcAverage() {
	average = (close + open) / 2.0;
//	cout << close <<" " << open <<" " << average << endl;
};

Sample::~Sample() {};

void Sample::calcMacd(vector<Sample> vector12, vector<Sample> vector26) {
	macd = emaMacd(vector12) - emaMacd(vector26);
};

void Sample::calcMacd() {
	macd = 0;
}

void Sample::calcSignal(vector<Sample> vector) {
	signal = emaSignal(vector);
};

double Sample::emaMacd(vector<Sample> vector) {
	reverse(vector.begin(), vector.end());
	double numerator = 0;
	double denominator = 0;
	int index = 0;
	for (Sample s : vector) {
		numerator += pow((1 - (2.0 / (vector.size() - 1))), index) * s.average;
		denominator += pow ((1 - (2.0 / (vector.size() - 1))), index);
		index++;
	}
	return numerator / denominator;
};

double Sample::emaSignal(vector<Sample> vector) {
	reverse(vector.begin(), vector.end());
	double numerator = 0;
	double denominator = 0;
	int index = 0;
	for (Sample s : vector) {
		numerator += pow((1 - (2.0 / (vector.size() - 1))), index) * s.macd;
		denominator += pow((1 - (2.0 / (vector.size() - 1))), index);
		index++;
	}
	return numerator / denominator;

};

void Sample::calcSignal() {
	signal = 0;
}

string Sample::toString() {
	return " data: " + date + 
		" otwarcie: " + std::to_string(open) + 
		" zamkniecie: " + std::to_string(close) + "\n";
}

double Sample::getMacd() {
	return this->macd;
};

double Sample::getSignal() {
	return this->signal;
};

string Sample::toSaveForm() {
	return date +
		";" + std::to_string(average) +
		";" + std::to_string(macd) +
		";" + std::to_string(signal) + "\n";
}

string Sample::getDate() {
	return date;
};

double Sample::getAverage() {
	return average;
};

bool Sample::operator== (Sample &s) {
	return s.getDate() == date;
}
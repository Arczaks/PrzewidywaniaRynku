#pragma once
#include <string>
#include <vector>
using namespace std;

class Sample {
public:
	Sample(string date, double open, double close);
	~Sample();
	void calcSignal(vector<Sample> vector);
	void calcSignal();
	void calcMacd(vector<Sample> vector12, vector<Sample> vector26);
	void calcMacd();
	string toString();
	string toSaveForm();
	double getMacd();
	double getSignal();
	double getAverage();
	string getDate();
	bool operator== (Sample &s);
private:
	double open;
	double close;
	double average;
	string date;
	double macd;
	double signal;
	double emaMacd(vector<Sample> vector);
	double emaSignal(vector<Sample> vector);
	void calcAverage();
};

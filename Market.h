#pragma once
#include "Container.h"

enum status {
	INCREASE,
	DECREASE,
	UNIDENTIFIED
};

class Market {
public:
	Market(Container container);
	~Market();
	string getCurrentDate();
	void start();
	double getValue();
	double getInitialValue();
	void setNextDate(int index);
private:
	string currentDate;
	double cash;
	int numberOfStock;
	Container container;
	double initialValue;
	status status;
	void buy(Sample today);
	void sell(Sample today);
};

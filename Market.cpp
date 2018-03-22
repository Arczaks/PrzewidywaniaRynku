#include "Market.h"
#include <math.h> 
#include <iostream>

Market::Market(Container container) {
	this->container = container;
	this->numberOfStock = 1000;
	this->initialValue = numberOfStock * this->container.getList().at(1).getAverage();
	this->currentDate = this->container.getList().at(26).getDate();
	this->cash = 0;
	this->status = UNIDENTIFIED;
};

Market::~Market() {
	std::cout << "Market destroy" << std::endl;
}

string Market::getCurrentDate() {
	return currentDate;
};

void Market::start() {
//	std::cout << currentDate << std::endl;
	Sample today = container.find(currentDate);
	if (today.getMacd() == 0 && today.getSignal() == 0){
		return;
	}
	else {
		if (status == UNIDENTIFIED) {
			if (today == container.getList().at(1)) {
				return;
			}
			else {
				if (container.getList().at(25).getAverage() >= today.getAverage()) {
					status = DECREASE;
					sell(today);
					return;
				}
				else {
					status = INCREASE;
					return;
				}
			}
		}
		else {
			if (today.getMacd() <= today.getSignal()
				&& status == INCREASE) {
				status = DECREASE;
				sell(today);
				return;
			}
			if (today.getMacd() >= today.getSignal()
				&& status == DECREASE) {
				status = INCREASE;
				buy(today);
				return;
			}
		}
	}
};

void Market::setNextDate(int index) {
	currentDate = container.getList().at(index + 1).getDate();
//	std::cout << currentDate << std::endl;
}

void Market::buy(Sample today) {
	numberOfStock = int (cash / today.getAverage());
	//std::cout << currentDate << " kupiono: " << numberOfStock << "akcji za: " << cash;
	cash -= numberOfStock * today.getAverage();
	//std::cout << " zostalo: " << cash << std::endl;
};

void Market::sell(Sample today) {
	cash += numberOfStock * today.getAverage();
	//std::cout << currentDate << " sprzedano: " << numberOfStock << "akcji za: " << cash << std::endl;
	numberOfStock = 0;
};

double Market::getValue() {
	return ((container.find(currentDate).getAverage() * numberOfStock) + cash);
}

double Market::getInitialValue() {
	return initialValue;
}

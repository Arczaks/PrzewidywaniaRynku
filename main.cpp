#include "Container.h"
#include <iostream>
#include "Market.h"

using namespace std;

string d = "2014-03-20";

int main() {
	cout << "Start" << endl;
	Container* c = new Container("D:\\notoria_data_20180321220545.csv");
//	cout << c->toString() << endl;
	c->calcMacd();
	c->calcSignal();
	c->saveToFile("D:\\out.csv");
	cout << c->getList().at(1).getDate() << " " << c->getList().at(1).getAverage() << endl;
	Market* m = new Market(*c);
	int i = 0;
	while (m->getCurrentDate() != d) {
		m->start();
		m->setNextDate(i);
		i++;
	} 
	cout << "---koniec---" << endl << 
		"na start: " << m->getInitialValue() << endl << 
		"teraz: " << m->getValue() << endl << 
		"zysk: " << (m->getValue() / m->getInitialValue()) - 1 << endl;
	return 0;
}
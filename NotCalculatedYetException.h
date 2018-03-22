#pragma once
#include <exception>
using namespace std;

class NotCalculatedYetException : public exception {
public:
	const char* what() const;
};

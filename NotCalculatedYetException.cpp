#include "NotCalculatedYetException.h"

const char* NotCalculatedYetException::what() const {
	return "Signal or MACD is not calculated yet!";
};
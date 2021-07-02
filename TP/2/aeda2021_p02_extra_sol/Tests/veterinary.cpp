#include "veterinary.h"
#include <sstream>
using namespace std;

Veterinary::Veterinary(string name, int cod) {
	this->name = name;
	this->codOrder = cod;
}

string Veterinary::getName() const {
	return name;
}

string Veterinary::getInfo() const {
	stringstream ss;
	ss << name << ", " << codOrder;
	return ss.str();
}



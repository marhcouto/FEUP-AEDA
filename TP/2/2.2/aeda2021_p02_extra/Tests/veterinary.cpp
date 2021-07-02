#include "veterinary.h"
#include <sstream>
using namespace std;

string Veterinary::getName() const {
    return name;
}

Veterinary::Veterinary(string nome, int cod) {name = nome; codOrder = cod;}

std::string Veterinary::getInfo() const {
    ostringstream ss;
    ss << name << ", " << codOrder;
    return ss.str();
}


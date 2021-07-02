#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}
std::string Zoo::getInfo() const {
    ostringstream stream;
    for (vector<Animal*>::const_iterator it = animals.begin(); it != animals.end(); it++)
        stream << (*it)->getInfo();
    return stream.str();
}
bool Zoo::isYoung(string nameA) {
    for (auto animal : animals){
        if (animal->getName() == nameA)
            return animal->isYoung();
    }
}


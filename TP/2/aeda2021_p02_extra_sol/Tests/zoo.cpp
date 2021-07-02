#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Class Zoo
 */

unsigned Zoo::numAnimals() const {
	return animals.size();
}

unsigned Zoo::numVeterinarians() const {
	return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
	stringstream ss;
	for(unsigned int i = 0; i < animals.size(); i++) {
		ss << animals[i]->getInfo() << "\n";
	}
	return ss.str();
}

bool Zoo::isYoung(string nameA) {
	for(unsigned int i = 0; i < animals.size(); i++) {
		if( animals[i]->getName() == nameA )
			return animals[i]->isYoung();
	}
	return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
	string name, cod;

	while(!isV.eof()) {
		getline(isV,name);
		getline(isV,cod);
		long num = atoi(cod.c_str());
		Veterinary *v1=new Veterinary(name, num);
		veterinarians.push_back(v1);
	}

	for(unsigned int i = 0; i < animals.size(); i++)
		animals[i]->setVeterinary( veterinarians[i%veterinarians.size()] );

}

bool Zoo::removeVeterinary(string nameV) {
	for(unsigned int i = 0; i < veterinarians.size(); i++) {
		if( veterinarians[i]->getName() == nameV ) {
			//look for animals treated by Veterinary with name nameV
			for(unsigned int j = 0; j < animals.size(); j++) {
				if( animals[j]->getVeterinary() == veterinarians[i] )
					//replaces with the next veterinary in the vector
					animals[j]->setVeterinary( veterinarians[(i + 1)%veterinarians.size()] );
			}
			veterinarians.erase( veterinarians.begin() + i );

			return true;
		}
	}
	return false;
}


bool Zoo::operator < (Zoo& zoo2) const {
	int sum1 = 0, sum2 = 0;
	for(unsigned int i = 0; i < this->animals.size(); i++)
		sum1 += animals[i]->getAge();
	for(unsigned int j = 0; j < zoo2.animals.size(); j++)
		sum2 += zoo2.animals[j]->getAge();
	return sum1 < sum2;
}


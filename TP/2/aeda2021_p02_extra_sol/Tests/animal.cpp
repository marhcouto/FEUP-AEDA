#include "animal.h"
#include <sstream>
using namespace std;

Animal::Animal(string name, int age) {
	this->name = name;
	this->age = age;
	this->vet = 0;
	if( age < youngest ) youngest = age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
	return age;
}

int Animal::youngest = 999;

int Animal::getYoungest() {
	return youngest;
}

void Animal::setVeterinary(Veterinary *vet) {
	this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
	return vet;
}

string Animal::getInfo() const {
	stringstream ss;
	ss << name << ", " << age;
	if (vet != NULL) ss << ", " << vet->getInfo();
	return ss.str();
}


/*
 * Class Dog
 */

Dog::Dog(string name, int age, string breed): Animal(name, age) {
	this->breed = breed;
}

string Dog::getInfo() const {
	stringstream ss;
	ss << Animal::getInfo() << ", " << breed;
	return ss.str();
}

bool Dog::isYoung() const {
	if (age < 5) return true;
	else return false;
}



/*
 * Class Flying
 */

Flying::Flying(int maxv, int maxa) {
	this->maxVelocity = maxv;
	this->maxAltitude = maxa;
}

string Flying::getInfo() const {
	stringstream ss;
	ss << maxVelocity << ", " << maxAltitude;
	return ss.str();
}



/*
 * Class Bat
 */

Bat::Bat(string name, int age, int maxv, int maxa): Animal(name, age), Flying(maxv, maxa) {
}

string Bat::getInfo() const {
	stringstream ss;
	ss << Animal::getInfo() << ", " << Flying::getInfo();
	return ss.str();
}

bool Bat::isYoung() const {
	if (age < 4) return true;
	else return false;
}





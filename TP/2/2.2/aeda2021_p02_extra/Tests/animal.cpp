#include "animal.h"
#include <sstream>
using namespace std;

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

Animal::Animal(std::string name, int age) : name(name), age(age) {
    if(age < youngest || youngest == 0)
        youngest = age;
}
Dog::Dog(std::string name, int age, std::string breed) : Animal(name, age), breed(breed){}
Flying::Flying(int maxv, int maxa) : maxVelocity(maxv), maxAltitude(maxa){}
Bat::Bat(std::string name, int age, int maxv, int maxa) : Animal(name, age), Flying(maxv, maxa){}

int Animal::getYoungest() {return youngest;}
bool Dog::isYoung() const {
    return age < 5;
}
bool Bat::isYoung() const {
    return age < 4;
}
std::string Animal::getInfo() const {
    ostringstream stream;
    stream << name << ", " << age;
    if (vet != NULL) stream << ", " << vet->getInfo();
    return stream.str();
}
std::string Dog::getInfo() const {
    ostringstream stream;
    stream << Animal::getInfo() << ", " << breed;
    return stream.str();
}
std::string Bat::getInfo() const {
    ostringstream stream;
    stream << Animal::getInfo() << ", " << Flying::getMaxVelocity() << ", " << Flying::getMaxAltitude();
    return stream.str();
}

int Animal::youngest = 0;


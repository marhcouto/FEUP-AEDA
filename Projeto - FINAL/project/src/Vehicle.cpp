
#include "Vehicle.h"

bool Vehicle::operator==(Vehicle &v1){
    return this->getMatricula() == v1.getMatricula();
}

void Vehicle::setEntryKm(float entryKm) {
    this->entryKm = entryKm;
}

void Vehicle::setEntryPort(std::string portName) {
    this->entryPort = portName;
}

void Vehicle::setEntryTime(float val) {
    this->entryTime = val;
}

void Vehicle::setExitPort(std::string portName) {
    this->exitPort = portName;
}

void Vehicle::setDriver(Driver *driver) {
    this->driver = driver;
}

void Vehicle::print() const {
    std::cout << "License Plate: " << matricula << " | " << "Driver: " << driver->getName() << std::endl;
}

std::ostream &operator<<(std::ostream &o, const Vehicle &v) {
    o << v.driver->getName() << std::endl << v.getMatricula() << " " << v.getClass() << " " << v.getPrefers() <<
    " " << v.getEntryPort() << " " << v.getEntryKm();
    return o;
}

void VehicleClass1::print() const {
    std::cout << "License Plate: " << getMatricula() << " | " << "Driver: " << getDriver()->getName() << " | ";
    std::cout << "Class: " << getClass() << std::endl;
}

void VehicleClass2::print() const {
    std::cout << "License Plate: " << getMatricula() << " | " << "Driver: " << getDriver()->getName() << " | ";
    std::cout << "Class: " << getClass() << std::endl;
}

void VehicleClass3::print() const {
    std::cout << "License Plate: " << getMatricula() << " | " << "Driver: " << getDriver()->getName() << " | ";
    std::cout << "Class: " << getClass() << std::endl;
}

void VehicleClass4::print() const {
    std::cout << "License Plate: " << getMatricula() << " | " << "Driver: " << getDriver()->getName() << " | ";
    std::cout << "Class: " << getClass() << std::endl;
}

std::ostream &operator<<(std::ostream &o, const VehicleClass1 &v) {
    std::string tipo = "f";
    if (v.getPrefers())
        tipo = "t";
    o << v.getDriver()->getName() << "\n\n";
    o << std::endl;
    o << v.getMatricula() << " " << v.getClass() << " " << tipo << " " << v.getEntryPort() << " " << v.getEntryKm();
    return o;
}

std::ostream &operator<<(std::ostream &o, const VehicleClass2 &v) {
    std::string tipo = "f";
    if (v.getPrefers())
        tipo = "t";
    o << v.getDriver()->getName();
    o << std::endl;
    o << v.getMatricula() << " " << v.getClass() << " " << tipo << " " << v.getEntryPort() << " " << v.getEntryKm();
    return o;
}

std::ostream &operator<<(std::ostream &o, const VehicleClass3 &v) {
    std::string tipo = "f";
    if (v.getPrefers())
        tipo = "t";
    o << v.getDriver()->getName();
    o << std::endl;
    o << v.getMatricula() << " " << v.getClass() << " " << tipo << " " << v.getEntryPort() << " " << v.getEntryKm();
    return o;
}

std::ostream &operator<<(std::ostream &o, const VehicleClass4 &v) {
    std::string tipo = "f";
    if (v.getPrefers())
        tipo = "t";
    o << v.getDriver()->getName();
    o << std::endl;
    o << v.getMatricula() << " " << v.getClass() << " " << tipo << " " << v.getEntryPort() << " " << v.getEntryKm();
    return o;
}

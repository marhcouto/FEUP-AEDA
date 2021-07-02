//
// Created by marhc on 15/11/2020.
//

#include "Worker.h"
#include <iostream>

/* ---Class Person--- */

bool Person::operator==(const Person &p) const {
    return this->name == p.name;
}

/* ---Class Driver--- */

void Driver::setVehicles(std::vector<std::string> vehicles) { this->vehicles = vehicles; }
void Driver::addVehicle(std::string vehicle) { this->vehicles.push_back(vehicle); }
void Driver::removeVehicle(std::string vehicle) {
    for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
        if ((*it) == vehicle) {
            vehicles.erase(it);
            break;
        }
    }
}

void Driver::print() const {
    std::cout << "Name: " << name << " | ";
    std::cout << "Cars: ";
    for (auto car : vehicles)
        std::cout << car << " ";
    std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& os, const Driver& d) {
    os << d.name << std::endl;
    for (auto licensePlate : d.vehicles)
        os << licensePlate << " ";
    return os;
}

std::istream& operator>> (std::istream& is, Driver& d) {
    std::string matricula, lastmatricula, matriculas;
    std::stringstream ss;
    std::getline(is, d.name);
    std::getline(is, matriculas);
    ss << matriculas;
    while (true) {
        ss >> matricula;
        if (matricula == lastmatricula) break;
        lastmatricula = matricula;
        d.addVehicle(matricula);
    }
    return is;
}

bool Driver::ownsVehicle (std::string licensePlate) const {
    return (std::count (vehicles.begin(), vehicles.end(), licensePlate)) ? true : false;
}

/* ---Class Worker--- */

bool Worker::operator==(const Worker &worker) const {
    return getName() == worker.getName() && workerID == worker.workerID;
}
void Worker::print(){
    std::cout << "Name:" << getName() << " ID:" << workerID << " Salary:" << salary << std::endl;
}

void Worker::setActive(bool a) {
    this->active = a;
}

void Worker::setWorkerID(unsigned int ID) {
    this->workerID = ID;
}

void Worker::setPort(std::string portName) {
    this->port = portName;
}

void Worker::setHighway(std::string highwayName) {
    this->highway = highwayName;
}

std::string Worker::getActiveString() const {
    if (active) return "Active";
    else return "Inactive";
}

void Worker::print() const {
    std::cout << "Name: " << name << " | " << "Status: " << getActiveString() << " | " << "Salary: " << salary << " | ";
    std::cout << "Port: " << port << " | " << "Highway: " << highway << " | " << "ID: " << workerID << std::endl;
}

std::ostream &operator <<(std::ostream &o, const Worker &w) {
    std::string active;
    if(w.active)
        active = "Active";
    else
        active = "Inactive";
    o << w.getName() << std::endl << w.salary << " " << active << " " << w.port << " " << w.highway;
    return o;
}

std::istream& operator>> (std::istream &is, Worker& w) {
    std::string active;
    std::getline(is, w.name);
    is >> w.salary >> active >> w.port >> w.highway;
    if (active == "Active") w.active = true;
    else w.active = false;
    return is;
}

/* ---Class Manager--- */

void Manager::changePassword(std::string newPassword) {
    this->password = newPassword;
}

void Manager::print() const {
    std::cout << "Name: " << name << " | " << "Password: " << password << std::endl;
}

std::ostream &operator <<(std::ostream &o, const Manager &m) {
    o << m.getName() << "\n" << m.getPassword();
    return o;
}

std::istream& operator>> (std::istream& is, Manager& m) {
    std::getline(is, m.name);
    is >> m.password;
    return is;
}

/* ---Class Technician--- */
float Technician::getAverageTime() const {
    return this->interventions / this->timeWorking;
}

void Technician::addExperience(int timeWorked) {
    this->timeWorking += timeWorked;
}

void Technician::print() const {
    std::cout << "Name: " << name << " | " << "Interventions: " << interventions << " | ";
    std::cout << "Time spent on jobs: " << timeWorking << " | " << "Average job time: " << getAverageTime() << " | "
    << "Port: " << port << " | " << "Specialty: " << getSpecString() << std::endl;
}

bool Technician::operator< (const Technician &tech) const {
    return this->getAverageTime() > tech.getAverageTime();
}

bool Technician::operator== (const Technician &tech) const {
    return this->name == tech.name && this->specialty == tech.specialty && this->port == tech.port;
}

void Technician::operator++() {
    this->interventions++;
}

std::string Technician::getSpecString() const {
    switch (specialty) {
        case Informatics: return "Informatics";
        case Electronics: return "Electronics";
        case Revision: return "Revision";
        default: return "";
    }
}

std::ostream& operator<< (std::ostream& os, const Technician& tech) {
    os << tech.name << std::endl << tech.getSpecString() << " " << tech.interventions
    << " " << tech.port << " "  << tech.timeWorking;
    return os;
}

std::istream& operator>> (std::istream& is, Technician& tech) {
    std::string spec;
    std::getline (is, tech.name);
    is >> spec >> tech.interventions >> tech.port >> tech.timeWorking;
    if (spec == "Informatics") tech.specialty = Informatics;
    else if (spec == "Electronics") tech.specialty = Electronics;
    else tech.specialty = Revision;
    return is;
}

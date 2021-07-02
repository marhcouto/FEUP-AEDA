//
// Created by marhc on 17/11/2020.
//

#include "HighWay.h"
#include <algorithm>
#include <sstream>

void HighWay::setPortagensS(std::vector<PortagemSaida*> portagens) {
    this->portagensS = portagens;
}

void HighWay::setPortagensE(std::vector<PortagemEntrada*> portagens) {
    this->portagensE = portagens;
}

void HighWay::addPortagemE(PortagemEntrada *portagem) {
    portagensE.push_back(portagem);
}

void HighWay::addPortagemS(PortagemSaida *portagem) {
    portagensS.push_back(portagem);
}

void HighWay::sortPortagens() {
    std::sort(portagensE.begin(), portagensE.end());
    std::sort(portagensS.begin(), portagensS.end());
}

/*void HighWay::removePortagem(Portagem *portagem) {
    std::vector<Portagem*>::iterator it;
    for (it = portagens.begin(); it != portagens.end(); it++){
        if(**it == *portagem) portagens.erase(it);
        return;
    }
    throw PortagemDoesNotExist<Portagem, HighWay>(portagem, this);
}*/

bool HighWay::operator==(const HighWay &highway) {
    return name == highway.name;
}

bool HighWay::operator<(const HighWay &highway) {
    return name < highway.name;
}

void HighWay::enterVehicle(Vehicle *v1, std::string namePort, bool write) {
    enterVehicle(v1, findPortE(namePort), write);
}

void HighWay::enterVehicle(Vehicle *v1, PortagemEntrada *port, bool write) {
    port->enterVehicle(v1, write);
    vehiclesInTransit.push_back(v1);
}

bool HighWay::exitVehicle(Vehicle *v1, PortagemSaida *port) {
    bool missbehaved = port->exitVehicle(v1);
    removeVehicle(v1);
    return missbehaved;
}

bool HighWay::exitVehicle(Vehicle *v1, std::string namePort) {
    return this->exitVehicle(v1, findPortS(namePort));
}

void HighWay::removeVehicle(Vehicle *v1) {
    std::vector<Vehicle*>::iterator it = std::find(vehiclesInTransit.begin(), vehiclesInTransit.end(), v1);
    if (it == vehiclesInTransit.end()) throw VehicleNotInTransit(v1->getMatricula(), this->getName());
    vehiclesInTransit.erase(it);
    delete *it;
}

void HighWay::setVehicles(std::vector<Vehicle *> vehicles) {
    this->vehiclesInTransit = vehicles;
}

void HighWay::printPorts() {
    std::cout << "Entry ports: ";
    std::vector<PortagemEntrada*>::const_iterator it;
    for (it = portagensE.begin(); it != portagensE.end(); it++) {
        std::cout << (*it)->getName() << " ";
    }
    std::cout << "\nExit ports: ";
    std::vector<PortagemSaida*>::const_iterator it1;
    for (it1 = portagensS.begin(); it1 != portagensS.end(); it1++) {
        std::cout << (*it1)->getName() << " ";
    }
    std::cout << std::endl;
}

PortagemEntrada* HighWay::findPortE(std::string name) {
    std::vector<PortagemEntrada*>::const_iterator it;
    for (it = portagensE.begin(); it != portagensE.end(); it++) {
        if ((*it)->getName() == name) return *it;
    }
    throw PortagemDoesNotExist(name);
}

PortagemSaida* HighWay::findPortS(std::string name) {
    std::vector<PortagemSaida*>::const_iterator it;
    for (it = portagensS.begin(); it != portagensS.end(); it++) {
        if ((*it)->getName() == name) return *it;
    }
    throw PortagemDoesNotExist(name);
}

Vehicle* HighWay::findVehicle(std::string matricula) {
    std::vector<Vehicle*>::const_iterator it;
    for (it = vehiclesInTransit.begin(); it != vehiclesInTransit.end(); it++) {
        if ((*it)->getMatricula() == matricula) return *it;
    }
    throw VehicleNotInTransit(matricula, this->getName());
}

void HighWay::printCurrentVehicles() {
    std::vector<Vehicle*>::const_iterator it;
    for (it = vehiclesInTransit.begin(); it != vehiclesInTransit.end(); it++) {
        std::cout << (*it)->getMatricula() << " ";
    }
    std::cout << std::endl;
}

void HighWay::print(){
    std::cout << "Name:" << name << " | " << "Length:" << km << std::endl;
}

std::ostream &operator<<(std::ostream &o, const HighWay &h) {
    o << h.getName() << " " << h.km;
    return o;
}

std::istream& operator>> (std::istream& is, HighWay& h) {
    is >> h.name >> h.km;
    return is;
}


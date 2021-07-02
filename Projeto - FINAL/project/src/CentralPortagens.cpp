//
// Created by marhc on 15/11/2020.
//

#include "CentralPortagens.h"
#include <algorithm>

unsigned int CentralPortagens::nextID = 1;

CentralPortagens::~CentralPortagens() {
    for (auto& a : highways) delete a;
    for (auto& a : portagensS) delete a;
    for (auto& a : portagensE) delete a;
    for (auto& a : workers) delete a;
    for (auto& a : vehicles) delete a;
    for (auto& a : missbDrivers) delete a;
    for (auto& a : drivers) delete a;
    for (auto& a : managers) delete a;
    interventions.clear();
}

void CentralPortagens::setHighWays(std::vector<HighWay *> highways) {
    this->highways = highways;
}

void CentralPortagens::setWorkers(std::vector<Worker *> workers) {
    this->workers = workers;
}

void CentralPortagens::setManagers(std::vector<Manager *> managers) {
    this->managers = managers;
}

void CentralPortagens::setDrivers(const DriversHT &drivers) {
    this->drivers = drivers;
}

void CentralPortagens::setDrivers(const std::vector<Driver*>&  drivers) {
    for (auto& d : drivers)
        this->drivers.insert(d);
}

void CentralPortagens::setIntervs(const BST<Intervention> &interventions) {
    this->interventions = interventions;
}

void CentralPortagens::setMissbDrivers(const DriversHT &drivers) {
    this->missbDrivers = drivers;
}

void CentralPortagens::setMissbDrivers(const std::vector<Driver*>& drivers) {
    for (auto& d : drivers)
        this->addMissbehavedDriver(d);
}

void CentralPortagens::addPortagemE(PortagemEntrada *portagem, HighWay *highway) {
    std::vector<HighWay*>::iterator it;
    for (it = highways.begin(); it != highways.end(); it++){
        if(**it == *highway) (*it)->addPortagemE(portagem);
        return;
    }
}

void CentralPortagens::addPortagemS(PortagemSaida *portagem, HighWay *highway) {
    std::vector<HighWay*>::iterator it;
    for (it = highways.begin(); it != highways.end(); it++){
        if(**it == *highway) (*it)->addPortagemS(portagem);
        return;
    }
    throw HighWayDoesNotExist(highway->getName());
}

void CentralPortagens::addVehicle(Vehicle *vehicle) {
    vehicles.push_back(vehicle);
}

void CentralPortagens::addDriver(Driver* driver) {
    drivers.insert(driver);
}

void CentralPortagens::addIntervention(int year, int day, int month, int duration, std::string type, std::string port) {
    Specialty spec;
    if (type == "Revision") spec = Revision;
    else if (type == "Informatics") spec = Informatics;
    else if (type == "Electronics") spec = Electronics;
    else throw SpecialtyInvalid(type);
    this->addIntervention( Intervention(day, month, year, duration, nullptr, port, spec));
}

void CentralPortagens::addIntervention(Intervention i) {
    Portagem* p = this->findPort(i.getPort());
    if (p == nullptr) throw PortagemDoesNotExist(i.getPort());
    Technician* t = this->getClosestTech(p, i.getType());
    if (t == nullptr) throw NoTechniciansAround(i.getPort(), i.getTypeString());
    t++;
    t->addExperience(i.getDuration());
    i.setTech(t);
    interventions.insert(i);
}

void CentralPortagens::addMissbehavedDriver(Driver *d) {
    missbDrivers.insert(d);
}

void CentralPortagens::removeMissbehavedDriver(std::string name) {
    Driver d(name);
    auto it = missbDrivers.find(&d);
    if (it == missbDrivers.end()) throw DriverNotFound(name);
    missbDrivers.erase(it);
    delete *it;
}

void CentralPortagens::removeDriver(std::string name) {
    Driver d(name);
    auto it = drivers.find(&d);
    if (it == drivers.end()) throw DriverNotFound(name);
    missbDrivers.erase(it);
    delete *it;
}

void CentralPortagens::removeIntervention(int day, int month, int year, int duration, std::string type,
                                          std::string port) {
    Specialty spec;
    if (type == "Revision") spec = Revision;
    else if (type == "Informatics") spec = Informatics;
    else if (type == "Electronics") spec = Electronics;
    else throw SpecialtyInvalid(type);
    if (!(interventions.remove(Intervention(day, month, year, duration, nullptr, port, spec))))
        throw InterventionDoesNotExist();
}

void CentralPortagens::removeVehicle(Vehicle *vehicle) {
    std::vector<Vehicle*>::iterator it;
    it = std::find(vehicles.begin(), vehicles.end(), vehicle);
    if (it == vehicles.end()) throw VehicleNotInTransit(vehicle->getMatricula(), this->getName());
    else {
        vehicles.erase(it);
        delete *it;
    }
}

void CentralPortagens::setPortagensE(std::vector<PortagemEntrada*> portagens) {
    this->portagensE = portagens;
}

void CentralPortagens::setPortagensS(std::vector<PortagemSaida*> portagens) {
    this->portagensS = portagens;
}

void CentralPortagens::addWorker(Worker *worker) {
    workers.push_back(worker);
}

void CentralPortagens::setVehicles(std::vector<Vehicle *> vehicles) {
    this->vehicles = vehicles;
}

void CentralPortagens::enterVehicle(Vehicle *v, std::string pName, std::string hName) {
    std::vector<HighWay*>::iterator it;
    this->findHighWay(hName)->enterVehicle(v, pName, true);
    drivers.insert(v->getDriver());
}

void CentralPortagens::exitVehicle(Vehicle *v, std::string pName, std::string hName) {
    std::vector<HighWay*>::iterator it;
    if (this->findHighWay(hName)->exitVehicle(v, pName)) this->addMissbehavedDriver(v->getDriver());
    this->removeVehicle(v);
}

void CentralPortagens::exitVehicle(std::string vMatricula, std::string pName, std::string hName) {
    this->exitVehicle(this->findVehicle(vMatricula), pName, hName);
}

void CentralPortagens::assignWorkers() {
    std::vector<Worker *>::const_iterator it1 = workers.begin();
    std::vector<PortagemSaida*>::iterator it2;
    unsigned int iteration = 0;
    for (it2 = portagensS.begin(); it2 != portagensS.end(); it2++) {
        for (unsigned int i = (*it2)->getNWays() - (*it2)->getVV(); i > 0; i--) {
            if(it1 == workers.end()) throw NotEnoughWorkers();
            (*it2)->addWorker((*it1));
            it1++;
            iteration++;
        }
        (*it2)->assignWorkers();
    }
}

void CentralPortagens::changeWorker(std::string oldWorkerName, std::string newWorkerName) {
    Worker *w1 = findWorker(oldWorkerName);
    Worker *w2 = findWorker(newWorkerName);
    if (!w1->getActive()) throw WorkerIsNotActive(w1->getName());
    if (w2->getActive()) throw WorkerIsActive(w2->getName());
    changeWorker(w1, w2);
}

void CentralPortagens::changeWorker(Worker *oldWorker, Worker *newWorker) {
    std::vector<PortagemSaida*>::iterator it;
    for (it = portagensS.begin(); it != portagensS.end(); it++) {
        if ((*it)->changeWorker(oldWorker, newWorker)) return;
    }
    throw WorkerDoesNotExist(oldWorker->getName(), this->getName());
}

void CentralPortagens::fireWorker(std::string name) {
    std::vector<Worker*>::iterator it;
    for (it = workers.begin(); it != workers.end(); it++) {
        if ((*it)->getName() == name) {
            if((*it)->getActive()) throw WorkerIsActive((*it)->getName());
            else {
                workers.erase(it);
                delete *it;
                return;
            }
        }
    }
    throw WorkerDoesNotExist(name, this->getName());
}

void CentralPortagens::hireWorker(Worker *w) {
    workers.push_back(w);
}

void CentralPortagens::hireTechnician(Technician *t) {
    Portagem* port = this->findPort(t->getPort());
    if (port == nullptr) throw PortagemDoesNotExist(t->getPort());
    port->addTech(t);
}

void CentralPortagens::fireTechnician(Technician *t) {
    Portagem* port = this->findPort(t->getPort());
    if (port == nullptr) throw PortagemDoesNotExist(t->getPort());
    port->removeTech(t);
}

void CentralPortagens::assignTechs(const std::vector<Technician*>& techs) {
    for (auto& t : techs) {
        Portagem* ptr = this->findPort(t->getPort());
        if (ptr != nullptr)
            ptr->addTech(t);
        else
            throw PortagemDoesNotExist(t->getPort());
    }
}

void CentralPortagens::assignIntervs(const std::vector<Technician*>& techs) {
    BSTiterator<Intervention> it = interventions.begin();
    for (; !(it == interventions.end()); it++) {
        bool found  = false;
        for (auto& t : techs) {
            if (*t == *((*it).getTech())) {
                (*it).setTech(t);
                found = true;
                break;
            }
        }
        if (!found) throw TechnicianNotFound((*it).getTech()->getName(), (*it).getTech()->getSpecString(), (*it).getTech()->getPort());
    }
}

void CentralPortagens::assignVehicles() {
    std::vector<HighWay*>::iterator it;
    std::vector<Vehicle*>::iterator it1;
    for (it1 = vehicles.begin(); it1 != vehicles.end(); it1++) {
        PortagemEntrada *p = findPortE((*it1)->getEntryPort());
        bool found = false;
        DriversHT::iterator it3 = drivers.find((*it1)->getDriver());
        if (it3 != drivers.end()) {
            if (!(*it3)->ownsVehicle((*it1)->getMatricula())) {
                (*it3)->addVehicle((*it1)->getMatricula());
                (*it3)->print();
            }
            (*it1)->setDriver(*it3);
        }
        else
            drivers.insert((*it1)->getDriver());
        for (it = highways.begin(); it != highways.end(); it++) {
            if ((*it)->getName() == p->getHighWay()) {
                (*it)->enterVehicle(*it1, p, false);
                found = true;
            }
        }
        if (!found) throw PortagemDoesNotExist(p->getName());
    }
}

std::vector<Driver*> CentralPortagens::getDriversVector() const {
    std::vector<Driver*> v;
    for (auto& d : drivers) v.push_back(d);
    return v;
}

std::vector<Driver*> CentralPortagens::getMbDriversVector() const {
    std::vector<Driver*> v;
    for (auto& d : missbDrivers) v.push_back(d);
    return v;
}

std::vector<Intervention> CentralPortagens::getInterventionsVector() const {
    std::vector<Intervention> v;
    for (BSTiterator<Intervention> it = interventions.begin(); !(it == interventions.end()); it++)
        v.push_back(*it);
    return v;
}

std::vector<Technician*> CentralPortagens::getTechs() const {
    std::vector<Technician*> v;
    for (auto& p : portagensE) {
        std::priority_queue<Technician*> temp = p->getTechs();
        while (!temp.empty()) {
            v.push_back(temp.top());
            temp.pop();
        }
    }
    for (auto& p : portagensS) {
        std::priority_queue<Technician*> temp = p->getTechs();
        while (!temp.empty()) {
            v.push_back(temp.top());
            temp.pop();
        }
    }
    return v;
}

HighWay* CentralPortagens::findHighWay(std::string name) {
    std::vector<HighWay*>::const_iterator it;
    for (it = highways.begin(); it != highways.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw HighWayDoesNotExist(name);
}

PortagemEntrada* CentralPortagens::findPortE(std::string name) {
    std::vector<PortagemEntrada*>::const_iterator it;
    for (it = portagensE.begin(); it != portagensE.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw PortagemDoesNotExist(name);
}

PortagemSaida* CentralPortagens::findPortS(std::string name) {
    std::vector<PortagemSaida*>::const_iterator it;
    for (it = portagensS.begin(); it != portagensS.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw PortagemDoesNotExist(name);
}

Portagem* CentralPortagens::findPort (std::string name) {
    std::vector<PortagemEntrada*>::iterator it;
    std::vector<PortagemSaida*>::iterator it2;
    for (it = portagensE.begin(); it != portagensE.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    for (it2 = portagensS.begin(); it2 != portagensS.end(); it2++) {
        if((*it2)->getName() == name) return *it2;
    }
    return nullptr;
}

Technician* CentralPortagens::getClosestTech(Portagem *port, Specialty spec) {
    Technician* t = nullptr;
    if (port->getTech(spec) != nullptr) {
        return port->getTech(spec);
    }
    int minDistance = 10000;
    for (auto& p1 : portagensS) {
        int distance = abs(p1->getLocation().km - port->getLocation().km);
        if (distance < minDistance && p1->getHighWay() == port->getHighWay()) {
            if (p1->getTech(spec) != nullptr) {
                minDistance = distance;
                t = p1->getTech(spec);
            }
        }
    }
    return t;
}

Manager* CentralPortagens::findManager(std::string name) {
    std::vector<Manager*>::const_iterator it;
    for (it = managers.begin(); it != managers.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw ManagerDoesNotExist(name);
}

Vehicle* CentralPortagens::findVehicle(std::string matricula) {
    std::vector<Vehicle*>::const_iterator it;
    for (it = vehicles.begin(); it != vehicles.end(); it++) {
        if((*it)->getMatricula() == matricula) return *it;
    }
    throw VehicleNotInTransit(matricula, this->getName());
}

Driver* CentralPortagens::findDriver(std::string name) {
    Driver d(name);
    auto it = drivers.find(&d);
    if (it == drivers.end()) throw DriverNotFound(name);
    return *it;
}

std::vector<Intervention> CentralPortagens::findIntervention(std::string port, int year, int month, int day,
                                                float duration, std::string spec) {
    std::vector<Intervention> v;
    Specialty s;
    if (spec == "Revision") s = Revision;
    else if (spec == "Electronics") s = Electronics;
    else if (spec == "Informatics") s = Informatics;
    else throw SpecialtyInvalid(spec);
    Intervention i(day, month, year, duration, nullptr, port, s);
    for (BSTiterator<Intervention> it = interventions.begin(); !(it == interventions.end()); it++) {
        if ((*it) == i) v.push_back(*it);
    }
    if (v.empty()) throw InterventionDoesNotExist();
    return v;
}

bool CentralPortagens::findVehicleBoolean(std::string matricula) {
    std::vector<Vehicle*>::const_iterator it;
    for (it = vehicles.begin(); it != vehicles.end(); it++) {
        if((*it)->getMatricula() == matricula) return true;
    }
    return false;
}

Worker* CentralPortagens::findWorker(std::string name) {
    std::vector<Worker*>::const_iterator it;
    for (it = workers.begin(); it != workers.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw WorkerDoesNotExist(name, this->getName());
}

Worker* CentralPortagens::findWorker(unsigned int ID) {
    std::vector<Worker*>::const_iterator it;
    for (it = workers.begin(); it != workers.end(); it++) {
        if((*it)->getID() == ID) return *it;
    }
    throw WorkerDoesNotExist(ID, this->getName());
}

Technician* CentralPortagens::findTech(std::string name, std::string spec, std::string port) {
    Portagem* p = findPort(port);
    if (p == nullptr) throw PortagemDoesNotExist(port);
    Technician* t = p->findTech(name, spec);
    if (t == nullptr) throw TechnicianNotFound(name, spec, port);
    return t;
}

void CentralPortagens::sortPortagens() {
    std::vector<HighWay*>::iterator it;
    for (it = highways.begin(); it != highways.end(); it++)
        (*it)->sortPortagens();
}

void CentralPortagens::sortHighways() {
    std::sort(highways.begin(), highways.end());
}

void CentralPortagens::printHighways() {
    std::cout << "Highways:\n";
    for (auto& h : highways)
        h->print();
    std::cout << std::endl;
}

void CentralPortagens::printTechs() const {
    std::cout << "Techs:\n";
    for (auto& p : portagensS) {
        if (p->getTechs().size())
            p->printTechs();
    }
    for (auto& p : portagensE) {
        if (p->getTechs().size())
            p->printTechs();
    }
    std::cout << std::endl;
}

void CentralPortagens::printInterventions() const {
    std::cout << "Interventions:\n";
    for (BSTiterator<Intervention> it = interventions.begin(); !(it == interventions.end()); it++)
        (*it).print();
    std::cout << std::endl;
}

void CentralPortagens::printWorkers() {
    std::cout << "Workers:\n";
    for (auto& w : workers)
        w->print();
    std::cout << std::endl;
}

void CentralPortagens::printPortagens() {
    std::cout << "Entry ports:\n";
    for (auto& p : portagensE)
        p->print();
    std::cout << "\nExit ports:\n";
    for (auto& p : portagensS)
        p->print();
    std::cout << std::endl;
}

void CentralPortagens::printCurrentVehicles() {
    std::cout << "Current Vehicles:\n";
    for (auto& v : vehicles)
        v->print();
    std::cout << std::endl;
}

void CentralPortagens::printDrivers() {
    std::cout << "Drivers:\n";
    for (auto& driver : drivers)
        driver->print();
    std::cout << std::endl;
}

void CentralPortagens::printMissbehavedDrivers() {
    std::cout << "Missbehaved Drivers:\n";
    for (auto& driver : missbDrivers)
        driver->print();
    std::cout << std::endl;
}

void CentralPortagens::printManagers() {
    std::cout << "Managers:\n";
    for (auto& man : managers)
        man->print();
    std::cout << std::endl;
}

void CentralPortagens::assignPortagens() {
    std::vector<PortagemEntrada*>::const_iterator it1;
    std::vector<HighWay*>::iterator it2;
    for (it1 = portagensE.begin(); it1 != portagensE.end(); it1++){
        bool found = false;
        for(it2 = highways.begin(); it2 != highways.end(); it2++){
            if((*it1)->getHighWay() == (*it2)->getName()){
                (*it2)->addPortagemE(*it1);
                found = true;
                break;
            }
        }
        if (!found) throw HighWayDoesNotExist((*it1)->getHighWay());
    }
    std::vector<PortagemSaida*>::const_iterator it3;
    for (it3 = portagensS.begin(); it3 != portagensS.end(); it3++){
        for(it2 = highways.begin(); it2 != highways.end(); it2++){
            if((*it3)->getHighWay() == (*it2)->getName()){
                (*it2)->addPortagemS(*it3);
            }
        }
    }
}

std::ostream &operator <<(std::ostream &o, const CentralPortagens &cp) {
    o << cp.getName() << ":" << std::endl;
    std::vector<HighWay*>::const_iterator it;
    for (it = cp.highways.begin(); it != cp.highways.end(); it++) {
        o << **it << std::endl;
    }
    return o;
}
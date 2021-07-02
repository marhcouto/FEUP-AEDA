#include "Portagem.h"
#include <sstream>
/* ---Portagem Class--- */


float PortagemSaida::totalProfit = 0.0;

Portagem::Portagem(std::string name, GeoLocation location, unsigned int nWays, unsigned int nViaVerde, std::string highway) :
name(name), location(location), nWays(nWays), nViaVerde(nViaVerde), highway(highway) {
    setWays(nWays, nViaVerde);
}

Portagem::~Portagem() {
    for (auto& w : ways)
        delete w;
    while (!techs.empty()) {
        delete techs.top();
        techs.pop();
    }
}

void Portagem::setWays(unsigned int nWays, unsigned int nViaVerde) {
    for(unsigned int i = 1; i <= nWays; i++){
        if(i <= nViaVerde) {
            Way *a = new Way(true, i);
            addWay(a);
        }
        else {
            Way *a = new Way(false, i);
            addWay(a);
        }
    }
}

void Portagem::addTech(Technician* tech) {
    techs.push(tech);
}

void Portagem::removeTech(Technician* t) {
    std::vector<Technician*> temp;
    bool found = false;
    while (!techs.empty()) {
        if (*(techs.top()) == *t) {
            techs.pop();
            break;
        }
        temp.push_back(techs.top());
        techs.pop();
    }
    for (auto t : temp)
        techs.push(t);
    if (!found) throw TechnicianNotFound (name, t->getSpecString(), this->name);
}

Technician* Portagem::getTech (Specialty specialty) {
    std::priority_queue<Technician*> temp;
    while (!temp.empty()) {
        if (temp.top()->getSpec() == specialty) {
            return temp.top();
        }
        temp.pop();
    }
    return nullptr;
}

Technician* Portagem::findTech(std::string name, std::string spec) {
    Specialty s;
    if (spec == "Revision") s = Revision;
    else if (spec == "Informatics") s = Informatics;
    else if (spec == "Electronics") s = Electronics;
    else throw SpecialtyInvalid(spec);
    Technician t(name, s, this->name);
    std::priority_queue<Technician*> temp = techs;
    while (!temp.empty()) {
        if (*(temp.top()) == t) {
            return temp.top();
        }
        temp.pop();
    }
    throw TechnicianNotFound(name, spec, this->name);
    return nullptr;
}

Way* Portagem::findWay(unsigned int number) {
    std::vector<Way*>::const_iterator it;
    for (it = ways.begin(); it != ways.end(); it++) {
        if ((*it)->getNumber() == number) return *it;
    }
    throw WayDoesNotExist(this->name, number);
}

Worker* PortagemSaida::findWorker(std::string name) {
    std::vector<Worker*>::const_iterator it;
    for (it = workers.begin(); it != workers.end(); it++) {
        if((*it)->getName() == name) return *it;
    }
    throw WorkerDoesNotExist(name, this->name);
}

Worker* PortagemSaida::findWorker(unsigned int ID) {
    std::vector<Worker*>::const_iterator it;
    for (it = workers.begin(); it != workers.end(); it++) {
        if((*it)->getID() == ID) return *it;
    }
    throw WorkerDoesNotExist(ID, this->name);
}

void PortagemSaida::printWorkers() {
    std::cout << "Workers: ";
    for (auto& w : workers)
        std::cout << w->getName() << " ";
    std::cout << std::endl;
}

void PortagemSaida::print() const {
    std::cout << "Name: " << name << " | " << "Highway: " << highway << "Km: " << location.km << " | ";
    std::cout << "Number of ways: " << nWays << " | " << "of which viaverde: " << nViaVerde << " | ";
    std::cout << "Profit: " << localProfit << " | " << "Type: exit\n";
}

void Portagem::sortWays() {
    std::sort(ways.begin(), ways.end());
}

void Portagem::print() const {
    std::cout << "Name: " << name << " | " << "Highway: " << highway << "Km: " << location.km << " | ";
    std::cout << "Number of ways: " << nWays << " | " << "of which viaverde: " << nViaVerde << std::endl;
}

void Portagem::printTechs() const {
    std::cout << name << "'s technicians: ";
    std::priority_queue<Technician*> temp = techs;
    while (!temp.empty()) {
        temp.top()->print();
        temp.pop();
    }
    std::cout << std::endl;
}

void PortagemSaida::setWorkers(std::vector<Worker *> w) {
    workers = w;
}

void Portagem::setWays(std::vector<Way *> ways) {
    this->ways = ways;
}

void Portagem::addWay(Way *way) {
    ways.push_back(way);
}

void PortagemSaida::addWorker(Worker *worker) {
    worker->setPort(this->getName());
    worker->setHighway(this->getHighWay());
    worker->setActive(true);
    workers.push_back(worker);
}

void PortagemSaida::removeWorker(Worker *worker) {
    std::vector<Worker*>::iterator it = std::find(workers.begin(), workers.end(), worker);
    if (it == workers.end()) throw WorkerDoesNotExist(worker->getName(), this->name);
    worker->setPort("-");
    worker->setHighway("-");
    worker->setActive(false);
    workers.erase(it);
}

void PortagemSaida::assignWorkers(){
    std::vector<Worker*>::iterator it1 = workers.begin();
    std::vector<Way*>::const_iterator it2;
    for(it2 = ways.begin(); it2 != ways.end(); it2++){
        if(!(*it2)->getVV()){
            if(it1 == workers.end()) throw NotEnoughWorkers();
            (*it1)->setActive(true);
            (*it2)->setWorker(*it1);
            it1++;
        }
    }
}

void PortagemSaida::changeWorker(std::string name, Worker *newWorker) {
    if (!this->changeWorker(this->findWorker(name), newWorker))
        throw WorkerDoesNotExist(name, this->name);
}

bool PortagemSaida::changeWorker(Worker *oldWorker, Worker *newWorker) {
    bool found = false;
    std::vector<Way*>::iterator it1;
    for (it1 = ways.begin(); it1 != ways.end(); it1++) {
        if ((*it1)->getWorker() == oldWorker) {
            (*it1)->changeWorker(newWorker);
            found = true;
        }
    }
    if (found) {
        this->removeWorker(oldWorker);
        this->addWorker(newWorker);
    }
    return found;
}

Way* Portagem::getBestWay(bool preference) {
    std::vector<Way*>::const_iterator it, itl = ways.begin();
    for (it = ways.begin(); it != ways.end(); it++) {
        if ((*it)->getVV() == preference) {
            if ((*itl)->getVV() != preference || (*it)->getOccupancy() < (*itl)->getOccupancy())
                itl = it;
        }
    }
    return *itl;
}

void PortagemEntrada::enterVehicle(Vehicle *v, bool write) {
    unsigned int nWay = getBestWay(v->getPrefers())->processVehicle(v);
    v->setEntryPort(this->name);
    v->setEntryKm(this->location.km);
    if (write) {
        std::cout << "Vehicle " << v->getMatricula() << " entered successfully in " << this->highway <<
                  " through " << this->name << std::endl;
    }
    time_t now = time(0);
    std::string date = ctime(&now);
    tm *ltm = localtime(&now);
    std::ofstream f;
    float currentHour = ltm->tm_hour;
    float currentMin = ltm->tm_min;
    v->setEntryTime(currentHour + currentMin / 60);
    if (write) {
        f.open("Registry.txt", std::ios::out | std::ios::app);
        f << "Vehicle:" << v->getMatricula() << " entered highway:" << this->highway
          << " via number:" << nWay << " port:" << this->name << " date:" << date << std::endl;
        f.close();
    }
}

void PortagemEntrada::print() const {
    std::cout << "Name: " << name << " | " << "Highway: " << highway << "Km: " << location.km << " | ";
    std::cout << "Number of ways: " << nWays << " | " << "of which viaverde: " << nViaVerde << " | ";
    std::cout << "Type: entry\n";
}

bool PortagemSaida::exitVehicle(Vehicle *v) {
    bool missbehavedVehicle = false;
    unsigned int nWay = getBestWay(v->getPrefers())->processVehicle(v);
    time_t now = time(0);
    std::string date = ctime(&now);
    tm *ltm = localtime(&now);
    float currentHour = ltm->tm_hour;
    float currentMin = ltm->tm_min;
    float travelTime = (currentHour + currentMin / 60) - v->getEntryTime();
    float travelDistance = this->getLocation().km - v->getEntryKm();
    float travelSpeed = travelTime / travelDistance;
    if (v->getClass() == 1 && travelSpeed > 130) missbehavedVehicle = true;
    if (v->getClass() == 2 && travelSpeed > 120) missbehavedVehicle = true;
    if (v->getClass() == 3 && travelSpeed > 110) missbehavedVehicle = true;
    if (v->getClass() == 4 && travelSpeed > 100) missbehavedVehicle = true;
    float payment = travelDistance * v->getFee();
    v->setExitPort(this->getName());
    this->incrementProfit(payment);
    PortagemSaida::incrementTotalProfit(payment);
    std::cout << "Vehicle " << v->getMatricula() << " exit successfully from " << this->highway <<
              " through " << this->name << std::endl;
    std::ofstream f;
    f.open("Registry.txt", std::ios::out | std::ios::app);
    f << "Vehicle:" << v->getMatricula() << " highway:" << " distance travelled:" << travelDistance
    << this->highway << " via:" << nWay << " port:" << this->name << " date:" << date << " paid:" <<
    payment << " current total profit:" << PortagemSaida::getTotalProfit() << std::endl;
    f.close();
    return missbehavedVehicle;
}

bool Portagem::operator==(const Portagem &portagem) const {
    return name == portagem.name && portagem.location.location == location.location
    && portagem.location.km == location.km;
}

bool Portagem::operator<(const Portagem &portagem) const {
    return location.km < portagem.location.km;
}

std::ostream &operator <<(std::ostream &o, const PortagemSaida &p) {
    o << p.getName() << " " << p.location.location << " " << p.location.km  << " " <<
      p.nWays << " " << p.nViaVerde << " " << p.highway << " " << p.localProfit;
    return o;
}

std::ostream &operator <<(std::ostream &o, const PortagemEntrada &p) {
    o << p.getName() << " " << p.location.location << " " << p.location.km << " " <<
    p.nWays << " " << p.nViaVerde << " " << p.highway;
    return o;
}

std::istream& operator>>(std::istream& is, PortagemEntrada& p) {
    is >> p.name >> p.location.location >> p.location.km >> p.nWays >> p.nViaVerde >> p.highway;
    return is;
}

std::istream& operator>>(std::istream& is, PortagemSaida& p) {
    is >> p.name >> p.location.location >> p.location.km >> p.nWays >> p.nViaVerde >> p.highway >> p.localProfit;
    return is;
}



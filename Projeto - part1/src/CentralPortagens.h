#ifndef UNTITLED2_CENTRALPORTAGENS_H
#define UNTITLED2_CENTRALPORTAGENS_H

#include "HighWay.h"
#include <unordered_set>
#include "Intervention.h"
#include "BST.h"

struct DriversHash{
    int operator() (const Driver* d) const {
        int hash = 0;
        for (auto letter : d->getName())
            hash = hash*37 + letter;
        return hash;
    }

    bool operator() (const Driver* d1, const Driver* d2) const {
        return *d1 == *d2;
    }
};

typedef std::unordered_set<Driver*, DriversHash, DriversHash> DriversHT;


class CentralPortagens {
    std::string name;
    std::vector<HighWay*> highways;
    std::vector<Worker*> workers;
    std::vector<PortagemEntrada*> portagensE;
    std::vector<PortagemSaida*> portagensS;
    std::vector<Vehicle*> vehicles;
    std::vector<Manager*> managers;
    DriversHT drivers;
    DriversHT missbDrivers;
    BST<Intervention> interventions;
    static unsigned int nextID;
    friend void readVehiclesFile(std::vector<Vehicle*> &vehicles);
public:
    CentralPortagens(std::string name) : name (name), interventions
    (Intervention(0, 0, 0, 0, nullptr, "", Revision)) {};
    ~CentralPortagens();
    std::string getName() const {return name;}
    void setHighWays(std::vector<HighWay*> highways);
    void setVehicles(std::vector<Vehicle*> vehicles);
    void setPortagensE(std::vector<PortagemEntrada*> portagens);
    void setPortagensS(std::vector<PortagemSaida*> portagens);
    void setWorkers(std::vector<Worker*> workers);
    void setManagers(std::vector<Manager*> managers);
    void setDrivers(const DriversHT& drivers);
    void setDrivers(const std::vector<Driver*>& drivers);
    void setIntervs (const BST<Intervention>& interventions);
    void setMissbDrivers (const DriversHT& drivers);
    void setMissbDrivers (const std::vector<Driver*>& drivers);
    void addPortagemE(PortagemEntrada* portagem, HighWay *highway);
    void addPortagemS(PortagemSaida* portagem, HighWay *highway);
    void addWorker(Worker* worker);
    void addVehicle(Vehicle *vehicle);
    void addDriver(Driver* driver);
    void addIntervention(int year, int day, int month, int duration, std::string type, std::string port);
    void addIntervention(Intervention i);
    void addMissbehavedVehicle(Vehicle *vehicle);
    void addMissbehavedDriver(Driver* d);
    void removeDriver(std::string name);
    void removeMissbehavedDriver(std::string name);
    void removeIntervention(int day, int month, int year, int duration, std::string type, std::string port);
    void removeVehicle(Vehicle* vehicle);
    void fireWorker(std::string name);
    void hireWorker(Worker *w);
    void hireTechnician(Technician* t);
    void fireTechnician(Technician* t);
    std::vector<HighWay*> getHighways() const {return highways;}
    std::vector<Worker*> getWorkers() const {return workers;}
    std::vector<Vehicle*> getVehicles() const {return vehicles;}
    std::vector<PortagemEntrada*> getPortagensE() const {return portagensE;}
    std::vector<PortagemSaida*> getPortagensS() const {return portagensS;}
    std::vector<Manager*> getManagers() const {return managers;}
    std::vector<Driver*> getDriversVector() const;
    std::vector<Driver*> getMbDriversVector() const;
    std::vector<Intervention> getInterventionsVector() const;
    DriversHT getDrivers() const {return drivers;}
    DriversHT getmbDrivers() const {return missbDrivers;}
    BST<Intervention> getInterventions() const {return interventions;}
    std::vector<Technician*> getTechs() const;
    HighWay * findHighWay(std::string name);
    PortagemEntrada* findPortE(std::string name);
    PortagemSaida* findPortS(std::string name);
    Portagem* findPort(std::string name);
    Technician* getClosestTech(Portagem* port, Specialty spec);
    Manager* findManager(std::string name);
    Vehicle* findVehicle(std::string matricula);
    Driver* findDriver(std::string name);
    std::vector<Intervention> findIntervention(std::string port, int year, int month, int day, float duration, std::string spec);
    bool findVehicleBoolean(std::string matricula);
    Worker* findWorker(std::string name);
    Worker* findWorker(unsigned int ID);
    Technician* findTech(std::string name, std::string spec, std::string port);
    static unsigned int getNextID() {return nextID;}
    void assignWorkers ();
    void assignPortagens ();
    void assignVehicles ();
    void assignTechs (const std::vector<Technician*>& techs);
    void assignIntervs (const std::vector<Technician*>& techs);
    static void incrementNextID() {nextID++;}
    void changeWorker(std::string oldWorkerName, std::string newWorkerName);
    void changeWorker(Worker *oldWorker, Worker *newWorker);
    void enterVehicle(Vehicle *v, std::string pName, std::string hName);
    void exitVehicle(Vehicle *v, std::string pName, std::string hName);
    void exitVehicle(std::string vMatricula, std::string pName, std::string hName);
    void printTechs() const;
    void printInterventions() const;
    void printWorkers();
    void printHighways();
    void printPortagens();
    void printCurrentVehicles();
    void printMissbehavedVehicles();
    void printManagers();
    void printDrivers();
    void printMissbehavedDrivers();
    void sortPortagens();
    void sortHighways();
    friend std::ostream &operator <<(std::ostream &o, const CentralPortagens &cp);



};




#endif //UNTITLED2_CENTRALPORTAGENS_H

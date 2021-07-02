#ifndef UNTITLED2_WORKER_H
#define UNTITLED2_WORKER_H

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include "Utilities.h"

class Person {
protected:
    std::string name;
public:
    Person() {};
    Person(std::string name) : name(name) {};
    std::string getName() const {return name;}
    void setName(std::string name) {this->name = name;}
    virtual bool operator== (const Person& p) const;
};

class Driver : public Person {
    std::vector<std::string> vehicles;
public:
    Driver() {};
    Driver(std::string name, std::vector<std::string> vehicles = {}) : Person (name), vehicles(vehicles) {};
    std::vector<std::string> getVehicles () const {return vehicles;}
    void setVehicles (std::vector<std::string> vehicles);
    void addVehicle (std::string vehicle);
    void removeVehicle (std::string vehicle);
    void print() const;
    bool ownsVehicle (std::string licensePlate) const;
    friend std::ostream& operator<< (std::ostream& os, const Driver& d);
    friend std::istream& operator>> (std::istream& is, Driver& d);
};

class Technician : public Person {
    Specialty specialty;
    int interventions;
    float timeWorking;
    std::string port;
public:
    Technician() {};
    Technician(std::string name, Specialty specialty, std::string port, int interventions = 0, float time = 0) :
            Person (name), specialty(specialty), interventions(interventions), timeWorking(time), port (port) {};
    Specialty getSpec() const {return specialty;}
    std::string getSpecString () const;
    std::string getPort() const {return port;}
    int getInterventions() const {return interventions;}
    float getTime() const {return timeWorking;}
    float getAverageTime() const;
    void print() const;
    void addExperience(int timeWorked);
    void operator++ ();
    bool operator< (const Technician& tech) const;
    bool operator== (const Technician& tech) const;
    friend std::ostream& operator<< (std::ostream& os, const Technician& tech);
    friend std::istream& operator>> (std::istream& is, Technician& tech);
};

class Worker : public Person {
    std::string port, highway;
    unsigned int workerID, salary;
    bool active;
public:
    Worker() {};
    Worker(std::string name, unsigned int ID, unsigned int salary, bool active, std::string port, std::string highway) : Person(name),
    active(active), workerID(ID), salary(salary), port(port), highway(highway) {};
    bool operator==(const Worker &worker) const;
    void print();
    void setActive(bool a);
    void setWorkerID(unsigned int ID);
    void setPort(std::string portName);
    void setHighway(std::string highwayName);
    bool getActive() const {return active;}
    std::string getHighway() const {return highway;}
    std::string getPort() const {return port;}
    std::string getActiveString() const;
    unsigned int getID() const {return workerID;}
    void print() const;
    friend std::ostream& operator<< (std::ostream &o, const Worker &w);
    friend std::istream& operator>> (std::istream& is, Worker& w);
};

class Manager : public Person {
    std::string password;
public:
    Manager() {};
    Manager (std::string name, std::string password) : Person(name), password(password) {};
    std::string getPassword() const {return password;}
    void changePassword(std::string newPassword);
    void print() const;
    friend std::ostream &operator << (std::ostream &o, const Manager &m);
    friend std::istream& operator>> (std::istream& is, Manager& m);
};

#endif //UNTITLED2_WORKER_H

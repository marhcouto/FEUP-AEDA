#ifndef UNTITLED2_WORKER_H
#define UNTITLED2_WORKER_H

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include "Utilities.h"
///Class de Pessoas
class Person {
protected:
    std::string name;
public:
    Person() {};
    ///Construtor class Person
    Person(std::string name) : name(name) {};
    ///Retona o nome da pessoa
    std::string getName() const {return name;}
    ///Define o nome da pessoa
    void setName(std::string name) {this->name = name;}
    virtual bool operator== (const Person& p) const;
};
///Class condutor
class Driver : public Person {
    std::vector<std::string> vehicles;
public:
    Driver() {};
    ///Construtor class condutor
    Driver(std::string name, std::vector<std::string> vehicles = {}) : Person (name), vehicles(vehicles) {};
    ///Retorna o vector vehicles
    std::vector<std::string> getVehicles () const {return vehicles;}
    ///Define o vector vehicles
    void setVehicles (std::vector<std::string> vehicles);
    ///Adicionar um veículo ao vector de veículos
    void addVehicle (std::string vehicle);
    ///Remove um veículo do vector de veículos
    void removeVehicle (std::string vehicle);
    ///Imprime os membros da class
    void print() const;
    ///Retorna verdadeiro se o condutor for dono do carro com matrícula (licensePlate) e falso caso contrário
    bool ownsVehicle (std::string licensePlate) const;
    friend std::ostream& operator<< (std::ostream& os, const Driver& d);
    friend std::istream& operator>> (std::istream& is, Driver& d);
};
///Class técnico
class Technician : public Person {
    Specialty specialty;
    int interventions;
    float timeWorking;
    std::string port;
public:
    Technician() {};
    ///Construtor da class technician
    Technician(std::string name, Specialty specialty, std::string port, int interventions = 0, float time = 0) :
            Person (name), specialty(specialty), interventions(interventions), timeWorking(time), port (port) {};
    ///Retorna Especialidade do técnico
    Specialty getSpec() const {return specialty;}
    ///Retorna especialidade em string
    std::string getSpecString () const;
    ///Retorna portagem em que trabalha
    std::string getPort() const {return port;}
    ///Retorna intervenção
    int getInterventions() const {return interventions;}
    ///Retorna o tempo de trabalho
    float getTime() const {return timeWorking;}
    ///Retorna o tempo médio de um trabalho
    float getAverageTime() const;
    ///Imprime os membros da class
    void print() const;
    ///Adiciona tempo de trabalho
    void addExperience(int timeWorked);
    void operator++ ();
    bool operator< (const Technician& tech) const;
    bool operator== (const Technician& tech) const;
    friend std::ostream& operator<< (std::ostream& os, const Technician& tech);
    friend std::istream& operator>> (std::istream& is, Technician& tech);
};
///Class trabalhador
class Worker : public Person {
    std::string port, highway;
    unsigned int workerID, salary;
    bool active;
public:
    Worker() {};
    ///Construtor class Worker
    Worker(std::string name, unsigned int ID, unsigned int salary, bool active, std::string port, std::string highway) : Person(name),
    active(active), workerID(ID), salary(salary), port(port), highway(highway) {};
    bool operator==(const Worker &worker) const;
    ///Imprime membros da class
    void print();
    ///Define se o trabalhador está ativo
    void setActive(bool a);
    ///Define o ID do trabalhador
    void setWorkerID(unsigned int ID);
    ///Define a portagem onde o trabalhador trabalha
    void setPort(std::string portName);
    ///Define a auto-estrada onde o trabalhador trabalha
    void setHighway(std::string highwayName);
    ///Retona se o trabalhador está a trabalhar ou não
    bool getActive() const {return active;}
    ///Retorna a auto-estrada onde o trabalhador está
    std::string getHighway() const {return highway;}
    ///Retorna a portagem onde o trabalhador está
    std::string getPort() const {return port;}
    ///Retona se o trabalhador está a trabalhar ou não em string
    std::string getActiveString() const;
    ///Retorna o ID do trabalhador
    unsigned int getID() const {return workerID;}
    void print() const;
    friend std::ostream& operator<< (std::ostream &o, const Worker &w);
    friend std::istream& operator>> (std::istream& is, Worker& w);
};
///Class de Manager
class Manager : public Person {
    std::string password;
public:
    Manager() {};
    ///Contrutor da class Manager
    Manager (std::string name, std::string password) : Person(name), password(password) {};
    ///Retorna a password do Manager
    std::string getPassword() const {return password;}
    ///Muda a password do Manager
    void changePassword(std::string newPassword);
    ///Imprime os membros da class
    void print() const;
    friend std::ostream &operator << (std::ostream &o, const Manager &m);
    friend std::istream& operator>> (std::istream& is, Manager& m);
};

#endif //UNTITLED2_WORKER_H

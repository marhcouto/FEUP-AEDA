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

///Class geral com a base de todos os dados
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
    ///construtor da class CentralPortagens
    CentralPortagens(std::string name) : name (name), interventions
    (Intervention(0, 0, 0, 0, nullptr, "", Revision)) {};
    ///destrutor da class CentralPortagens
    ~CentralPortagens();
    ///retorna o nome do objeto desta class
    std::string getName() const {return name;}
    ///Define o vector de auto-estradas (highways)
    void setHighWays(std::vector<HighWay*> highways);
    ///Define o vector de veículos (vehicles)
    void setVehicles(std::vector<Vehicle*> vehicles);
    ///Define o vector de portagens de entrada (portagensE)
    void setPortagensE(std::vector<PortagemEntrada*> portagens);
    ///Define o vector de portagens de saída (portagensS)
    void setPortagensS(std::vector<PortagemSaida*> portagens);
    ///Define o vector de trabalhadores (workers)
    void setWorkers(std::vector<Worker*> workers);
    ///Define o vector de managers (managers)
    void setManagers(std::vector<Manager*> managers);
    ///Define a tabela de dispersão de condutores (drivers)
    void setDrivers(const DriversHT& drivers);
    ///Define o vector de condutores (drivers)
    void setDrivers(const std::vector<Driver*>& drivers);
    ///Define a árvore binária de intervenções (interventions)
    void setIntervs (const BST<Intervention>& interventions);
    ///Define na tabela de dispersão os condutores que infringiram a lei
    void setMissbDrivers (const DriversHT& drivers);
    ///Define no vector os condutores que infringiram a lei
    void setMissbDrivers (const std::vector<Driver*>& drivers);
    ///Adiciona uma portagem de entrada a uma autoestrada
    void addPortagemE(PortagemEntrada* portagem, HighWay *highway);
    ///Adiciona uma portagem de saída a uma autoestrada
    void addPortagemS(PortagemSaida* portagem, HighWay *highway);
    ///Adiciona um trabalhador ao vector de trabalhadores (workers)
    void addWorker(Worker* worker);
    ///Adiciona um veículo ao vector de veículos (vehicles)
    void addVehicle(Vehicle *vehicle);
    ///Adiciona um condutor à tabela de dispersão
    void addDriver(Driver* driver);
    ///Adiciona uma intervenção à árvore binária
    void addIntervention(int year, int day, int month, int duration, std::string type, std::string port);
    ///Adiciona uma intervenção à árvore binária
    void addIntervention(Intervention i);
    ///Adiciona à tabela de dispersão um condutor que infringiu a lei
    void addMissbehavedVehicle(Vehicle *vehicle);
    ///Adiciona ao vector um condutor que infringiu a lei
    void addMissbehavedDriver(Driver* d);
    ///Remove o condutor de nome(name) da tabela de dispersão
    void removeDriver(std::string name);
    ///Remove o condutor que infrigiu a lei de nome (name) da tabela de dispersão
    void removeMissbehavedDriver(std::string name);
    ///Remove intervenção da àrvore binária
    void removeIntervention(int day, int month, int year, int duration, std::string type, std::string port);
    ///Remove um veículo do vector vehicles
    void removeVehicle(Vehicle* vehicle);
    ///Despedir o trabalhador de nome (name)
    void fireWorker(std::string name);
    ///Contratar o trabalhador de nome (name)
    void hireWorker(Worker *w);
    ///Contratar o técnico t
    void hireTechnician(Technician* t);
    ///Despedir o técnico t
    void fireTechnician(Technician* t);
    ///Retorna o vector de auto-estradas
    std::vector<HighWay*> getHighways() const {return highways;}
    ///Retorna o vector de trabalhadores
    std::vector<Worker*> getWorkers() const {return workers;}
    ///Retorna o vector de veículos
    std::vector<Vehicle*> getVehicles() const {return vehicles;}
    ///Retorna o vector de portadens de entrada
    std::vector<PortagemEntrada*> getPortagensE() const {return portagensE;}
    ///Retorna o vector de portagens de saída
    std::vector<PortagemSaida*> getPortagensS() const {return portagensS;}
    ///Retorna o vector de managers
    std::vector<Manager*> getManagers() const {return managers;}
    ///Retorna o vector de condutores
    std::vector<Driver*> getDriversVector() const;
    ///Retorna o vector de condutores que infrigiram a lei
    std::vector<Driver*> getMbDriversVector() const;
    ///Retorna o vector de intervenções
    std::vector<Intervention> getInterventionsVector() const;
    ///Retorna a tabela de dispersão de condutores
    DriversHT getDrivers() const {return drivers;}
    ///Retorna a tabela de dispersão de condutores que infrigiram a lei
    DriversHT getmbDrivers() const {return missbDrivers;}
    ///Retorna a árvore binária de intervenções
    BST<Intervention> getInterventions() const {return interventions;}
    ///Retorna o vector de técnicos
    std::vector<Technician*> getTechs() const;
    ///Procurar a autoestrada de nome (name)
    HighWay * findHighWay(std::string name);
    ///Procurar a portagem de entrada de nome (name)
    PortagemEntrada* findPortE(std::string name);
    ///Procurar a portagem de saída de nome (name)
    PortagemSaida* findPortS(std::string name);
    ///Procurar a portagem de nome (name)
    Portagem* findPort(std::string name);
    ///Retorna o técnico mais próximo
    Technician* getClosestTech(Portagem* port, Specialty spec);
    ///Procurar o manager de nome (name)
    Manager* findManager(std::string name);
    ///Procurar o veículo com a matricula (matricula)
    Vehicle* findVehicle(std::string matricula);
    ///Procurar o condutor de nome (name)
    Driver* findDriver(std::string name);
    ///Procurar a itervenção
    std::vector<Intervention> findIntervention(std::string port, int year, int month, int day, float duration, std::string spec);
    ///Procurar o estado do veículo
    bool findVehicleBoolean(std::string matricula);
    ///Procurar o trabalhador de nome (name)
    Worker* findWorker(std::string name);
    ///Procurar o trabalhador com ID (ID)
    Worker* findWorker(unsigned int ID);
    ///Procurar técnico com nome (name), especificação (spec) e porta (port)
    Technician* findTech(std::string name, std::string spec, std::string port);
    ///Retorna o ID do próximo trabalhador a ser criado
    static unsigned int getNextID() {return nextID;}
    ///Distribui os trabalhadores
    void assignWorkers ();
    ///Distribui as portagens
    void assignPortagens ();
    ///Distribui os veículos
    void assignVehicles ();
    ///Distribui os técnicos
    void assignTechs (const std::vector<Technician*>& techs);
    ///Distribui as intervenções
    void assignIntervs (const std::vector<Technician*>& techs);
    ///Incrementa o membro nextID
    static void incrementNextID() {nextID++;}
    ///Substitui um trabalhador antigo por um novo
    void changeWorker(std::string oldWorkerName, std::string newWorkerName);
    ///Substitui um trabalhador antigo por um novo
    void changeWorker(Worker *oldWorker, Worker *newWorker);
    ///Dar entrada ao veículo (v) na portagem (p) da autoestrada (h)
    void enterVehicle(Vehicle *v, std::string pName, std::string hName);
    ///Dar saída ao veículo (v) na portagem de nome (pName) da autoestrada de nome (hName)
    void exitVehicle(Vehicle *v, std::string pName, std::string hName);
    ///Dar saída ao veículo de matricula (vMatricula) na portagem de nome (pName) da autoestrada de nome (hName)
    void exitVehicle(std::string vMatricula, std::string pName, std::string hName);
    ///Imprime os técnicos
    void printTechs() const;
    ///Imprime as intervenções
    void printInterventions() const;
    ///Imprime os trabalhadores
    void printWorkers();
    ///Imprime as Auto-estradas
    void printHighways();
    ///Imprime as portagens
    void printPortagens();
    ///Imprime os veículos
    void printCurrentVehicles();
    ///Imprime os Managers
    void printManagers();
    ///Imprime os condutores
    void printDrivers();
    ///Imprime os condutores que infringiram as regras
    void printMissbehavedDrivers();
    ///Ordena as portagens
    void sortPortagens();
    ///Ordena as autoestradas
    void sortHighways();
    friend std::ostream &operator <<(std::ostream &o, const CentralPortagens &cp);



};




#endif //UNTITLED2_CENTRALPORTAGENS_H

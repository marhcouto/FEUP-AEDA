#ifndef UNTITLED2_PORTAGEM_H
#define UNTITLED2_PORTAGEM_H

#include <iostream>
#include <vector>
#include "Way.h"
#include <algorithm>
#include <fstream>
#include <ctime>
#include <queue>

struct GeoLocation{
    float km;
    std::string location;
};

/* ---Class Portagem--- */
class Portagem {
protected:
    std::string name, highway;
    GeoLocation location;
    unsigned int nWays, nViaVerde;
    std::vector<Way*> ways;
    std::priority_queue<Technician*> techs;
public:
    Portagem() {};
    Portagem(std::string name, GeoLocation location, unsigned int nWays,
             unsigned int nViaVerde, std::string highway);
    ~Portagem();
    std::string getName () const {return name;}
    std::string getHighWay () const {return highway;}
    GeoLocation getLocation () const {return location;}
    std::vector <Way*> getWays () const {return ways;}
    std::priority_queue<Technician*> getTechs () const {return techs;}
    void setWays (std::vector<Way*> ways);
    void setWays (unsigned int nWays, unsigned int nViaVerde);
    void addWay (Way *way);
    void addTech (Technician* tech);
    void removeTech (Technician* t);
    Technician* getTech (Specialty specialty);
    Technician* findTech (std::string name, std::string spec);
    void sortWays();
    virtual void print() const;
    void printTechs() const;
    unsigned int getVV () const {return nViaVerde;}
    unsigned int getNWays () const {return nWays;}
    Way* findWay (unsigned int number);
    Way* getBestWay (bool preference);
    bool operator== (const Portagem &portagem) const;
    bool operator< (const Portagem &portagem) const;
};

class PortagemEntrada : public Portagem {
public:
    PortagemEntrada() : Portagem() {};
    PortagemEntrada(std::string name, GeoLocation location, unsigned int nWays, unsigned int nViaVerde,
            std::string highway) : Portagem(name, location, nWays, nViaVerde, highway) {};
    void enterVehicle(Vehicle *v, bool write);
    void print() const;
    friend std::ostream &operator <<(std::ostream &o, const PortagemEntrada &p);
    friend std::istream &operator >>(std::istream &is, PortagemEntrada& p);
};

class PortagemSaida : public Portagem {
    std::vector<Worker*> workers;
    float localProfit;
    static float totalProfit;
public:
    PortagemSaida() : Portagem() {};
    PortagemSaida(std::string name, GeoLocation location, unsigned int nWays, unsigned int nViaVerde,
                  std::string highway, float profit) : Portagem(name, location, nWays, nViaVerde, highway),
                  localProfit(profit) {};
    std::vector<Worker*> getWorkers() const {return workers;}
    float getProfit() const {return localProfit;}
    void setWorkers(std::vector<Worker*> w);
    void addWorker(Worker *worker);
    void removeWorker(Worker *worker);
    void changeWorker(std::string name, Worker *newWorker);
    bool changeWorker(Worker *oldWorker, Worker *newWorker);
    void assignWorkers();
    void printWorkers();
    void print() const;
    void incrementProfit(float val) {localProfit += val;}
    static void incrementTotalProfit(float val) {totalProfit += val;}
    static float getTotalProfit() {return totalProfit;}
    bool exitVehicle (Vehicle *v);
    Worker* findWorker(std::string name);
    Worker* findWorker(unsigned int ID);
    friend std::ostream &operator <<(std::ostream &o, const PortagemSaida &p);
    friend std::istream &operator >>(std::istream &is, PortagemSaida& p);
};




#endif //UNTITLED2_PORTAGEM_H

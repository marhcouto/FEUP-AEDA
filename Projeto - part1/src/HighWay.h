#ifndef UNTITLED2_HIGHWAY_H
#define UNTITLED2_HIGHWAY_H


#include "Portagem.h"


class HighWay {
    std::vector<Vehicle*> vehiclesInTransit;
    std::vector<PortagemSaida*> portagensS;
    std::vector<PortagemEntrada*> portagensE;
    std::string name;
    float km;
public:
    HighWay() {};
    HighWay(std::string name, float km) : name(name), km(km) {};
    void setPortagensS(std::vector <PortagemSaida*> portagens);
    void setPortagensE(std::vector <PortagemEntrada*> portagens);
    void setVehicles(std::vector <Vehicle*> vehicles);
    void addPortagemE(PortagemEntrada *portagem);
    void addPortagemS(PortagemSaida *portagem);
    void removeVehicle (Vehicle *v1);
    void enterVehicle (Vehicle *v1, std::string namePort, bool write);
    bool exitVehicle (Vehicle *v1, std::string namePort);
    void enterVehicle (Vehicle *v1, PortagemEntrada *port, bool write);
    bool exitVehicle (Vehicle *v1, PortagemSaida *port);
    void print ();
    void printPorts ();
    void printCurrentVehicles ();
    std::string getName () const {return name;}
    float getLength () const {return km;}
    PortagemEntrada *findPortE (std::string name);
    PortagemSaida *findPortS (std::string name);
    Vehicle *findVehicle (std::string matricula);
    bool operator== (const HighWay &highway);
    bool operator< (const HighWay &highway);
    void sortPortagens ();
    friend std::ostream &operator<< (std::ostream &o, const HighWay &h);
    friend std::istream& operator>> (std::istream& is, HighWay &h);
};


#endif //UNTITLED2_HIGHWAY_H

#ifndef UNTITLED2_WAY_H
#define UNTITLED2_WAY_H

#include <iostream>
#include <queue>
#include "Worker.h"
#include "Vehicle.h"
#include "Exceptions.h"

///Class Via
class Way {
    Worker *worker;
    unsigned int wayNumber, occupancy;
    bool viaverde;
public:
    ///Construtor class Way
    Way(bool viaverde, unsigned int wayNumber) : viaverde(viaverde), wayNumber(wayNumber), occupancy(0) {};
    ///Definir Trabalhador
    void setWorker(Worker *worker);
    ///Retorna se é via verde ou não
    bool getVV() const {return viaverde;}
    ///Retorna o trabalhador
    Worker *getWorker();
    ///Troca o trabalhador
    void changeWorker(Worker *newWorker);
    ///Imprime membros da class
    void print() const;
    ///Retorna o número da via
    unsigned int getNumber() const {return wayNumber;}
    ///Retorna a ocupação da via
    unsigned int getOccupancy() const {return occupancy;}
    ///Processa o veículo
    unsigned int processVehicle(Vehicle *vehicle);
    bool operator<(const Way &way) const;

};


#endif //UNTITLED2_WAY_H

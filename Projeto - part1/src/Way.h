#ifndef UNTITLED2_WAY_H
#define UNTITLED2_WAY_H

#include <iostream>
#include <queue>
#include "Worker.h"
#include "Vehicle.h"
#include "Exceptions.h"


class Way {
    Worker *worker;
    unsigned int wayNumber, occupancy;
    bool viaverde;
public:
    Way(bool viaverde, unsigned int wayNumber) : viaverde(viaverde), wayNumber(wayNumber), occupancy(0) {};
    void setWorker(Worker *worker);
    bool getVV() const {return viaverde;}
    Worker *getWorker();
    void changeWorker(Worker *newWorker);
    void print() const;
    unsigned int getNumber() const {return wayNumber;}
    unsigned int getOccupancy() const {return occupancy;}
    unsigned int processVehicle(Vehicle *vehicle);
    bool operator<(const Way &way) const;

};


#endif //UNTITLED2_WAY_H

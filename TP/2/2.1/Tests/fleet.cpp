#include "fleet.h"
#include <string>
#include <iostream>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}
void Fleet::addVehicle(Vehicle *vl){vehicles.push_back(vl);}
int Fleet::numVehicles() const {return vehicles.size();}
int Fleet::lowestYear() const {
    int lessyear;
    if (!vehicles.empty())
        lessyear = vehicles[0]->getYear();
    else
        return 0;
    for (vector<Vehicle *>::const_iterator it = vehicles.begin(); it < vehicles.end(); it++){
        if(lessyear > (*it)->getYear())
            lessyear = (*it)->getYear();
    }
    return lessyear;
}

vector <Vehicle*> Fleet::operator()(int yearM) const {
    std::vector <Vehicle*> vehicles2;
    for (std::vector<Vehicle*>::const_iterator it = vehicles.begin(); it != vehicles.end(); it++){
        if ((*it)->getYear() == yearM)
            vehicles2.push_back(*it);
    }
    return vehicles2;
}

float Fleet::totalTax() const {
    float sum;
    for(std::vector<Vehicle*>::const_iterator it = vehicles.begin(); it != vehicles.end();it++)
        sum = (*it)->calculateTax() + sum;
    return sum;
}

unsigned Fleet::removeOldVehicles(int yl) {
    unsigned count = 0;
    for(std::vector<Vehicle*>::const_iterator it = vehicles.begin(); it != vehicles.end();it++){
        if ((*it)->getYear() <= yl) {
            vehicles.erase(it);
            count++;
            it--;
        }
    }
    return count;
}




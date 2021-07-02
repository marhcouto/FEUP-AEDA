//
// Created by marhc on 15/11/2020.
//

#include "Way.h"
#include <sstream>

/* ---Way Class--- */

void Way::setWorker(Worker *worker) {
    if (!viaverde)
        worker = worker;
    else
        throw WayIsViaverde(this->getNumber());
}

unsigned int Way::processVehicle(Vehicle *vehicle) {
    occupancy++;
    return wayNumber;
}

void Way::changeWorker(Worker *newWorker) {
    this->setWorker(newWorker);
    std::cout << "Change of wokers was successful\n";
}

void Way::print() const {
    std::string vv;
    if (this->viaverde) vv = "viaverde";
    else vv = "normal";
    std::cout << "Way number: " << wayNumber << " | " << "Type: " << vv << " | " << "Occupancy: " << occupancy << " | ";
    std::cout << "Worker: " << worker->getName() << std::endl;
}

Worker* Way::getWorker() {
    if(viaverde) throw WayIsViaverde(this->getNumber());
    else return this->worker;
}

bool Way::operator<(const Way &way) const {
    return wayNumber < way.wayNumber;
}


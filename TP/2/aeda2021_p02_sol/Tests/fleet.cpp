#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

// ---------- TODO

int Fleet::numVehicles() const
{ return vehicles.size(); }

void Fleet::addVehicle(Vehicle *v1)
{ vehicles.push_back(v1); }

int Fleet::lowestYear() const
{
	if (vehicles.size()==0) return 0;
	vector<Vehicle *>::const_iterator it=vehicles.begin();
	int menorA=(*it)->getYear();
	it++;
	while(it!=vehicles.end()) {
		int ano1=(*it)->getYear();
		if (ano1<menorA) menorA=ano1;
		it++;
	}
	return menorA;
}

float Fleet::totalTax() const
{
	if (vehicles.size()==0) return 0;
	float total=0;
	vector<Vehicle *>::const_iterator it = vehicles.begin();
	while(it != vehicles.end()) {
		total +=(*it)->calculateTax();
		it++;
	}
	return total;
}

vector<Vehicle *> Fleet::operator() (int y1) const {
	vector<Vehicle *> vehiclesYear;
	if (vehicles.size()==0) return vehiclesYear;
	vector<Vehicle *>::const_iterator it = vehicles.begin();
	while(it != vehicles.end()) {
		if ((*it)->getYear() == y1)
			vehiclesYear.push_back(*it);
		it++;
	}
	return vehiclesYear;
}

unsigned Fleet::removeOldVehicles(int y1) {
    int n=0;
    vector<Vehicle *>::const_iterator it = vehicles.begin();
    while(it != vehicles.end()) {
        if ((*it)->getYear()<= y1) {
            it = vehicles.erase(it);
            n++;
        }
        else
          it++;
    }
    return n;
}

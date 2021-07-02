#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    vector<Vehicle *> getVehicles() const;
	int numVehicles() const;
	void addVehicle(Vehicle *v1);
	int lowestYear() const;
	float totalTax() const;
	vector<Vehicle *> operator() (int y1) const;
	friend ostream & operator<<(ostream & o, const Fleet & f);
	unsigned removeOldVehicles(int y1);
};

#endif /*FLEET_H*/

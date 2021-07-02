#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    vector<Vehicle *> getVehicles() const;
	friend ostream & operator<<(ostream & o, const Fleet & f);
	void addVehicle(Vehicle *vl);
	int numVehicles () const;
	int lowestYear () const;
	std::vector <Vehicle*> operator () (int yearM) const;
	float totalTax() const;
	unsigned removeOldVehicles(int yl);
};


#endif /*FLEET_H_*/

#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	vector<Animal *> animals;
	vector<Veterinary *> veterinarians;
public:
	unsigned numAnimals() const;
    unsigned numVeterinarians() const;
    void addAnimal(Animal *a1);
	string getInfo() const;
	bool isYoung(string nameA);
	void allocateVeterinarians(istream &isV);
	bool removeVeterinary(string nameV);
	bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */

#ifndef CENTRALPORTAGENS_CPP_INTERVENTION_H
#define CENTRALPORTAGENS_CPP_INTERVENTION_H
#include <string>
#include <iostream>
#include "Worker.h"

class Intervention {
    Date date;
    std::string port;
    Specialty type;
    int duration; // in min
    Technician *tech;

public:
    Intervention() {};
    Intervention(int day, int month, int year, int duration, Technician* tech, std::string port, Specialty type);
    std::string getTypeString() const;
    Specialty getType() const {return type;}
    std::string getPort() const {return port;}
    int getDuration() const {return duration;}
    Technician* getTech () const {return tech;}
    void setTech (Technician* tech);
    void print() const;
    bool operator< (const Intervention& interv) const;
    bool operator==(const Intervention& interv) const;
    friend std::ostream& operator<< (std::ostream& os, const Intervention& interv);
    friend std::istream& operator>> (std::istream& is, Intervention& interv);
};


#endif //CENTRALPORTAGENS_CPP_INTERVENTION_H

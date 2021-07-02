#ifndef CENTRALPORTAGENS_CPP_INTERVENTION_H
#define CENTRALPORTAGENS_CPP_INTERVENTION_H
#include <string>
#include <iostream>
#include "Worker.h"
///Class Intervenção
class Intervention {
    Date date;
    std::string port;
    Specialty type;
    int duration; // in min
    Technician *tech;

public:
    Intervention() {};
    ///Construtor da class Intervention
    Intervention(int day, int month, int year, int duration, Technician* tech, std::string port, Specialty type);
    ///Retorna o tipo de intervenção em string
    std::string getTypeString() const;
    ///Retorna o tipo de intervenção
    Specialty getType() const {return type;}
    ///Retorna a portagem onde é feita
    std::string getPort() const {return port;}
    ///Retorna a duração
    int getDuration() const {return duration;}
    ///Retorna o técnico responsável
    Technician* getTech () const {return tech;}
    ///Define o técnico responsável
    void setTech (Technician* tech);
    ///Imprime os membros da classe
    void print() const;
    bool operator< (const Intervention& interv) const;
    bool operator==(const Intervention& interv) const;
    friend std::ostream& operator<< (std::ostream& os, const Intervention& interv);
    friend std::istream& operator>> (std::istream& is, Intervention& interv);
};


#endif //CENTRALPORTAGENS_CPP_INTERVENTION_H

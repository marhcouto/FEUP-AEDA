#ifndef UNTITLED2_HIGHWAY_H
#define UNTITLED2_HIGHWAY_H


#include "Portagem.h"

///Class Auto-Estrada
class HighWay {
    std::vector<Vehicle*> vehiclesInTransit;
    std::vector<PortagemSaida*> portagensS;
    std::vector<PortagemEntrada*> portagensE;
    std::string name;
    float km;
public:
    HighWay() {};
    ///Construtor da class HighWay
    HighWay(std::string name, float km) : name(name), km(km) {};
    ///Define o vector de portagens de Saida (portagensS)
    void setPortagensS(std::vector <PortagemSaida*> portagens);
    ///Define o vector de portagens de Entrada (portagensE)
    void setPortagensE(std::vector <PortagemEntrada*> portagens);
    ///Define o vector de veículos em circulação (vehiclesInTransit)
    void setVehicles(std::vector <Vehicle*> vehicles);
    ///Adiciona uma portagem de entrada ao vector de portagens de entrada
    void addPortagemE(PortagemEntrada *portagem);
    ///Adiciona uma portagem de saída ao vector de portagens de saída
    void addPortagemS(PortagemSaida *portagem);
    ///Remover veículo do vector de veículos (vehicles)
    void removeVehicle (Vehicle *v1);
    ///Dar entrada do veículo (v1) na portagem com nome (namePort)
    void enterVehicle (Vehicle *v1, std::string namePort, bool write);
    ///Dar saída do veículo (v1) na portagem com nome (namePort)
    bool exitVehicle (Vehicle *v1, std::string namePort);
    ///Dar entrada do veículo (v1) na portagem de entrada (port)
    void enterVehicle (Vehicle *v1, PortagemEntrada *port, bool write);
    ///Dar saída do veículo (v1) na portragem de saída (port)
    bool exitVehicle (Vehicle *v1, PortagemSaida *port);
    ///Imprime conteúdos da auto-estrada
    void print ();
    ///Imprime as portagens
    void printPorts ();
    ///Imprime os veículos em circulação
    void printCurrentVehicles ();
    ///Retorna o nome da auto-estrada
    std::string getName () const {return name;}
    ///Retorna o comprimento da auto-estrada
    float getLength () const {return km;}
    ///Procura a portagem de entrada de nome (name)
    PortagemEntrada *findPortE (std::string name);
    ///Procura a portagem de saída de nome (name)
    PortagemSaida *findPortS (std::string name);
    ///Procura o veículo com matricula (matricula)
    Vehicle *findVehicle (std::string matricula);
    bool operator== (const HighWay &highway);
    bool operator< (const HighWay &highway);
    ///Ordena as portagens
    void sortPortagens ();
    friend std::ostream &operator<< (std::ostream &o, const HighWay &h);
    friend std::istream& operator>> (std::istream& is, HighWay &h);
};


#endif //UNTITLED2_HIGHWAY_H

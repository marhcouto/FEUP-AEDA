#ifndef UNTITLED2_PORTAGEM_H
#define UNTITLED2_PORTAGEM_H

#include <iostream>
#include <vector>
#include "Way.h"
#include <algorithm>
#include <fstream>
#include <ctime>
#include <queue>
///struct para definir a localização da portagem
struct GeoLocation{
    float km;
    std::string location;
};
///Class geral portagem
/* ---Class Portagem--- */
class Portagem {
protected:
    std::string name, highway;
    GeoLocation location;
    unsigned int nWays, nViaVerde;
    std::vector<Way*> ways;
    std::priority_queue<Technician*> techs;
public:
    Portagem() {};
    ///Construtor da class Portagem
    Portagem(std::string name, GeoLocation location, unsigned int nWays,
             unsigned int nViaVerde, std::string highway);
    ///Destrutor da class Portagem
    ~Portagem();
    ///Retorna o nome da portagem
    std::string getName () const {return name;}
    ///Retorna o nome da auto-estrada onde a portagem está inserida
    std::string getHighWay () const {return highway;}
    ///retorna a localização da portagem
    GeoLocation getLocation () const {return location;}
    ///retorna o vector de vias da portagem (ways)
    std::vector <Way*> getWays () const {return ways;}
    ///Retorna a fila de prioridade de técnicos
    std::priority_queue<Technician*> getTechs () const {return techs;}
    ///Define o vector de vias (ways)
    void setWays (std::vector<Way*> ways);
    ///Define o número de vias-via verde (nViaVerde) e o número de vias-não via verde(nWays)
    void setWays (unsigned int nWays, unsigned int nViaVerde);
    ///Adiciona uma via ao vector de vias (ways)
    void addWay (Way *way);
    ///Adiciona um técnico à fila de prioridade
    void addTech (Technician* tech);
    ///Remove um técnico da fila de prioridade
    void removeTech (Technician* t);
    ///Retorna um técnico de especialidade (specialty)
    Technician* getTech (Specialty specialty);
    ///Procura o técnico de nome(name) e especialidade(spec)
    Technician* findTech (std::string name, std::string spec);
    ///Ordena as vias
    void sortWays();
    ///Imprime membros da class
    virtual void print() const;
    ///Imprime os técnicos
    void printTechs() const;
    ///Retorna o número de vias-via verde
    unsigned int getVV () const {return nViaVerde;}
    ///Retorna o número de vias-não via verde
    unsigned int getNWays () const {return nWays;}
    ///Procurar uma via no vector de vias (ways)
    Way* findWay (unsigned int number);
    ///Retorna e melhor via baseada na preferência do cliente
    Way* getBestWay (bool preference);
    bool operator== (const Portagem &portagem) const;
    bool operator< (const Portagem &portagem) const;
};
///Class de Portagens de Entrada
class PortagemEntrada : public Portagem {
public:

    PortagemEntrada() : Portagem() {};
    ///Construtor da class PortagemEntrada
    PortagemEntrada(std::string name, GeoLocation location, unsigned int nWays, unsigned int nViaVerde,
            std::string highway) : Portagem(name, location, nWays, nViaVerde, highway) {};
    ///Dar entrada a um veículo
    void enterVehicle(Vehicle *v, bool write);
    ///Imprimir membros da classe
    void print() const;
    friend std::ostream &operator <<(std::ostream &o, const PortagemEntrada &p);
    friend std::istream &operator >>(std::istream &is, PortagemEntrada& p);
};
///Class de Portagens de Saida
class PortagemSaida : public Portagem {
    std::vector<Worker*> workers;
    float localProfit;
    static float totalProfit;
public:
    PortagemSaida() : Portagem() {};
    ///Construtor class PortagemSaida
    PortagemSaida(std::string name, GeoLocation location, unsigned int nWays, unsigned int nViaVerde,
                  std::string highway, float profit) : Portagem(name, location, nWays, nViaVerde, highway),
                  localProfit(profit) {};
    ///Retorna os trabalhadores da Portagem
    std::vector<Worker*> getWorkers() const {return workers;}
    ///Retorna o lucro da portagem
    float getProfit() const {return localProfit;}
    ///Define o vector de trabalhadores (workers)
    void setWorkers(std::vector<Worker*> w);
    ///Adiciona um trabalhador ao vector de trabalhadores
    void addWorker(Worker *worker);
    ///Remove um trbalhador do vector de trabalhadores
    void removeWorker(Worker *worker);
    ///Substitui o trabalhador com nome (name) pelo trabalhador (newWorker)
    void changeWorker(std::string name, Worker *newWorker);
    ///Substitui o trbalhador (oldWorker) pelo trabalhador (newWorker)
    bool changeWorker(Worker *oldWorker, Worker *newWorker);
    ///Distribui os trabalhadores
    void assignWorkers();
    ///Imprime os trabalhadores
    void printWorkers();
    ///Imprime membros da função
    void print() const;
    ///Incrementa o lucro da portagem
    void incrementProfit(float val) {localProfit += val;}
    ///Incrementa o lucro total das portagens
    static void incrementTotalProfit(float val) {totalProfit += val;}
    ///Retorna o lucro total das portagens
    static float getTotalProfit() {return totalProfit;}
    ///Dá saída ao veículo (v)
    bool exitVehicle (Vehicle *v);
    ///Procura o trabalhador de nome (name)
    Worker* findWorker(std::string name);
    ///Procura o trabalhador de ID (ID)
    Worker* findWorker(unsigned int ID);
    friend std::ostream &operator <<(std::ostream &o, const PortagemSaida &p);
    friend std::istream &operator >>(std::istream &is, PortagemSaida& p);
};




#endif //UNTITLED2_PORTAGEM_H

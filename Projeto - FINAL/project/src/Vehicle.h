//
// Created by marhc on 15/11/2020.
//

#ifndef UNTITLED2_VEHICLE_H
#define UNTITLED2_VEHICLE_H

#include <string>
#include <iostream>
#include "Worker.h"



///Class geral de veículos
class Vehicle {
    std::string matricula, entryPort, exitPort;
    bool prefersViaVerde;
    float entryKm;
    float entryTime;
    Driver *driver;
public:
    ///Construtor da class Vehicle
    Vehicle(std::string matricula, bool prefersViaVerde) :
    matricula(matricula), prefersViaVerde(prefersViaVerde){};
    ///Construtor da class Vehicle
    Vehicle(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
    matricula(matricula), prefersViaVerde(prefersViaVerde), entryKm(entryKm), entryPort(entryPort), driver(driver) {};
    ///Retorna a portagem pela qual o veículo entrou
    std::string getEntryPort() const {return entryPort;}
    ///Retorna a matricula do veículo
    std::string getMatricula() const {return matricula;}
    ///Retorna o condutor
    Driver* getDriver() const {return driver;}
    ///Retona o km relativo à portagem na qual o veículo entrou
    float getEntryKm() const {return entryKm;}
    ///Retorna a hora em que o veículo entrou na auto-estrada
    float getEntryTime() const {return entryTime;}
    ///Retorna o imposto pago por km percorrido na auto-estrada
    virtual float getFee() const = 0;
    ///Retorna a categoria do veículo
    virtual int getClass() const = 0;
    ///Defina a hora em que o veículo entrou na auto-estrada
    void setEntryTime(float val);
    ///Define a portagem na qual o veículo entrou na auto-estrada
    void setEntryPort(std::string portName);
    ///Defina a portagem na qual o veículo saiu da auto-estrada
    void setExitPort(std::string portName);
    ///Define o km relativo à portagem na qual o veículo entrou
    void setEntryKm(float entryKm);
    ///Define o condutor do veículo
    void setDriver (Driver* driver);
    ///Imprime os membros da class
    virtual void print() const;
    ///Retorna a preferência relativa às vias (via verda/não via verde)
    bool getPrefers() const {return prefersViaVerde;}
    bool operator==(Vehicle &v1);
    friend std::ostream &operator<<(std::ostream &o, const Vehicle &v);
};
///Class de veículos de categoria 1
class VehicleClass1 : public Vehicle{
    constexpr static float fee = 0.05;
public:
    ///Construtor da class VehicleClass1
    VehicleClass1(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
    Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    ///Construtor da class VehicleClass1
    VehicleClass1(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    ///Retorna o imposto pago por km percorrido na auto-estrada
    float getFee() const {return fee;}
    ///Retorna a categoria do veículo
    int getClass() const {return 1;}
    ///Imprime os membros da class
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass1 &v);
};
///Class de veículos de categoria 2
class VehicleClass2 : public Vehicle{
    constexpr static float fee = 0.10;
public:
    ///Construtor da class VehicleClass2
    VehicleClass2(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    ///Construtor da class VehicleClass2
    VehicleClass2(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    ///Retorna o imposto pago por km percorrido na auto-estrada
    float getFee() const {return fee;}
    ///Retorna a categoria do veículo
    int getClass() const {return 2;}
    ///Imprime os membros da class
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass2 &v);
};
///Class de veículos de categoria 3
class VehicleClass3 : public Vehicle{
    constexpr static float fee = 0.15;
public:
    ///Construtor da class VehicleClass3
    VehicleClass3(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    ///Construtor da class VehicleClass3
    VehicleClass3(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    ///Retorna o imposto pago por km percorrido na auto-estrada
    float getFee() const {return fee;}
    ///Retorna a categoria do veículo
    int getClass() const {return 3;}
    ///Imprime os membros da class
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass3 &v);
};
///Class de veículos de categoria 4
class VehicleClass4 : public Vehicle{
    constexpr static float fee = 0.20;
public:
    ///Construtor da class VehicleClass4
    VehicleClass4(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    ///Construtor da class VehicleClass4
    VehicleClass4(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    ///Retorna o imposto pago por km percorrido na auto-estrada
    float getFee() const {return fee;}
    ///Retorna a categoria do veículo
    int getClass() const {return 4;}
    ///Imprime os membros da função
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass4 &v);
};


#endif //UNTITLED2_VEHICLE_H

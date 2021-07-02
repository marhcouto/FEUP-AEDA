//
// Created by marhc on 15/11/2020.
//

#ifndef UNTITLED2_VEHICLE_H
#define UNTITLED2_VEHICLE_H

#include <string>
#include <iostream>
#include "Worker.h"




class Vehicle {
    std::string matricula, entryPort, exitPort;
    bool prefersViaVerde;
    float entryKm;
    float entryTime;
    Driver *driver;
public:
    Vehicle(std::string matricula, bool prefersViaVerde) :
    matricula(matricula), prefersViaVerde(prefersViaVerde){};
    Vehicle(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
    matricula(matricula), prefersViaVerde(prefersViaVerde), entryKm(entryKm), entryPort(entryPort), driver(driver) {};
    std::string getEntryPort() const {return entryPort;}
    std::string getMatricula() const {return matricula;}
    Driver* getDriver() const {return driver;}
    float getEntryKm() const {return entryKm;}
    float getEntryTime() const {return entryTime;}
    virtual float getFee() const = 0;
    virtual int getClass() const = 0;
    void setEntryTime(float val);
    void setEntryPort(std::string portName);
    void setExitPort(std::string portName);
    void setEntryKm(float entryKm);
    void setDriver (Driver* driver);
    virtual void print() const;
    bool getPrefers() const {return prefersViaVerde;}
    bool operator==(Vehicle &v1);
    friend std::ostream &operator<<(std::ostream &o, const Vehicle &v);
};

class VehicleClass1 : public Vehicle{
    constexpr static float fee = 0.05;
public:
    VehicleClass1(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
    Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    VehicleClass1(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    float getFee() const {return fee;}
    int getClass() const {return 1;}
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass1 &v);
};

class VehicleClass2 : public Vehicle{
    constexpr static float fee = 0.10;
public:
    VehicleClass2(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    VehicleClass2(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    float getFee() const {return fee;}
    int getClass() const {return 2;}
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass2 &v);
};

class VehicleClass3 : public Vehicle{
    constexpr static float fee = 0.15;
public:
    VehicleClass3(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    VehicleClass3(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    float getFee() const {return fee;}
    int getClass() const {return 3;}
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass3 &v);
};

class VehicleClass4 : public Vehicle{
    constexpr static float fee = 0.20;
public:
    VehicleClass4(std::string matricula, bool prefersViaVerde, std::string entryPort, float entryKm, Driver* driver) :
            Vehicle(matricula, prefersViaVerde, entryPort, entryKm, driver) {};
    VehicleClass4(std::string matricula, bool prefersViaVerde) : Vehicle(matricula, prefersViaVerde) {};
    float getFee() const {return fee;}
    int getClass() const {return 4;}
    void print() const;
    friend std::ostream &operator<<(std::ostream &o, const VehicleClass4 &v);
};


#endif //UNTITLED2_VEHICLE_H

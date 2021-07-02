#include "vehicle.h"
#include <iostream>


Vehicle::Vehicle(string b, int m, int y) :brand(b), month(m), year(y){}
MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl): Vehicle(b, m, y), fuel(f), cylinder(cyl) {}
Car::Car(string b, int m, int y, string f, int cyl): MotorVehicle(b, m, y, f, cyl) {}
Bicycle::Bicycle(string b, int m, int y, string t) :Vehicle(b, m, y), type(t) {}
Truck::Truck(string b, int m, int y, string f, int cyl, int ml): MotorVehicle(b, m, y, f, cyl), maximumLoad(ml) {}


std::string Vehicle::getBrand() const {return brand;}
std::string MotorVehicle::getFuel() const {return fuel;}
int Vehicle::getYear() const {return year;}

int Vehicle::info() const {return 3;}
int MotorVehicle::info() const {return MotorVehicle::info(std::cout);}
int MotorVehicle::info(ostream &o) const {
    o << "\nbrand: " << brand << "\nmonth: " << month;
    o << "\nyear: " << year;
    o << "\nfuel: " << fuel << "\ncylinder: " << cylinder;
    return Vehicle::info() + 2;
}
int Car::info() const {return Car::info(std::cout);}
int Car::info(ostream &o) const {
    return MotorVehicle::info(o);
}
int Bicycle::info() const {return Bicycle::info(std::cout);}
int Bicycle::info(ostream &o) const {
    o << "\nbrand: " << brand << "\nmonth: " << month;
    o << "\nyear: " << year;
    o << "\ntype: " << type;
    return Vehicle::info() + 1;
}
int Truck::info() const {return Truck::info(std::cout);}
int Truck::info(ostream &o) const {
    o << "\nmaximumLoad: " << maximumLoad;
    return MotorVehicle::info() + 1;
}

bool Vehicle::operator < (const Vehicle & v) const{
    if (year < v.getYear())
        return true;
    else if (year == v.getYear())
        return month < v.month;
}

float MotorVehicle::calculateTax() const {
    if (fuel == "gas"){
        if (cylinder <= 1000) {
            if (year > 1995)
                return 14.56;
            else
                return 8.10;
        }
        else if(cylinder > 1000 && cylinder <= 1300) {
            if (year > 1995)
                return 29.06;
            else
                return 14.56;
        }
        else if(cylinder > 1300 && cylinder <= 1750) {
            if (year > 1995)
                return 45.15;
            else
                return 22.65;
        }
        else if(cylinder > 1750 && cylinder <= 2600) {
            if (year > 1995)
                return 113.98;
            else
                return 54.89;
        }
        else if(cylinder > 2600 && cylinder <= 3500) {
            if (year > 1995)
                return 181.17;
            else
                return 87.13;
        }
        else if(cylinder > 3500){
            if (year > 1995)
                return 320.89;
            else
                return 148.37;
        }
    }
    else{
        if (cylinder <= 1500) {
            if (year > 1995)
                return 14.56;
            else
                return 8.10;
        }
        else if(cylinder > 1500 && cylinder <= 2000) {
            if (year > 1995)
                return 29.06;
            else
                return 14.56;
        }
        else if(cylinder > 2000 && cylinder <= 3000) {
            if (year > 1995)
                return 45.15;
            else
                return 22.65;
        }
        else if(cylinder > 3000){
            if (year > 1995)
                return 113.98;
            else
                return 54.89;
        }
    }
}
float Bicycle::calculateTax() const {return 0.0;}





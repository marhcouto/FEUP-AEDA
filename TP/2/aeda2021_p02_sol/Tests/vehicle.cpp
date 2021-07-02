#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y)
{ brand=b; month=m; year=y; }

string Vehicle::getBrand() const
{ return brand; }

int Vehicle::info(ostream &o) const
{
    o << "Brand: " << brand << endl;
    o << "Date: " << month << "/" << year << endl;
    return 3;
}

int Vehicle::info() const
{ return Vehicle::info(cout); }

bool Vehicle::operator <(const Vehicle & v) const
{
    if (year<v.year) return true;
    if (year==v.year && month<v.month) return true;
    return false;
}

int Vehicle::getYear() const
{ return year; }


MotorVehicle::MotorVehicle(string b, int m, int y, string f,int cyl):Vehicle(b,m,y)
{ fuel=f; cylinder=cyl; }

string MotorVehicle::getFuel() const
{ return fuel; }


int MotorVehicle::info(ostream &o) const
{
   int infoV = Vehicle::info();
   o << "Fuel: " << fuel << endl;
   o << "Cylinder: " << cylinder << endl;
   return infoV+2;
}

int MotorVehicle::info() const
{ return MotorVehicle::info(cout); }

float MotorVehicle::calculateTax() const
{
   if (fuel=="gas") {
      if (cylinder<=1000)
		if (year<=1995) return 8.10; else return 14.56;
	else if (cylinder<=1300)
		if (year<=1995) return 14.56; else return 29.06;
	else if (cylinder<=1750)
		if (year<=1995) return 22.65; else return 45.15;
	else if (cylinder<=2600)
		if (year<=1995) return 54.89; else return 113.98;
	else if (cylinder<=3500)
		if (year<=1995) return 87.13; else return 181.17;
	else if (year<=1995) return 148.35; else return 320.89;
   }
   else {
	if (cylinder<=1500)
		if (year<=1995) return 8.10; else return 14.56;
	else if (cylinder<=2000)
		if (year<=1995) return 14.56; else return 29.06;
	else if (cylinder<=3000)
		if (year<=1995) return 22.65; else return 45.15;
	else  if (year<=1995) return 54.89; else return 113.98;
   }
}


Car::Car(string b, int m, int y, string f, int cyl): MotorVehicle(b,m,y,f,cyl)
{ }

int Car::info(ostream &o) const
{
   o << "Car"<< endl;
   int infoM=MotorVehicle::info();
   o << endl;
   return infoM;
}

int Car::info() const
{ return Car::info(cout); }


Truck::Truck(string b, int m, int y, string f, int cyl,int ml): MotorVehicle(b,m,y,f,cyl)
{
   maximumLoad=ml;
}

int Truck::info(ostream &o) const
{
   o << "Truck"<<endl;
   int infoM = MotorVehicle::info();
   o << "Maximum Load: " << maximumLoad<< endl<< endl;
   return infoM+1;
}

int Truck::info() const
{ return Truck::info(cout); }


Bicycle::Bicycle(string b, int m, int y, string t): Vehicle(b,m,y)
{ type=t; }

int Bicycle::info(ostream &o) const
{
   o << "Bicycle" << endl;
   int infoV=Vehicle::info();
   o << "Type: " << type<< endl<< endl;
   return infoV+1;
}

int Bicycle::info() const
{ return Bicycle::info(cout); }

float Bicycle::calculateTax() const
{ return 0; }





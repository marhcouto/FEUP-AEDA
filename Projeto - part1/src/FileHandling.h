#ifndef UNTITLED2_FILEHANDLING_H
#define UNTITLED2_FILEHANDLING_H

#include <fstream>
#include "CentralPortagens.h"

template <class item>
void fileUpdater(std::string fileName, const std::vector<item> &i) {
    std::ofstream f;
    f.open(fileName);
    if (f.fail())
        throw FileDoesNotExist(fileName);
    int Indice = 0;
    int n = i.size();
    typename std::vector<item>::const_iterator it;
    for (it = i.begin(); it != i.end(); it++) {
        f << **it;
        Indice++;
        if (Indice < n) f << "\n";
    }
    f.close();
}

void printRegistry() {
    std::ifstream f;
    std::cout << "\n\nRegisrtry:\n";
    f.open("Registry.txt");
    if (f.fail())
        throw FileDoesNotExist("Registry.txt");
    while (!f.eof()) {
        std::string line;
        std::getline(f, line);
        std::cout << line;
    }
    std::cout << "\n\n";
    f.close();
}

void interventionsFileUpdater(const std::vector<Intervention>& interventions) {
    std::ofstream f;
    f.open("Interventions.txt");
    if (f.fail())
        throw FileDoesNotExist("Interventions.txt");
    int Indice = 0;
    int n = interventions.size();
    for (auto interv : interventions) {
        f << interv;
        Indice++;
        if (Indice < n) f << "\n";
    }
    f.close();
}

void readInterventionsFile (BST<Intervention>& interventions) {
    std::ifstream f;
    f.open("Interventions.txt");
    if (f.fail())
        throw FileDoesNotExist("Interventions.txt");
    while (!f.eof()) {
        Intervention i;
        f >> i;
        f.ignore(20, '\n');
        interventions.insert(i);
    }
    f.close();
}

template <class Item>
void fileReader (std::string fileName, std::vector<Item*> &v) {
    std::ifstream f;
    f.open(fileName);
    if (f.fail()) {
        std::cout << "Failed to open " << fileName << std::endl;
        return;
    }
    while (!f.eof()) {
        Item *i = new Item();
        f >> *i;
        f.ignore(20, '\n');
        v.push_back(i);
    }
    f.close();
}

void readDriversFile (std::string fileName, DriversHT& drivers) {
    std::ifstream f;
    f.open (fileName);
    if (f.fail()) {
        std::cout << "Failed to open " << fileName << std::endl;
        return;
    }
    while (!f.eof()) {
        std::stringstream ss;
        std::string name, matricula, matriculas, lastMatricula = "";
        std::getline(f, name);
        //if (name.empty()) continue;
        Driver* driver = new Driver(name);
        std::getline(f, matriculas);
        ss << matriculas;
        while (true) {
            ss >> matricula;
            if (matricula == lastMatricula) break;
            lastMatricula = matricula;
            driver->addVehicle(matricula);
        }
        drivers.insert(driver);
    }
    f.close();
}

void clearFile(std::string fileName){
    std::fstream f;
    f.open(fileName, std::ios::trunc | std::ios::out);
    if (f.fail()) {
        throw FileDoesNotExist(fileName);
    }
    f.close();
}

void readEntryPortsFile(std::vector<PortagemEntrada*> &ports){
    std::ifstream f;
    std::string line, name, highway;
    unsigned int nWays, nVV;
    GeoLocation loc;
    f.open("EntryPorts.txt");
    while(!f.eof()){
        f >> name >> loc.location >> loc.km >> nWays >> nVV >> highway;
        PortagemEntrada *portagem1 = new PortagemEntrada(name, loc, nWays, nVV, highway);
        ports.push_back(portagem1);
    }
    f.close();
}

void readVehiclesFile(std::vector<Vehicle*> &vehicles){
    std::ifstream f;
    std::string matricula, prefers, entryPort, propriator;
    float entryKm;
    bool prefersViaVerde;
    int classe;
    f.open("Vehicles.txt");
    while(!f.eof()){
        std::getline(f, propriator);
        if (propriator.empty()) continue;
        f >> matricula >> classe >> prefers >> entryPort >> entryKm;
        Driver* d = new Driver(propriator, {matricula});
        if (prefers == "t") prefersViaVerde = true;
        else prefersViaVerde = false;
        switch (classe) {
            case 1: {
                VehicleClass1 *v = new VehicleClass1(matricula, prefersViaVerde, entryPort, entryKm, d);
                vehicles.push_back(v);
                break;
            }
            case 2: {
                VehicleClass2 *v = new VehicleClass2(matricula, prefersViaVerde, entryPort, entryKm, d);
                vehicles.push_back(v);
                break;
            }
            case 3: {
                VehicleClass3 *v = new VehicleClass3(matricula, prefersViaVerde, entryPort, entryKm, d);
                vehicles.push_back(v);
                break;
            }
            case 4: {
                VehicleClass4 *v = new VehicleClass4(matricula, prefersViaVerde, entryPort, entryKm, d);
                vehicles.push_back(v);
                break;
            }
            default: {
                std::cout << "Invalid class of car\n";
                break;
            }
        }
    }
    f.close();
}

void readExitPortsFile(std::vector<PortagemSaida*> &ports){
    std::ifstream f;
    std::string line, name, highway;
    unsigned int nWays, nVV;
    float profit;
    GeoLocation loc;
    f.open("ExitPorts.txt");
    while(!f.eof()){
        f >> name >> loc.location >> loc.km >> nWays >> nVV >> highway >> profit;
        PortagemSaida *portagem1 = new PortagemSaida(name, loc, nWays, nVV, highway, profit);
        ports.push_back(portagem1);
    }
    f.close();
}


#endif //UNTITLED2_FILEHANDLING_H

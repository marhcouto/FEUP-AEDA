#include <iostream>
#include <sstream>
#include "FileHandling.h"

void createCentral(CentralPortagens &cp){
    clearFile("Registry.txt");
    std::vector<HighWay *> highways;
    std::vector <PortagemEntrada*> entryPorts;
    std::vector <PortagemSaida*> exitPorts;
    std::vector <Worker*> workers;
    std::vector <Vehicle*> vehicles;
    std::vector <Manager*> managers;
    std::vector <Technician*> techs;
    DriversHT missbDrivers, drivers;
    BST<Intervention> interventions (Intervention(0, 0, 0, 0, nullptr, "", Revision));

    readDriversFile("MissbehavedDrivers.txt", missbDrivers);
    fileReader<HighWay> ("Highway.txt", highways);
    readEntryPortsFile (entryPorts);
    readExitPortsFile (exitPorts);
    readInterventionsFile (interventions);
    fileReader<Worker> ("Workers.txt", workers);
    fileReader<Technician> ("Technicians.txt", techs);
    readVehiclesFile (vehicles);
    fileReader<Manager>("Managers.txt", managers);
    readDriversFile ("Drivers.txt", drivers);

    cp.setIntervs (interventions);
    cp.setMissbDrivers(missbDrivers);
    cp.setDrivers (drivers);
    cp.setManagers (managers);
    cp.setHighWays (highways);
    cp.setWorkers (workers);
    cp.setPortagensE (entryPorts);
    cp.setPortagensS (exitPorts);
    cp.setVehicles (vehicles);

    try {
        cp.assignWorkers ();
        cp.assignPortagens ();
        cp.assignVehicles ();
        cp.assignTechs (techs);
        cp.assignIntervs (techs);
    }
    catch (TechnicianNotFound& e) {
        std::cout << e.getMSG() << std::endl;
    }
    catch (PortagemDoesNotExist& e) {
        std::cout << e.getMSG() << std::endl;
    }
    catch (NotEnoughWorkers& e) {
        std::cout << e.getMSG() << std::endl;
    }
    catch (HighWayDoesNotExist& e) {
        std::cout << e.getMSG() << std::endl;
    }
    cp.printInterventions();
}

void portSMenu(PortagemSaida *p) {
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "Type the number of the option you wish to execute:\n";
        std::cout << "1-Print all workers\n";
        std::cout << "2-Print info\n";
        std::cout << "3-Access way\n";
        std::cout << "4-Access worker by name\n";
        std::cout << "5-Access worker by ID\n";
        std::cout << "6-Access technician info\n";
        std::cout << "0-Go back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                p->printWorkers();
                break;
            }
            case 2: {
                p->print();
            }
            case 3: {
                Way *w;
                bool valid2, zero = false;
                do {
                    valid2 = true;
                    unsigned int number;
                    std::cout << "Way number:\n";
                    std::cin >> number;
                    if (number == 0) {
                        zero = true;
                        break;
                    }
                    try {
                        w = p->findWay(number);
                    }
                    catch(WayDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) w->print();
                break;
            }
            case 4: {
                Worker *w;
                bool valid2, zero = false;
                do {
                    std::string name;
                    valid2 = true;
                    std::cout << "Worker name:\n";
                    std::cin.ignore(1);
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        w = p->findWorker(name);
                    }
                    catch(WorkerDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) w->print();
                break;
            }
            case 5: {
                Worker *w;
                bool valid2, zero = false;
                do {
                    unsigned int ID;
                    valid2 = true;
                    std::cout << "Worker ID:\n";
                    std::cin >> ID;
                    if (ID == 0) {
                        zero = true;
                        break;
                    }
                    try {
                        w = p->findWorker(ID);
                    }
                    catch(WorkerDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) w->print();
                break;
            }
            case 6: {
                Technician *t;
                bool valid = true, zero = false;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name, spec;
                    std::cout << "Technician's name:\n";
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Technician's specialty:\n";
                    std::getline(std::cin, spec);
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        t = p->findTech(name, spec);
                    }
                    catch(TechnicianNotFound &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(SpecialtyInvalid &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                if (!zero) t->print();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void portEMenu(PortagemEntrada *p) {
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "Type the number of the option you wish to execute:\n";
        std::cout << "1-Print info\n";
        std::cout << "2-Access way info\n";
        std::cout << "3-Access technician info\n";
        std::cout << "0-Go back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                p->print();
                break;
            }
            case 2: {
                Way *w;
                bool valid2, zero = false;
                do {
                    valid2 = true;
                    unsigned int number;
                    std::cout << "Way number:\n";
                    std::cin >> number;
                    if (number == 0) {
                        zero = true;
                        break;
                    }
                    try {
                        w = p->findWay(number);
                    }
                    catch(WayDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) w->print();
                break;
            }
            case 3: {
                Technician *t;
                bool valid = true, zero = false;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name, spec;
                    std::cout << "Technician's name:\n";
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Technician's specialty:\n";
                    std::getline(std::cin, spec);
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        t = p->findTech(name, spec);
                    }
                    catch(TechnicianNotFound &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(SpecialtyInvalid &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                if (!zero) t->print();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void highwayMenu(CentralPortagens &cp, HighWay *h) {
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "\n\nType the number of the option you wish to execute:\n";
        std::cout << "1-Print all ports (portagens)\n";
        std::cout << "2-Print all current vehicles\n";
        std::cout << "3-Port(portagem) options\n";
        std::cout << "4-Access a specific vehicle\n";
        std::cout << "5-Print info\n";
        std::cout << "6-Register vehicle entrance\n";
        std::cout << "7-Register vehicle exit\n";
        std::cout << "0-Go back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                h->printPorts();
                break;
            }
            case 2: {
                h->printCurrentVehicles();
                break;
            }
            case 3: {
                bool valid, zero = false;
                do {
                    std::string type;
                    valid = true;
                    std::cout << "Port type(entry or exit):\n";
                    std::cin >> type;
                    if (type == "0") {
                        zero = true;
                        break;
                    }
                    if (type == "entry") {
                        bool valid2;
                        PortagemEntrada *p;
                        do {
                            valid2 = true;
                            std::string name;
                            std::cout << "Port name:\n";
                            std::cin >> name;
                            if (name == "0") {
                                zero = true;
                                break;
                            }
                            try {
                                p = h->findPortE(name);
                            }
                            catch(PortagemDoesNotExist &e) {
                                std::cout << e.getMSG();
                                valid = false;
                            }
                        } while (!valid2);
                        if (!zero) portEMenu(p);
                    }
                    else if (type == "exit") {
                        bool valid2;
                        PortagemSaida *p;
                        do {
                            valid2 = true;
                            std::string name;
                            std::cout << "Port name:\n";
                            std::cin >> name;
                            if (name == "0") {
                                zero = true;
                                break;
                            }
                            try {
                                p = h->findPortS(name);
                            }
                            catch(PortagemDoesNotExist &e) {
                                std::cout << e.getMSG();
                                valid = false;
                            }
                        } while (!valid2);
                        if (!zero) portSMenu(p);
                    }
                    else {
                        std::cout << "Invalid type for a port\n";
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 4: {
                Vehicle *v;
                bool valid2, zero = false;
                do {
                    valid2 = true;
                    std::string matricula;
                    std::cout << "Vehicle matricula:\n";
                    std::cin >> matricula;
                    if (matricula == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        v = h->findVehicle(matricula);
                    }
                    catch(PortagemDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) v->print();
                break;
            }
            case 5: {
                h->print();
                break;
            }
            case 6: {
                bool valid;
                Vehicle* v;
                do {
                    valid = true;
                    bool viaverde;
                    std::string pName, licensePlate, preference;
                    unsigned int classe;
                    std::cout << "Vehicle's license plate:\n";
                    std::cin >> licensePlate;
                    if (licensePlate == "0") {
                        break;
                    }
                    if (licensePlate.size() != 6) {
                        std::cout << "License plate's length must be 6\n";
                        valid = false;
                        continue;
                    }
                    if (cp.findVehicleBoolean(licensePlate)) {
                        std::cout << "Vehicle is already in transit\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Vehicle preference ('viaverde' or 'normal'):\n";
                    std::cin >> preference;
                    if (preference == "0") break;
                    if (preference == "viaverde") {
                        viaverde = true;
                    }
                    else if (preference == "normal") {
                        viaverde = false;
                    }
                    else {
                        std::cout << "Invalid preference\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Port by which the vehicle should go through(name):\n";
                    std::cin >> pName;
                    std::cout << "Vehicle class (1, 2, 3 or 4)\n";
                    std::cin >> classe;
                    switch (classe) {
                        case 1: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 2: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 3: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 4: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default:{
                            std::cout << "Invalid class\n";
                            valid = false;
                            break;
                        }
                    }
                    try {
                        cp.enterVehicle(v, pName, h->getName());
                    }
                    catch (PortagemDoesNotExist &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 7: {
                bool valid;
                do {
                    std::string licensePlate, pName;
                    std::cout << "Vehicle's license plate:\n";
                    std::cin >> licensePlate;
                    if (licensePlate == "0") break;
                    if (licensePlate.size() != 6) {
                        std::cout << "License plate's length must be 6\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Exit port (name):\n";
                    std::cin >> pName;
                    if (pName == "0") break;
                    try {
                        cp.exitVehicle(licensePlate, pName, h->getName());
                    }
                    catch (VehicleNotInTransit &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (PortagemDoesNotExist &e3) {
                        std::cout << e3.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while(!exit);

}

void cpVehicleOperationsMenu(CentralPortagens& cp) {
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "\n\nType the number of the option you wish to execute:\n";
        std::cout << "1-Register vehicle entrance\n";
        std::cout << "2-Register vehicle exit\n";
        std::cout << "3-Access driver info\n";
        std::cout << "0-Go Back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                bool valid;
                Vehicle* v;
                do {
                    valid = true;
                    bool viaverde;
                    std::string hName, pName, licensePlate, preference;
                    unsigned int classe;
                    std::cout << "Vehicle's license plate:\n";
                    std::cin >> licensePlate;
                    if (licensePlate == "0") break;
                    if (licensePlate.size() != 6) {
                        std::cout << "License plate's length must be 6\n";
                        valid = false;
                        continue;
                    }
                    if (cp.findVehicleBoolean(licensePlate)) {
                        std::cout << "Vehicle is already in transit\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Vehicle class (1, 2, 3 or 4)\n";
                    std::cin >> classe;
                    std::cout << "Vehicle preference ('viaverde' or 'normal'):\n";
                    std::cin >> preference;
                    if (preference == "0") break;
                    if (preference == "viaverde") {
                        viaverde = true;
                    }
                    else if (preference == "normal") {
                        viaverde = false;
                    }
                    else {
                        std::cout << "Invalid preference\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Highway in which the vehicle should enter(name):\n";
                    std::cin >> hName;
                    if (hName == "0") break;
                    std::cout << "Port by which the vehicle should go through(name):\n";
                    std::cin >> pName;
                    if (pName == "0") break;
                    switch (classe) {
                        case 1: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 2: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 3: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 4: {
                            v = new VehicleClass1(licensePlate, viaverde);
                            break;
                        }
                        case 0: {
                            break;
                        }
                        default:{
                            std::cout << "Invalid class\n";
                            valid = false;
                            break;
                        }
                    }
                    try {
                        cp.enterVehicle(v, pName, hName);
                    }
                    catch (PortagemDoesNotExist &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (HighWayDoesNotExist &e2) {
                        std::cout << e2.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 2: {
                bool valid;
                do {
                    std::string licensePlate, hName, pName;
                    std::cout << "Vehicle's license plate:\n";
                    std::cin >> licensePlate;
                    if (licensePlate == "0") break;
                    if (licensePlate.size() != 6) {
                        std::cout << "License plate's length must be 6\n";
                        valid = false;
                        continue;
                    }
                    std::cout << "Exit port (name):\n";
                    std::cin >> pName;
                    if (pName == "0") break;
                    std::cout << "Highway to exit (name):\n";
                    std::cin >> hName;
                    if (hName == "0") break;
                    try {
                        cp.exitVehicle(licensePlate, pName, hName);
                    }
                    catch (VehicleNotInTransit &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (HighWayDoesNotExist &e2) {
                        std::cout << e2.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (PortagemDoesNotExist &e3) {
                        std::cout << e3.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 3: {
                Driver *d;
                bool valid = true, zero = false;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name;
                    std::cout << "Driver's name:\n";
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        d = cp.findDriver(name);
                    }
                    catch(DriverNotFound &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                if (!zero) d->print();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void cpPersonelOperationsMenu(CentralPortagens &cp) {
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "\n\nType the number of the option you wish to execute:\n";
        std::cout << "1-Change workers\n";
        std::cout << "2-Fire Worker\n";
        std::cout << "3-Hire Worker\n";
        std::cout << "4-Add intervention\n";
        std::cout << "5-Hire technician\n";
        std::cout << "6-Fire technician\n";
        std::cout << "7-Remove intervention\n";
        std::cout << "0-Go Back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                bool valid = true;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string oldWorkerName, newWorkerName;
                    std::cout << "Name of the worker to be substituted(must be active):\n";
                    std::getline(std::cin, oldWorkerName);
                    if (oldWorkerName == "0") break;
                    std::cout << "Name of the worker that will substitute(must be inactive):\n";
                    std::getline(std::cin, newWorkerName);
                    if (newWorkerName == "0") break;
                    try {
                        cp.changeWorker(oldWorkerName, newWorkerName);
                    }
                    catch (WorkerIsActive &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (WorkerIsNotActive &e2) {
                        std::cout << e2.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 2: {
                bool valid = true;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name;
                    std::cout << "Name of the worker to be fired(must be inactive):\n";
                    std::getline(std::cin, name);
                    if (name == "0") break;
                    try {
                        cp.fireWorker(name);
                    }
                    catch (WorkerDoesNotExist &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (WorkerIsActive e2) {
                        std::cout << e2.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
            }
            case 3: {
                bool valid = true;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name;
                    unsigned int salary;
                    std::cout << "Name of the worker to be hired:\n";
                    std::getline(std::cin, name);
                    if (name == "0") break;
                    std::cout << "Salary that this worker should be awarded monthly:\n";
                    std::cin >> salary;
                    if (salary == 0) break;
                    auto *w = new Worker(name, salary, CentralPortagens::getNextID(), false, "-", "-");
                    CentralPortagens::incrementNextID();
                    cp.hireWorker(w);
                } while (!valid);
            }
            case 4: {
                bool valid, zero = false;
                do {
                    valid = true;
                    std::string name, spec, port;
                    int year, month, day;
                    std::cout << "Year:\n";
                    std::cin >> year;
                    std::cout << year << " ";
                    if (year == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Month:\n";
                    std::cin >> month;
                    std::cout << month << " ";
                    if (month == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Day:\n";
                    std::cin >> day;
                    std::cout << day << " ";
                    if (day == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Specialty:\n";
                    std::cin >> spec;
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Port:\n";
                    std::cin >> port;
                    if (port == "0") {
                        zero = true;
                        break;
                    }
                    srand (time(NULL));
                    int duration = rand() % 600 + 30;
                    try {
                        cp.addIntervention(year, day, month, duration, spec, port);
                    }
                    catch(NoTechniciansAround &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(PortagemDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(SpecialtyInvalid& e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 5: {
                bool valid = true;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name, spec, port;
                    Specialty s;
                    unsigned int salary;
                    std::cout << "Name of the technician to be hired:\n";
                    std::getline(std::cin, name);
                    if (name == "0") break;
                    if (spec == "Informatics") s = Informatics;
                    else if (spec == "Electronics") s = Electronics;
                    else if (spec == "Revision") s = Revision;
                    else {
                        std::cout << "Invalid specialty\n";
                        valid = false;
                        continue;
                    };
                    std::cout << "Specialty of the technician:\n";
                    std::cin >> spec;
                    if (spec == "0") break;
                    std::cout << "Port the technician should work on\n";
                    std::cin >> port;
                    if (port == "0") break;
                    /*std::cout << "Salary that this technician should be awarded monthly:\n";
                    std::cin >> salary;
                    if (salary == 0) break;*/
                    Technician *t = new Technician(name, s, port);
                    try {
                        cp.hireTechnician(t);
                    }
                    catch (PortagemDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
            }
            case 6: {
                bool valid = true;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name, spec, port;
                    Specialty s;
                    unsigned int salary;
                    std::cout << "Name of the technician to be fired:\n";
                    std::getline(std::cin, name);
                    if (name == "0") break;
                    if (spec == "Informatics") s = Informatics;
                    else if (spec == "Electronics") s = Electronics;
                    else if (spec == "Revision") s = Revision;
                    else {
                        std::cout << "Invalid specialty\n";
                        valid = false;
                        continue;
                    };
                    std::cout << "Specialty of the technician:\n";
                    std::cin >> spec;
                    if (spec == "0") break;
                    std::cout << "Port the technician works on\n";
                    std::cin >> port;
                    if (port == "0") break;
                    /*std::cout << "Salary that this technician should be awarded monthly:\n";
                    std::cin >> salary;
                    if (salary == 0) break;*/
                    Technician *t = new Technician(name, s, port);
                    try {
                        cp.fireTechnician(t);
                    }
                    catch (PortagemDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
            }
            case 7: {
                bool valid, zero = false;
                do {
                    valid = true;
                    std::string name, spec, port;
                    int year, month, day, duration;
                    std::cout << "Year:\n";
                    std::cin >> year;
                    if (year == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Month:\n";
                    std::cin >> month;
                    if (month == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Day:\n";
                    std::cin >> day;
                    if (day == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Specialty:\n";
                    std::cin >> spec;
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Port:\n";
                    std::cin >> port;
                    if (port == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Duration(min):\n";
                    std::cin >> duration;
                    if (day == 0) {
                        zero = true;
                        break;
                    }
                    try {
                        cp.removeIntervention(day, month, year, duration, spec, port);
                    }
                    catch (InterventionDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void workerMenu(CentralPortagens &cp, Worker *w){
    std::cout << "\n\n\nWELCOME " << w->getName() << "\n\n";
    bool exit;
    do {
        exit = false;
        int opt;
        std::cout << "Type the number of the option you wish to execute:\n";
        std::cout << "1-Register vehicle exit\n";
        std::cout << "2-Get my info\n";
        std::cout << "0-Go back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                bool valid;
                do {
                    std::string licensePlate;
                    std::cout << "Vehicle's license plate:\n";
                    std::cin >> licensePlate;
                    if (licensePlate == "0") continue;
                    if (licensePlate.size() != 6) {
                        std::cout << "License plate's length must be 6\n";
                        valid = false;
                        continue;
                    }
                    try {
                        cp.exitVehicle(licensePlate, w->getPort(), w->getHighway());
                    }
                    catch (VehicleNotInTransit &e1) {
                        std::cout << e1.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (HighWayDoesNotExist &e2) {
                        std::cout << e2.getMSG() << std::endl;
                        valid = false;
                    }
                    catch (PortagemDoesNotExist &e3) {
                        std::cout << e3.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 2: {
                w->print();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void updater(CentralPortagens &cp) {
    try {
        fileUpdater<PortagemEntrada*>("EntryPorts.txt", cp.getPortagensE());
        fileUpdater<PortagemSaida*>("ExitPorts.txt", cp.getPortagensS());
        fileUpdater<Vehicle*>("Vehicles.txt", cp.getVehicles());
        fileUpdater<Worker*>("Workers.txt", cp.getWorkers());
        fileUpdater<Technician*>("Technicians.txt", cp.getTechs());
        fileUpdater<Manager*>("Managers.txt", cp.getManagers());
        interventionsFileUpdater(cp.getInterventionsVector());
        fileUpdater("Drivers.txt", cp.getDriversVector());
        fileUpdater("MissbehavedDrivers.txt", cp.getMbDriversVector());
    }
    catch (FileDoesNotExist& e) {
        std::cout << e.getMSG() << std::endl;
    }
    std::cout << "File updated successfully\n";
}

void listingMenu(CentralPortagens &cp) {
    bool exit;
    do {
        int opt;
        exit = false;
        std::cout << "\n\nType the number of the option you wish to execute:\n";
        std::cout << "1-List all vehicles in traffic\n";
        std::cout << "2-List all missbehaved drivers\n";
        std::cout << "3-List all interventions\n";
        std::cout << "4-List all workers\n";
        std::cout << "5-List all managers\n";
        std::cout << "6-List all technicians\n";
        std::cout << "7-List all drivers\n";
        std::cout << "8-List all ports\n";
        std::cout << "9-List all highways\n";
        std::cout << "0-Go back\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                cp.printCurrentVehicles();
                break;
            }
            case 2: {
                cp.printMissbehavedDrivers();
                break;
            }
            case 3: {
                cp.printInterventions();
                break;
            }
            case 4: {
                cp.printWorkers();
                break;
            }
            case 5: {
                cp.printManagers();
                break;
            }
            case 6: {
                cp.printTechs();
                break;
            }
            case 7: {
                cp.printDrivers();
                break;
            }
            case 8: {
                cp.printPortagens();
                break;
            }
            case 9: {
                cp.printHighways();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    } while (!exit);
}

void managerMenu(CentralPortagens &cp, Manager* m) {
    std::cout << "\n\n\n" << "WELCOME " << m->getName() << "\n\n";
    bool exit;
    do{
        exit = false;
        int opt;
        std::cout << "Type the number of the option you wish to execute:\n";
        std::cout << "1-Listing options\n";
        std::cout << "2-Highway options (listing, vehicle entrance, etc.)\n";
        std::cout << "3-Port(portagem) options\n";
        std::cout << "4-Access worker by name\n";
        std::cout << "5-Access worker by ID\n";
        std::cout << "6-Access vehicle\n";
        std::cout << "7-Access technician\n";
        std::cout << "8-Access intervention\n";
        std::cout << "9-Access driver\n";
        std::cout << "10-Update files\n";
        std::cout << "11-Vehicle entrance and exit registry\n";
        std::cout << "12-Personel operations (firing, hiring, changing workers, create interventions, etc.)\n";
        std::cout << "13-Change password\n";
        std::cout << "14-Erase file\n";
        std::cout << "15-Print Registry file\n";
        std::cout << "0-Exit\n";
        std::cin >> opt;
        switch (opt){
            case 1: {
                listingMenu(cp);
                break;
            }
            case 2: {
                HighWay *h;
                bool valid, zero = false;
                do {
                    valid = true;
                    std::string name;
                    std::cout << "Highway name/code (should look something like A(number):\n";
                    std::cin >> name;
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        h = cp.findHighWay(name);
                    }
                    catch(HighWayDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid = false;
                    }
                } while(!valid);
                if (!zero) highwayMenu(cp, h);
                break;
            }
            case 3: {
                bool valid, zero = false;
                do {
                    std::string type;
                    valid = true;
                    std::cout << "Port type(entry or exit):\n";
                    std::cin >> type;
                    if (type == "0") {
                        zero = true;
                        break;
                    }
                    if (type == "entry") {
                        bool valid2;
                        PortagemEntrada *p;
                        do {
                            valid2 = true;
                            std::string name;
                            std::cout << "Port name:\n";
                            std::cin >> name;
                            if (name == "0") {
                                zero = true;
                                break;
                            }
                            try {
                                p = cp.findPortE(name);
                            }
                            catch(PortagemDoesNotExist &e) {
                                std::cout << e.getMSG();
                                valid = false;
                            }
                        } while (!valid2);
                        if (!zero) portEMenu(p);
                    }
                    else if (type == "exit") {
                        bool valid2;
                        PortagemSaida *p;
                        do {
                            valid2 = true;
                            std::string name;
                            std::cout << "Port name:\n";
                            std::cin >> name;
                            if (name == "0") {
                                zero = true;
                                break;
                            }
                            try {
                                p = cp.findPortS(name);
                            }
                            catch(PortagemDoesNotExist &e) {
                                std::cout << e.getMSG();
                                valid = false;
                            }
                        } while (!valid2);
                        if (!zero) portSMenu(p);
                    }
                    else {
                        std::cout << "Invalid type for a port\n";
                        valid = false;
                    }
                } while (!valid);
                break;
            }
            case 4: {
                Worker *w;
                bool valid, zero = false;
                do {
                    valid = true;
                    std::string name;
                    std::cout << "Worker name:\n";
                    std::cin.ignore(1);
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        w = cp.findWorker(name);
                    }
                    catch(WorkerDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid = false;
                    }
                } while (!valid);
                if (!zero) w->print();
                break;
            }
            case 5: {
                Worker *w;
                bool valid, zero = true;
                do {
                    valid = true;
                    unsigned int ID;
                    std::cout << "Worker ID:\n";
                    std::cin >> ID;
                    if (ID == 0) {
                        zero = true;
                        break;
                    }
                    try {
                        w = cp.findWorker(ID);
                    }
                    catch(WorkerDoesNotExist &e) {
                        std::cout << e.getMSG();
                        valid = false;
                    }
                } while (!valid);
                if (!zero) w->print();
                break;
            }
            case 6: {
                Vehicle *v;
                bool valid2, zero = true;
                do {
                    valid2 = true;
                    std::string matricula;
                    std::cout << "Vehicle matricula:\n";
                    std::cin >> matricula;
                    if (matricula == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        v = cp.findVehicle(matricula);
                    }
                    catch(VehicleNotInTransit &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid2 = false;
                    }
                } while(!valid2);
                if (!zero) v->print();
                break;
            }
            case 7: {
                Technician *t;
                bool valid = true, zero = false;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name, spec, port;
                    std::cout << "Technician's name:\n";
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Technician's specialty:\n";
                    std::getline(std::cin, spec);
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Technician's port:\n";
                    std::getline(std::cin, port);
                    if (port == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        t = cp.findTech(name, spec, port);
                    }
                    catch(TechnicianNotFound &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(PortagemDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(SpecialtyInvalid &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                if (!zero) t->print();
                break;
            };
            case 8: {
                std::vector<Intervention> v;
                bool valid, zero = false;
                do {
                    valid = true;
                    std::string name, spec, port;
                    int year, month, day;
                    float duration;
                    std::cout << "Year:\n";
                    std::cin >> year;
                    std::cout << year << " ";
                    if (year == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Month:\n";
                    std::cin >> month;
                    std::cout << month << " ";
                    if (month == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Day:\n";
                    std::cin >> day;
                    std::cout << day << " ";
                    if (day == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Duration:\n";
                    std::cin >> duration;
                    if (duration == 0) {
                        zero = true;
                        break;
                    }
                    std::cout << "Specialty:\n";
                    std::cin >> spec;
                    if (spec == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Port:\n";
                    std::cin >> port;
                    if (port == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        v = cp.findIntervention(port, year, month, day, duration, spec);
                    }
                    catch(InterventionDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    catch(SpecialtyInvalid &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
                if (!zero) {
                    for (auto i : v) i.print();
                }
                break;
            }
            case 9: {
                Driver *d;
                bool valid = true, zero = false;
                do {
                    if (valid) std::cin.ignore(1);
                    valid = true;
                    std::string name;
                    std::cout << "Driver's name:\n";
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        d = cp.findDriver(name);
                    }
                    catch(DriverNotFound &e) {
                        std::cout << e.getMSG();
                        valid = false;
                    }
                } while (!valid);
                if (!zero) d->print();
                break;
            }
            case 10: {
                updater(cp);
                break;
            }
            case 11: {
                cpVehicleOperationsMenu(cp);
                break;
            }
            case 12: {
                cpPersonelOperationsMenu(cp);
                break;
            }
            case 13: {
                std::string newPassword;
                std::cout << "New password:\n";
                std::cin >> newPassword;
                m->changePassword(newPassword);
                break;
            }
            case 14: {
                bool valid;
                do {
                    valid = true;
                    std::string fileName;
                    std::cout << "File name:\n";
                    std::cin >> fileName;
                    try {
                        clearFile(fileName);
                    }
                    catch (FileDoesNotExist& e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                } while (!valid);
            }
            case 15: {
                printRegistry();
                break;
            }
            case 0: {
                exit = true;
                break;
            }
            default: {
                std::cout << "Invalid option code, please try again\n";
                break;
            }
        }
    }while(!exit);
}

void menu(CentralPortagens &cp) {
    bool exit;
    do {
        unsigned int opt;
        exit = false;
        std::cout << "\n\nType the number of the option you wish to execute:\n";
        std::cout << "1-Enter as manager (names and passwords in Managers.txt)\n";
        std::cout << "2-Enter as worker(worker must be active)\n";
        std::cout << "0-Exit\n";
        std::cin >> opt;
        switch (opt) {
            case 1: {
                bool valid, zero = false;
                Manager *m;
                do {
                    valid = true;
                    std::string name, password;
                    std::cout << "Name:\n";
                    std::cin.ignore(1);
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    std::cout << "Password:\n";
                    std::cin >> password;
                    if (password == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        m = cp.findManager(name);
                    }
                    catch (ManagerDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    if (m->getPassword() != password) {
                        std::cout << "Wrong username-password combination\n";
                        valid = false;
                    }
                } while (!valid);
                if (!zero) managerMenu(cp, m);
                break;
            }
            case 2: {
                bool valid, zero = false;
                Worker *w;
                do {
                    valid = true;
                    std::string name, portType;
                    std::cout << "Name:\n";
                    std::cin.ignore(1);
                    std::getline(std::cin, name);
                    if (name == "0") {
                        zero = true;
                        break;
                    }
                    try {
                        w = cp.findWorker(name);
                    }
                    catch (WorkerDoesNotExist &e) {
                        std::cout << e.getMSG() << std::endl;
                        valid = false;
                    }
                    if (!w->getActive()) {
                        std::cout << "This worker is not active\n";
                        valid = false;
                    }
                } while (!valid);
                if (!zero) workerMenu(cp, w);
                break;
            }
            case 0: {
                exit = true;
                break;
            }
        }
    } while (!exit);

}

int main() {

    CentralPortagens cp("Central Portguesa de Portagens");
    createCentral(cp);
    menu(cp);
    updater(cp);

    return 0;
}

#ifndef UNTITLED2_EXCEPTIONS_H
#define UNTITLED2_EXCEPTIONS_H

#endif //UNTITLED2_EXCEPTIONS_H
#include <string>
#include <sstream>

/// ---Exception ManagerDoesNotExist---
class ManagerDoesNotExist {
    std::string message;
public:
    ManagerDoesNotExist(std::string managerName) {
        std::stringstream ss;
        ss << managerName << "is not a manager";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception WorkerIsActive---
class WorkerIsActive {
    std::string message;
public:
    WorkerIsActive(std::string name) {
        std::stringstream ss;
        ss << name << " is already active";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception WorkerIsNotActive---
class WorkerIsNotActive {
    std::string message;
public:
    WorkerIsNotActive(std::string name) {
        std::stringstream ss;
        ss << name << " is not active";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception WayIsViaverde---
class WayIsViaverde{
    std::string message;
public:
    WayIsViaverde(int n) {
        std::stringstream ss;
        ss << "Way number " << n << " is viaverde";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception NotEnoughWorkers---
class NotEnoughWorkers{
    std::string message;
public:
    NotEnoughWorkers() {
        std::stringstream ss;
        ss << "Not enough workers this entreprise";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};

/// ---Exception HighWayDoesNotExist---
class HighWayDoesNotExist{
    std::string message;
public:
    HighWayDoesNotExist(std::string name){
        std::stringstream ss;
        ss << "Highway " << name << " does not exist";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception PortagemDoesNotExist---
class PortagemDoesNotExist{
    std::string message;
public:
    PortagemDoesNotExist(std::string portName) {
        std::stringstream ss;
        ss << "Portagem " << portName << " does not exist or was not found";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception WayDoesNotExist---
class WayDoesNotExist {
    std::string message;
public:
    WayDoesNotExist(std::string port, unsigned int number) {
        std::stringstream ss;
        ss << "Way " << number << " does not exist in port " << port;
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception WorkerDoesNotExist---
class WorkerDoesNotExist{
    std::string message;
public:
    WorkerDoesNotExist(std::string name, std::string port) {
        std::stringstream ss;
        ss << "Worker " << name << " does not work in " << port;
        message = ss.str();
    }
    WorkerDoesNotExist(unsigned int ID, std::string port) {
        std::stringstream ss;
        ss << "Worker " << ID << " does not work in " << port;
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};

/// ---Exception VehicleNotInTransit---
class VehicleNotInTransit{
    std::string message;
public:
    VehicleNotInTransit(std::string matricula, std::string highway) {
        std::stringstream ss;
        ss << "Vehicle " << matricula << " is not in transit in " << highway;
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception TechnicianNotFound---
class TechnicianNotFound {
    std::string message;
public:
    TechnicianNotFound(std::string name, std::string specialty, std::string port) {
        std::stringstream ss;
        ss << specialty << " technician " << name << " does not exist in port " << port;
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception DriverNotFound---
class DriverNotFound {
    std::string message;
public:
    DriverNotFound(std::string name) {
        std::stringstream ss;
        ss << "Driver " << name << " does not exist in the database";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception SpecialtyInvalid---
class SpecialtyInvalid {
    std::string message;
public:
    SpecialtyInvalid(std::string spec) {
        std::stringstream ss;
        ss << spec << " is not a valid specialty";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception InterventionDoesNotExist---
class InterventionDoesNotExist {
    std::string message;
public:
    InterventionDoesNotExist() {
        message = "Such an intervention does not exist";
    }
    std::string getMSG() const {return message;}
};
/// ---Exception NoTechniciansAround---
class NoTechniciansAround {
    std::string message;
public:
    NoTechniciansAround(std::string port, std::string spec) {
        std::stringstream ss;
        ss << "No "<< spec << " technicians near port " << port;
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
/// ---Exception FileDoesNotExist---
class FileDoesNotExist {
    std::string message;
public:
    FileDoesNotExist(std::string name) {
        std::stringstream ss;
        ss << "File with name " << name << " does not exist";
        message = ss.str();
    }
    std::string getMSG() const {return message;}
};
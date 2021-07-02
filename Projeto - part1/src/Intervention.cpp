//
// Created by marhc on 29/12/2020.
//

#include "Intervention.h"

Intervention::Intervention (int day, int month, int year, int duration, Technician *tech, std::string port, Specialty type) :
duration (duration), tech (tech), port (port), type (type) {
    this->date.month = month;
    this->date.day = day;
    this->date.year = year;
}

void Intervention::setTech(Technician *tech) {
    this->tech = tech;
}

bool Intervention::operator<(const Intervention &interv) const {
    if (this->date.year != interv.date.year) return this->date.year < interv.date.year;
    else if (this->date.month != interv.date.month) return this->date.month < interv.date.month;
    else if (this->date.day != interv.date.day) return this->date.day < interv.date.day;
    else if (this->port != interv.port) return this->port < interv.port;
    else return this->type < interv.type;
}

bool Intervention::operator==(const Intervention &interv) const {
    return date.year == interv.date.year && date.month == interv.date.month && date.day == interv.date.day &&
    type == interv.type && port == interv.port && duration == interv.duration;
}

void Intervention::print() const {
    std::cout << "Date: " << date.day << "-" << date.month << "-" << date.year << " | ";
    std::cout << "Port: " << port << " | " << "Type: " << getTypeString() << " | ";
    std::cout << "Duration: " << duration << " | " << "Technician: " << getTech()->getName() << std::endl;
}

std::string Intervention::getTypeString() const {
    switch (type) {
        case Informatics: return "Informatics";
        case Electronics: return "Electronics";
        case Revision: return "Revision";
        default: return "error";
    }
}

std::ostream& operator<< (std::ostream& os, const Intervention& interv) {
    os << interv.getTech()->getName() << std::endl;
    os << interv.port;
    os << " " << interv.date.year << " " << interv.date.month << " " << interv.date.day << " " << interv.duration << " " <<
    interv.getTypeString() << " " << interv.tech->getName();
    return os;
}

std::istream& operator>> (std::istream& is, Intervention& interv) {
    std::string typeString, techName, port;
    Specialty spec;
    std::getline (is, techName);
    is >> port >> interv.date.year >> interv.date.month >> interv.date.day >> interv.duration >> typeString;
    if (typeString == "Informatics") spec = Informatics;
    else if (typeString == "Electronics") spec = Electronics;
    else spec = Revision;
    interv.type = spec;
    interv.port = port;
    interv.setTech(new Technician (techName, spec, port));
    return is;
}

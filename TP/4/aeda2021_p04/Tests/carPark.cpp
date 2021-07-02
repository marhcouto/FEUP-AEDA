#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}


int CarPark::clientPosition(const string & name) const
{
    InfoCard client;
    client.name = name;
    return sequentialSearch<InfoCard>(clients, client);
}


unsigned CarPark::getFrequency(const string &name) const
{
    for(auto client : clients){
        if (client.name == name) return client.frequency;
    }
    throw ClientDoesNotExist (name);
}


bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency = 0;
    clients.push_back(info);
    return true;
}


bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}


bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}


bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}



InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    if(p > clients.size() - 1 || p < 0)
        throw PositionDoesNotExist(p);
    else
        info = clients[p];
    return info;
}


void CarPark::sortClientsByFrequency()
{
    insertionSort<InfoCard>(clients);
}


void CarPark::sortClientsByName()
{
    bool trade;
    InfoCard tmp;
    for (unsigned int p = clients.size() - 1; p > 0; p--) {
        trade = false;
        for (unsigned int q = 0; q < p; q++)
            if(clients[q].name > clients[q+1].name){
                tmp = clients[q];
                clients[q] = clients[q+1];
                clients[q+1] = tmp;
                trade = true;
            }
        if(!trade) break;
    }
}


vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    insertionSort<InfoCard>(clients);
    for(std::vector <InfoCard>::const_iterator it = clients.begin(); it != clients.end(); it++){
        if(it->frequency >= f1 and it->frequency <= f2) names.push_back(it->name);
        if(it->frequency > f2) break;
    }
    return names;
}



ostream & operator<<(ostream & os, const CarPark & cp)
{
    std::vector <InfoCard> :: const_iterator it;
    for(it = cp.clients.begin(); it != cp.clients.end(); it++)
        os << "Name: " << it->name << " Freq: " << it->frequency << " Present: " << it->present << std::endl;
    return os;
}

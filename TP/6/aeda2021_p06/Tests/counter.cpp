#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
#include <time.h>
using namespace std;


Client::Client() {
    srand(time(NULL));
    numGifts = rand() % 5 + 1;
}


unsigned Client::getNumGifts() const {
    return numGifts;
}


Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    srand(time(NULL));
    nextEnter = rand() % 20 + 1;
    nextLeave = 0;
    numAttendedClients = 0;
}


unsigned Counter::getActualTime() const {
    return actualTime;
}


unsigned Counter::getNextEnter() const {
    return nextEnter;
}


unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}


unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}


unsigned Counter::getNextLeave() const {
    return nextLeave;
}


Client & Counter::getNextClient() {
    if(clients.empty()) throw EmptyQueue();
    return clients.front();
}


void Counter::enter()
{
    Client c1;
    bool empt = clients.empty();
    clients.push(c1);
    srand(time(NULL));
    nextEnter = rand() % 20 + 1;
    if(empt) nextLeave = c1.getNumGifts() * wrappingTime + actualTime;
    std::cout << "time = " << actualTime << std::endl << "New costumer arrived with " << c1.getNumGifts() << " gifts.\n\n";
}


void Counter::leave()
{
    if(clients.empty()) throw EmptyQueue();
    Client c1 = clients.front();
    clients.pop();
    numAttendedClients++;
    nextLeave = clients.front().getNumGifts() * wrappingTime + actualTime;
    std::cout << "time: " << actualTime << std::endl << "Customer left with " << c1.getNumGifts() << " gifts wrapped.\n\n";
}


void Counter::nextEvent()
{
    if(clients.empty()) enter();
    else if(nextEnter < nextLeave){
        actualTime = nextEnter;
        Counter::enter();
    }
    else {
        actualTime = nextLeave;
        Counter::leave();
    }
}



ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Número de clientes atendidos: " << c2.getNumAttendedClients() << std::endl
    << "Número de clientes em espera: " << c2.clients.size() << "\n\n";
    return out;
}



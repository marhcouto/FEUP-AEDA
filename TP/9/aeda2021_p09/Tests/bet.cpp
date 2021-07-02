#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
    if (numbers.count(num) == 0) return false;
    else return true;
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    for (auto it = values.begin(); it != values.end() && n > 0; it++) {
        if (!contains(*it)) {
            numbers.insert(*it);
            n--;
        }
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
    unsigned count = 0;
    for (auto num : draw) {
        if (contains(num)) count++;
    }
    return count;
}

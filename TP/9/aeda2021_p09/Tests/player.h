#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;


struct betHash
{
	int operator() (const Bet& b) const
	{
	    int hashVal = 0;
	    for (tabHInt::const_iterator it = b.getNumbers().begin(); it != b.getNumbers().end(); it++) {
	        hashVal = 37 * hashVal + (*it);
	    }
		return hashVal;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
	    if (b1.getNumbers().size() != b2.getNumbers().size()) return false;
	    if (b1.countRights(b2.getNumbers()) == b1.getNumbers().size()) return true;
	    else return false;
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 

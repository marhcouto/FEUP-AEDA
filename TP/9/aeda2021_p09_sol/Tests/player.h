#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

struct betHash
{
	int operator() (const Bet& b) const
	{
	    tabHInt nums = b.getNumbers();
	    tabHInt::iterator it= nums.begin();
	    int v=0;
	    while (it!=nums.end()) {
	        v =37*v+(*it);
	        it++;
	    }
	    return v;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		if ( b1.size() != b2.size() )
			return false;
		unsigned int n = b1.countRights(b2.getNumbers());
		if ( n == b1.size() )
			return true;
		else
			return false;
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

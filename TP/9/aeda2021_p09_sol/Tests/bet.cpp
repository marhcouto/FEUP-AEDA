#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;

bool Bet::contains(unsigned num) const
{
	tabHInt::const_iterator it = numbers.find(num);
	if (it == numbers.end())
		return false;
	else
		return true;
}


void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
	numbers.clear();
	unsigned nVals=0, i=0;
	while (nVals<n) {
		pair<tabHInt::iterator, bool> res = numbers.insert(values[i]);
		if ( res.second == true)
			nVals++;
		i++;
	}
}


unsigned Bet::countRights(const tabHInt& draw) const
{
	unsigned rights = 0;
	for ( tabHInt::const_iterator it = draw.begin();
					it != draw.end(); it++ ) {
		if ( contains(*it) )
			rights++;
	}
	return rights;
}


unsigned Bet::sumNumbers() const
{
	unsigned sum = 0;
	for (tabHInt::const_iterator it = numbers.begin();
					it != numbers.end(); it++ )
		sum +=* it;
	return sum;
}

unsigned Bet::size() const
{
	return numbers.size();
}




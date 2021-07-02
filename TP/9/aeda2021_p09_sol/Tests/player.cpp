#include "player.h"

void Player::addBet(const Bet& b)
{
	bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const
{
	unsigned count = 0;
	for( tabHBet::const_iterator it = bets.begin(); it != bets.end(); it++) {
        if ((*it).contains(num))
            count++;
    }
	return count;
}


tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	res.clear();
	for( tabHBet::const_iterator it = bets.begin(); it != bets.end(); it++) {
	    if ((*it).countRights(draw) > 3)
	        res.insert(*it);
	}
	return res;
}

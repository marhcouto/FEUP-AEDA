#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}


Game::Game() {}


Game::Game(list<Kid>& l2) : kids(l2){};


void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}


list<Kid> Game::getKids() const {return kids;}

string Game::write() const
{
    ostringstream ss;
    list<Kid>::const_iterator it;
    for(it = kids.begin(); it != kids.end(); it++)
        ss << it->write() << "\n";
    return ss.str();
}


Kid& Game::loseGame(string phrase)
{
    list<Kid> k = kids;
    list<Kid>::const_iterator it = k.begin();
    int nWords = (numberOfWords(phrase) - 1);

    while (k.size() > 1){
        for(unsigned n = 0; n < nWords % k.size(); n++)
            if ((it++) == k.end()) it = k.begin();
        it = k.erase(it);
        if(it == k.end())
            it = k.begin();
    }
    return const_cast<Kid &>(*it);
}


list<Kid>& Game::reverse()
{
    list<Kid>::const_reverse_iterator rev;
    list<Kid> k;
    for (rev = kids.rbegin(); rev != kids.rend(); rev++)
        k.push_back((*rev));
    kids = k;
    return kids;
}


list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    list<Kid>::const_iterator it;
    for (it = kids.begin(); it != kids.end();){
        if (it->getAge() > id){
            res.push_back((*it));
            it = kids.erase(it);
        }
        else
            it++;
    }
    return res;
}


void Game::setKids(const list<Kid>& l1) {
    kids = l1;
}


bool Game::operator==(Game& g2)
{
    if (kids.size() != g2.getKids().size()) return false;
    list<Kid>::const_iterator it1, it2;
    it1 = kids.begin(); it2 = g2.kids.begin();
    while(it1 != kids.end() && it2 != g2.kids.end()){
        if ((*it1) == (*it2)) ;
        else{
            return false;
        }
        it1++; it2++;
    }
	return true;
}


list<Kid> Game::shuffle() const
{
    int n;
    std::list<Kid>::const_iterator it;
    std::list<Kid> copyKids = kids;
    std::list<Kid> res;
    while (!copyKids.empty()){
        srand(time(0));
        it = copyKids.begin();
        n = rand() % copyKids.size();
        std::advance(it, n);
        res.push_back((*it));
        copyKids.erase(it);
    }
    return res;
}

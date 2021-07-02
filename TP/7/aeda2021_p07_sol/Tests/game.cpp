#include "game.h"
#include <sstream>


ostream &operator << (ostream &os, Circle &c1)
{
	string stateStr;
	if (c1.state) stateStr="true"; else stateStr="false";
	os << c1.points << "-" << stateStr  << "-" << c1.nVisits << endl;
	return os;
}


BinaryTree<Circle> Game::initiateGame(int pos, int level, vector<int> &points, vector<bool> &states)
{
	Circle c1(points[pos],states[pos]);
	if (level==0) return BinaryTree<Circle>(c1);
	BinaryTree<Circle> leftChild = initiateGame(2 * pos + 1, level - 1, points, states);
	BinaryTree<Circle> rightChild = initiateGame(2 * pos + 2, level - 1, points, states);
	return BinaryTree<Circle>(c1, leftChild, rightChild);
}


Game::Game(int h, vector<int> &points, vector<bool> &states)
{
	game=initiateGame(0,h,points,states);
}


string Game::writeGame()
{
	BTItrLevel<Circle> it(game);
	stringstream gameStr("");
	while (!it.isAtEnd()) {
		gameStr << it.retrieve();
		it.advance();
	}
	return gameStr.str();
}


int Game::move()
{
	int pos=1; int nPoints=-1;
	BTItrLevel<Circle> it(game);
	if (it.isAtEnd()) return nPoints;
	while (true) {
		Circle &c1=it.retrieve();
		bool state=c1.getState();
		int n;
		if (state==false) n=pos;
		else n=pos+1;
		c1.changeState();
		c1.incNVisits();
		nPoints=c1.getPoints();
		int i=0;
		while(i<n && !it.isAtEnd()) {
			it.advance();        // advances to left or right child
			i++;
		}
		if (!it.isAtEnd()) pos+=n;
		else break;
	}
	return nPoints;
}


int Game::mostVisited()
{
	BTItrLevel<Circle> it(game);
	if (it.isAtEnd()) return -1;
	int moreVisits=-1;
	it.advance();
	while (!it.isAtEnd()) {
		Circle c1=it.retrieve();
		int nV=c1.getNVisits();
		if (nV>moreVisits) moreVisits=nV;
		it.advance();
	}
	return moreVisits;
}

#include "game.h"
#include <sstream>



ostream &operator << (ostream &os, Circle &c1)
{
    os << c1.getPoints() << "-" << (c1.getState() ? "true" : "false") << "-" << c1.getNVisits() << std::endl;
	return os;
}

BinaryTree<Circle> Game::initGame(int pos, int h, vector<int> &points, vector<bool> &states) {
    Circle c(points[pos], states[pos]);
    if (h == 0) return BinaryTree<Circle>(c);
    BinaryTree<Circle> left = initGame(2*pos + 1, h - 1, points, states);
    BinaryTree<Circle> right = initGame(2*pos + 2, h - 1, points, states);
    return BinaryTree<Circle>(c, left, right);
}

Game::Game(int h, vector<int> &points, vector<bool> &states) {
    game = initGame(0, h, points, states);
}



string Game::writeGame()
{
    std::stringstream ss ("");
    BTItrLevel<Circle> it (game);
    while (!it.isAtEnd()) {
        ss << it.retrieve();
        it.advance();
    }
    return ss.str();
}


int Game::move()
{
    int score, pos = 0, h = 0;
	BTItrLevel<Circle> it (game);
	while (true) {
	    it.retrieve().incVisits();
	    score = it.retrieve().getPoints();
        int i = pos;
	    if (it.retrieve().getState()) pos = pos * 2 + 2;
	    else pos = pos * 2 + 1;
        it.retrieve().changeState();
        for (; i < pos && !it.isAtEnd(); i++) it.advance();
        if (it.isAtEnd()) break;
	}
	return score;
}



int Game::mostVisited()
{
    int maxV = -1;
	BTItrLevel<Circle> it (game);
    if (it.isAtEnd()) return -1;
	it.advance();
	while (!it.isAtEnd()) {
        if (it.retrieve().getNVisits() > maxV) maxV = it.retrieve().getNVisits();
        it.advance();
    }
	return maxV;

}

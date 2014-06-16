#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"

#include <set>

class Player{
public:
	virtual void playTurn() = 0;
	virtual ~Player();
	int getScore();
	int getHandSize();
private:
	std::set<Card*> _hand;
	std::set<Card*> _discards;
	int _score;
};

#endif
#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

typedef std::set<Card*, bool(*)(const Card*& lhs, const Card*& rhs)> CardSet;

class HumanPlayer: public Player{
public:
	HumanPlayer(CardSet*);
	~HumanPlayer(){};
	void playTurn();
};

#endif
#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

typedef std::set<Card*, bool(*)(const Card*& lhs, const Card*& rhs)> CardSet;

class ComputerPlayer: public Player{
public:
	ComputerPlayer(CardSet*);
	~ComputerPlayer(){};
	void playTurn();
};

#endif
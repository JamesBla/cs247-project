#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include <map>

class HumanPlayer: public Player{
public:
	HumanPlayer(std::map<Card*, bool>*);
	~HumanPlayer(){};
	void playTurn();
};

#endif
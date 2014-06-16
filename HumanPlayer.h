#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

class HumanPlayer: public Player{
public:
	~HumanPlayer(){};
	void playTurn();
};

#endif
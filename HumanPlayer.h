#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "Card.h"
#include "View.h"

#include <map>

class HumanPlayer: public Player{
public:
	HumanPlayer(View* view);
	~HumanPlayer(){};
	void playTurn(bool (&cardMap)[4][13]);
};

#endif
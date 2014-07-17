#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

class Model;
class Controller;

class HumanPlayer: public Player{
public:
	HumanPlayer(Model* model, Controller* controller, int playerNumber);
	virtual bool isHuman() const;
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
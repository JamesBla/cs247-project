#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

class Model;
class View;
class Controller;

class HumanPlayer: public Player{
public:
	HumanPlayer(Model* model, View* view, Controller* controller, int playerNumber);
	virtual bool isHuman() const;
	void playTurn(bool (&cardMap)[4][13]);
};

#endif
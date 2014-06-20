#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include <map>

class Model;
class View;
class Controller;
class Card;

class HumanPlayer: public Player{
public:
	HumanPlayer(Model* model, View* view, Controller* controller, int playerNumber);
	~HumanPlayer(){};
	void playTurn(bool (&cardMap)[4][13]);
};

#endif
#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "HumanPlayer.h"

class Model;
class View;
class Controller;

class ComputerPlayer: public Player{
public:
	ComputerPlayer(Model* model, View* view, Controller* controller, int playerNumber);
	ComputerPlayer(const HumanPlayer&);
	void playTurn(bool (&cardMap)[4][13]);
};

#endif
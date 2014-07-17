#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "HumanPlayer.h"

class Model;
class Controller;

class ComputerPlayer: public Player{
public:
	ComputerPlayer(Model* model, Controller* controller, int playerNumber);
	ComputerPlayer(const Player&);
	virtual bool isHuman() const;
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
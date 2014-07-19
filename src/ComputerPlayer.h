#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class Model;

class ComputerPlayer: public Player{
public:
	ComputerPlayer(Model* model, int playerNumber);
	ComputerPlayer(const Player&);
	virtual bool isHuman() const;
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
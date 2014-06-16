#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

#include <map>

class ComputerPlayer: public Player{
public:
	ComputerPlayer(std::map<Card*, bool>*);
	~ComputerPlayer(){};
	void playTurn();
};

#endif
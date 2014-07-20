#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class Model;

class ComputerPlayer: public Player{
public:
	ComputerPlayer(Model* model, int playerNumber);
	ComputerPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);
	ComputerPlayer(const Player&);
	virtual bool isHuman() const;
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
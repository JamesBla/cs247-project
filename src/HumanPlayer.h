#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

class Model;

class HumanPlayer: public Player{
public:
	HumanPlayer(Model* model, int playerNumber);
	HumanPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);
	virtual bool isHuman() const;
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
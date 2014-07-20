#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"

class Model;

class HumanPlayer: public Player{
public:
	// Standard constructor
	HumanPlayer(Model* model, int playerNumber);
	// Constructor used for importing from gamesave
	HumanPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);
	virtual bool isHuman() const;
	// plays turn and return TRUE if play or discard is valid, else return FALSE
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
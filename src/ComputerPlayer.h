#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class Model;

class ComputerPlayer: public Player{
public:
	// Standard constructor
	ComputerPlayer(Model* model, int playerNumber);
	// Constructor used for importing from gamesave
	ComputerPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);
	// Copy-constructor used for computerizing human player
	ComputerPlayer(const Player&);
	virtual bool isHuman() const;
	// uses simple AI algorithm to play a card
	bool playTurn(Card*, bool (&cardMap)[4][13]);
};

#endif
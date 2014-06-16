#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Card.h"
#include "Player.h"

class View;
class Controller;

class Model{

public:
	~Model();
	static int getPlayerCount();
	void setPlayers(char[]);
	void playGame();
	int getMaxScore();
	void initializeDeck();
	void shuffle();
private:
	static const int PLAYER_COUNT;
	static const int CARD_COUNT;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	// int firstPlayer;
};

#endif
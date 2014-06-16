#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Card.h"
#include "Player.h"
#include "View.h"

class View;
class Controller;

class Model{

public:
	~Model();
	void setView(View*);

	static int getPlayerCount();
	void setPlayers(char[]);
	void playGame();
	int getMaxScore() const;
	void initializeDeck();
	void shuffle();
	void deal();
private:
	static const int PLAYER_COUNT;
	static const int CARD_COUNT;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	View* _view;
	// int firstPlayer;
};

#endif
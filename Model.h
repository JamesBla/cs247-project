#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <map>

#include "Controller.h"
#include "Card.h"
#include "Player.h"
#include "View.h"

class View;
class Controller;
class Player;

class Model{
public:
	~Model();
	void setView(View*);
	void setController(Controller*);
	static int getPlayerCount();
	void setPlayers(char[]);
	void playGame();
	int getMaxScore() const;
	void initializeDeck();
	void shuffle();
	void deal();
	void putCardOnTable(Card*&);
	std::vector<Card*> getDeck() const;
private:
	static const int PLAYER_COUNT;
	static const int CARD_COUNT;
	Controller* _controller;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	View* _view;
	bool _playedCards[4][13];
};

#endif
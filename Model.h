#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <map>

#include "Controller.h"
#include "Card.h"
#include "Player.h"
#include "HumanPlayer.h"
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
	void initializeDeck();
	void shuffle();
	void deal();
	void putCardOnTable(Card*&);
	std::vector<Card*> getDeck() const;
	void cleanUp();
	void computerizePlayer(HumanPlayer*);
	void clearCardsOnTable();
	Card* findCard(Card*) const;
	int getWinner() const;
	static const Card* sevenOfSpades();
private:
	static const int PLAYER_COUNT;
	static const int CARD_COUNT;
	static const Card SEVEN_OF_SPADES;
	Controller* _controller;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	int _curPlayer;
	View* _view;
	bool _playedCards[4][13];
};

#endif
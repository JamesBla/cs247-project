#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "subject.h"

class View;
class Controller;

class Player;
class HumanPlayer;
class Card;

class Model : public Subject{
public:
	~Model();
	// void setView(View*);
	void setController(Controller*);
	static int getPlayerCount();
	void initializePlayers(char[]);
	void playGame();
	void initializeDeck();
	void shuffle();
	void deal();
	void putCardOnTable(Card*);
	std::vector<Card*> getDeck() const;
	void cleanUp();
	void computerizePlayer(HumanPlayer*);
	void clearCardsOnTable();
	Card* findCard(Card*) const;
	std::vector<Player*> getWinners() const;
	static const Card* sevenOfSpades();
	bool isStartOfNewRound() const;
	bool isRoundInProgress() const;
	bool isRoundFinished() const;
	Player* getFirstPlayer() const;
	Player* getCurrentPlayer() const;
	Player* getPlayer(int) const;
	int getPlayerScore(int) const;
	int getPlayerDiscardedCount(int) const;
	std::vector<Card*> getDiscardedCards(int) const;
	
	void playATurn(Card* card);
	bool beenPlayed(int rank, int suit) const;

private:
	static const int PLAYER_COUNT;
	static const int CARD_COUNT;
	static const Card SEVEN_OF_SPADES;
	Controller* _controller;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	int _curPlayer;
	bool _playedCards[4][13];
	void playRound();
	bool startOfNewRound;
	bool roundInProgress;
	bool roundEnded;
};

#endif
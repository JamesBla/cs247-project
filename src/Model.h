#ifndef _MODEL_
#define _MODEL_

#include <vector>

#include "Subject.h"

class View;

class Player;
class HumanPlayer;
class Card;

class Model : public Subject{
public:
	virtual ~Model();

	enum State { NONE, ROUND_STARTED, IN_PROGRESS, ROUND_ENDED, GAME_ENDED, RESET_VIEW };

	void initializePlayers(char[]);
	void initializeDeck();
	void shuffle();
	void deal();
	void putCardOnTable(Card*);
	std::vector<Card*> getDeck() const;
	void cleanUp();
	void computerizePlayer(Player*);
	void clearCardsOnTable();
	Card* findCard(Card*) const;
	std::vector<Player*> getWinners() const;
	static const Card* sevenOfSpades();
	bool beenPlayed(int rank, int suit) const;

	void clear();
	bool resetView() const;
	bool doneGame() const;

	std::vector<Card*> getLegalPlays(Player*);

	// Accessors
	State getState() const;
	Player* getFirstPlayer() const;
	Player* getCurrentPlayer() const;
	Player* getPlayer(int) const;
	int getPlayerScore(int) const;
	int getPlayerCurrentRoundScore(int) const;
	int getPlayerDiscardedCount(int) const;
	std::vector<Card*> getDiscardedCards(int) const;

	// Modifiers
	void setState(State state);
	void setCurrentPlayer(int);

	void updateScoreAndEndGame();
	bool playTurn(Card*);
	void advanceCurrentPlayer();

private:
	static const Card SEVEN_OF_SPADES;
	
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	int _curPlayer;
	bool _playedCards[4][13];
	State _state;
	bool _doneGame;
};

#endif
#ifndef _MODEL_
#define _MODEL_

#include <vector>
#include <fstream>

#include "Subject.h"

class Player;
class Card;

class Model : public Subject{
public:
	Model();
	virtual ~Model();

	enum State { NONE, ROUND_STARTED, IN_PROGRESS, ROUND_ENDED, GAME_ENDED, RESET_VIEW };

	// Accessors
	static const Card* sevenOfSpades();
	Card* findCard(Card*) const;
	bool beenPlayed(int rank, int suit) const;
	std::vector<Player*> getWinners() const;
	State getState() const;
	Player* getFirstPlayer() const;
	Player* getCurrentPlayer() const;
	Player* getPlayer(int) const;
	int getPlayerScore(int) const;
	int getPlayerCurrentRoundScore(int) const;
	int getPlayerDiscardedCount(int) const;
	std::vector<Card*> getDeck() const;
	std::vector<Card*> getDiscardedCards(int) const;
	std::vector<Card*> getLegalPlays(Player*);
	int getSeed() const;
	char getPlayerType(int) const;

	// Modifiers
	void initializePlayers();
	void initializeDeck();
	void shuffle();
	void deal();
	void putCardOnTable(Card*);
	void computerizePlayer(int);
	void updateScoreAndEndGame();
	bool playTurn(Card*);
	void advanceCurrentPlayer();
	void setState(State state);
	void setCurrentPlayer(int);
	void setSeed(int);
	void setPlayerType(int, char);
	void cleanUp();
	void clearCardsOnTable();
	void deleteCardsAndPlayers();
	void exportModel(std::ofstream&);
	void reconstructModel(std::ifstream&);

private:
	static const Card SEVEN_OF_SPADES;
	std::vector<Player*> _players;
	std::vector<Card*> _deck;
	int _firstPlayer;
	int _curPlayer;
	bool _playedCards[4][13];
	State _state;
	int _seed;
	char _playerTypes[4];
};

#endif
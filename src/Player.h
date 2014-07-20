#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <ostream>
#include <istream>

class Model;

class Card;

class Player{
public:
	Player(Model*, int);										// Standard constructor
	virtual ~Player();
	Player(const Player&);										// Copy-constructor

	Player(Model*, int score, int roundScore, 					// Constructor used for importing from gamesave
		int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);

	virtual bool playTurn(Card*, bool (&cardMap)[4][13]) = 0;	// plays a turn
	virtual bool isHuman() const = 0;

	int getScore() const;
	int getRoundScore() const;
	int getOldScore() const;
	int getHandSize() const;

	void addCard(Card*);										// adds card to hand
	void playCard(Card*);										// plays card and puts it on table
	void discard(Card*);										// discards card

	int getNumber() const;
	void updateScore();											// updates score
	void prepForNewRound();										// resets player for new round
	std::vector<Card*> getHand() const;
	std::vector<Card*> getDiscarded() const;
	int getDiscardedCount() const;
	std::vector<Card*> getLegalPlays(bool (&cardMap)[4][13]) const;

	Model* getModel() const;
protected:
	bool playable(Card*, bool (&cardMap)[4][13]) const;
private:
	std::vector<Card*> _hand;
	std::vector<Card*> _discards;
	int _score;
	int _roundScore;
	int _oldScore;
	int _playerNumber;
	Model* _model;
};

std::ostream &operator<<(std::ostream &, const Player &);		// streaming operator for persisting player in saved game

#endif
#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <ostream>
#include <istream>

class Model;

class Card;

class Player{
public:
	Player(Model*, int);
	virtual ~Player();
	Player(const Player&);

	Player(Model*, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards);

	virtual bool playTurn(Card*, bool (&cardMap)[4][13]) = 0;
	virtual bool isHuman() const = 0;

	int getScore() const;
	int getRoundScore() const;
	int getOldScore() const;
	int getHandSize() const;

	void addCard(Card*);
	void playCard(Card*);
	void discard(Card*);

	int getNumber() const;
	void updateScore();
	void prepForNewRound();
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

// For persisting player in saved game
std::ostream &operator<<(std::ostream &, const Player &);
std::istream &operator>>(std::istream &, Player &);
#endif
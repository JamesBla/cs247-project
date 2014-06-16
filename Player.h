#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"

#include <set>

typedef std::set<Card*, bool(*)(const Card*& lhs, const Card*& rhs)> CardSet;

class Player{
public:
	Player(CardSet*);
	virtual void playTurn() = 0;
	virtual ~Player(){};
	int getScore();
	int getHandSize();
	void addCard(Card*);
private:
	std::set<Card*> _hand;
	std::set<Card*> _discards;
	CardSet *_playedCards;
	int _score;
};

#endif
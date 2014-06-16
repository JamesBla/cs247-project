#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"

#include <map>
#include <set>

class Player{
public:
	Player(std::map<Card*, bool>*);
	virtual void playTurn() = 0;
	virtual ~Player(){};
	int getScore();
	int getHandSize();
	void addCard(Card*);
private:
	std::set<Card*> _hand;
	std::set<Card*> _discards;
	std::map<Card*, bool> *_playedCards;
	int _score;
};

#endif
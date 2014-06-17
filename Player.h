#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "View.h"

#include <map>
#include <set>

class Player{
public:
	Player(View*);
	virtual void playTurn(bool (&cardMap)[4][13]) = 0;
	virtual ~Player(){};
	int getScore();
	int getHandSize();
	void addCard(Card*);
private:
	std::vector<Card*> _hand;
	std::vector<Card*> _discards;
	int _score;
	View* _view;
};

#endif
#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"


#include <map>
#include <set>

class Model;
class View;
class Controller;

class Player{
public:
	Player(Model*, View*, Controller*, int);
	virtual void playTurn(bool (&cardMap)[4][13]) = 0;
	virtual ~Player(){};
	int getScore() const;
	int getHandSize() const;
	void addCard(Card*);
	void playCard(Card*& card);
	void discard(Card*& card);
	int getNumber() const;
protected:
	View* getView() const;
	std::vector<Card*> getHand() const;
	bool playable(Card*, bool (&cardMap)[4][13]) const;
	std::vector<Card*> getLegalPlays(bool (&cardMap)[4][13]) const;
	Controller* getController() const;
private:
	std::vector<Card*> _hand;
	std::vector<Card*> _discards;
	int _score;
	View* _view;
	int _playerNumber;
	Model* _model;
	Controller* _controller;
};

#endif
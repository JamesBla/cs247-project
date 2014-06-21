#ifndef _PLAYER_
#define _PLAYER_

#include <vector>

class Model;
class View;
class Controller;

class Card;

class Player{
public:
	Player(Model*, View*, Controller*, int);
	Player(const Player&);
	virtual void playTurn(bool (&cardMap)[4][13]) = 0;
	virtual ~Player(){};
	int getScore() const;
	int getHandSize() const;
	void addCard(Card*);
	void playCard(Card*& card);
	void discard(Card* card);
	int getNumber() const;
	void updateScore();
	void prepForNewRound();
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
	int _roundScore;
	View* _view;
	int _playerNumber;
	Model* _model;
	Controller* _controller;
};

#endif
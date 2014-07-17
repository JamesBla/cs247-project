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
	virtual ~Player();
	Player(const Player&);
	virtual bool playTurn(Card*, bool (&cardMap)[4][13]) = 0;
	virtual bool isHuman() const = 0;
	int getScore() const;
	int getHandSize() const;
	void addCard(Card*);
	void playCard(Card*);
	void discard(Card*);
	int getNumber() const;
	void updateScore();
	void prepForNewRound();
	std::vector<Card*> getHand() const;
	int getDiscardedCount() const;
protected:
	View* getView() const;
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
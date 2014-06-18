#ifndef _VIEW_
#define _VIEW_

#include "Model.h"
#include "Controller.h"
#include "Card.h"
#include "Player.h"

#include <string>
#include <vector>

class Model;
class Controller;
class Card;
class Player;

class View{
public:
	View(Controller*, Model*);
	void requestPlayerType(int) const;
	void announceNewRound(int) const;
	void printCardsOnTable(const bool (&cardMap)[4][13]) const;
	void printCardsInHand(const std::vector<Card*>&) const;
	void printLegalPlays(const std::vector<Card*>&) const;
	void printPrompt() const;
	void printLegalPlay(Player*&, Card*&) const;
	void printIllegalPlay() const;
	void printDiscard(Player*&, Card*&) const;
	void printMayNotDiscard() const;
};

#endif
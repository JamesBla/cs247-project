#ifndef _VIEW_
#define _VIEW_

#include "Model.h"
#include "Controller.h"
#include "Card.h"

#include <string>
#include <vector>

class Model;
class Controller;
class Card;

class View{
public:
	View(Controller*, Model*);
	void requestPlayerType(int) const;
	void announceNewRound(int) const;
	void printCardsOnTable(const bool (&cardMap)[4][13]) const;
	void printCardsInHand(const std::vector<Card*>&) const;
	void printLegalPlays(const std::vector<Card*>&) const;
	void printPrompt() const;
};

#endif
#ifndef _VIEW_
#define _VIEW_

#include "Model.h"
#include "Controller.h"

#include <string>

class Model;
class Controller;

class View{
public:
	View(Controller*, Model*);
	void requestPlayerType(int) const;
	void announceNewRound(int) const;
	void printCardsOnTable(std::string[]) const;
	void printCardsInHand(std::string) const;
	void printLegalPlays(std::string) const;
	void printPrompt() const;
};

#endif
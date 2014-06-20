#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <vector>

class Card;
class Controller;
class Model;
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
	void printDeck(std::vector<Card*> &) const;
};

#endif
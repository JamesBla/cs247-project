#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <vector>

class Model;
class Controller;

class Card;
class Player;
class HumanPlayer;

class View{
public:
	View(Controller*, Model*);
	void requestPlayerType(int) const;
	void announceNewRound(Player*) const;
	void printCardsOnTable(const bool (&cardMap)[4][13]) const;
	void printCardsInHand(const std::vector<Card*>&) const;
	void printLegalPlays(const std::vector<Card*>&) const;
	void printPrompt() const;
	void printLegalPlay(Player*, Card*) const;
	void printIllegalPlay() const;
	void printDiscard(Player*, Card*) const;
	void printMayNotDiscard() const;
	void printDeck(std::vector<Card*> &) const;
	void printNewScore(std::vector<Card*> &, int, int, int, Player*) const;
	void announceWinner(Player*) const;
	void printRagequit(HumanPlayer* player) const;
};

#endif
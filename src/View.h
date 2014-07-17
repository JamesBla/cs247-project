#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <vector>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>

#include "Card.h"
#include "DeckGUI.h"
#include "PlayerView.h"
#include "Observer.h"

class Model;
class Controller;

class Card;
class Player;
class HumanPlayer;
class CardButtonView;

class View : public Gtk::Window, public Observer {
public:
	View(Controller*, Model*);
	virtual ~View();
	void update();
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Rank r, Suit s) const;

	void announceNewRound(Player*);
	void printCardsOnTable(const bool (&cardMap)[4][13]) const;
	void printCardsInHand(const std::vector<Card*>&) const;
	void printDiscard(Player*, Card*) const;
	void printNewScore(std::vector<Card*> &, int, int, int, Player*) const;
	void announceWinners(std::vector<Player*>) const;

	bool requestPlayerType(int) const; // true if human, false if computer
	void printPrompt() const;
	void printLegalPlay(Player*, Card*) const;
	void printIllegalPlay() const;
	void printMayNotDiscard() const;
	void printDeck(std::vector<Card*> &) const;
	void printRagequit(HumanPlayer* player) const;

	void setHandView(std::vector<Card*> *);

	void printLegalPlays(const std::vector<Card*>&) const; // bonus
private:
	Model* _model;
	Controller* _controller;


	 //Signal handlers:
  	virtual void onNewGame();
  	virtual void onEndGame();
  	std::string intToString(int);

	DeckGUI                         deck;             // Knows all of the card pixel buffers.
	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf;
	
	// Member widgets:
	Gtk::Image                    * card[13];          // Images to display.
	Gtk::Button                     button;           // Button that will hold an image.
	Gtk::HBox                       hbox;             // Horizontal box for aligning widgets in the window.
	Gtk::Frame                      frame;            // Create a nice framed border for the box.

	Gtk::VBox topContainer;

	Gtk::HBox toolbar;
	Gtk::Button newGameButton;
	Gtk::Entry seedEntry;
	Gtk::Button endGameButton;

	Gtk::Frame cardsOnTableFrame;
	Gtk::Table cardsOnTable;
	Gtk::Image *cardsPlayed[4][13];

	Gtk::HBox playersContainer;
	PlayerView *playerViews[4];

	CardButtonView *cardButtonViews[13];
};

#endif
#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <vector>
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
	Glib::RefPtr<Gdk::Pixbuf> getPlayOverlay() const;
	Glib::RefPtr<Gdk::Pixbuf> getDiscardOverlay() const;
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Rank r, Suit s) const;

	bool getPlayerType(int) const; // true if human, false if computer
	void setHandView(std::vector<Card*> *, std::vector<Card*> *);
	void setPlayedCardsView(bool clear);
	std::string intToString(int);
	
private:
	Controller* _controller;
	Model* _model;

	 //Signal handlers:
  	virtual void onNewGame();
  	virtual void onEndGame();

  	void showDialogue(std::string, std::string);

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
#ifndef _VIEW_
#define _VIEW_

#include <string>
#include <vector>
#include <gtkmm.h>

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
	void update();													// updates view based on model state
	void onActionFileQuit();										// event handlers
	void onActionFileSave();
	void onActionFileOpen();
	void onActionHelpAbout();
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;				// pixbufs for card images and overlays
	Glib::RefPtr<Gdk::Pixbuf> getPlayOverlay() const;
	Glib::RefPtr<Gdk::Pixbuf> getDiscardOverlay() const;
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Rank r, Suit s) const;

	void setHandView(std::vector<Card*> *, std::vector<Card*> *);	// sets the view of the hand
	void setPlayedCardsView(bool clear);							// sets the view of cards that are played
	std::string intToString(int);									// method for converting int to string

private:
	Controller* _controller;
	Model* _model;

  	virtual void onNewGame();										// signal handlers
  	virtual void onEndGame();
  	virtual void onSeedInput();

  	void showDialogue(std::string, std::string);						// show dialog
  	int showFileChooser(Gtk::FileChooserDialog&, Gtk::BuiltinStockID);	// show file chooser

	DeckGUI deck;             										// Knows all of the card pixel buffers.
	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf;
	
	Gtk::Image * card[13];       								    // Images to display.
	Gtk::Button button;     								        // Button that will hold an image.
	Gtk::HBox hbox;       									        // Horizontal box for aligning widgets in the window.
	Gtk::Frame frame;       								        // Create a nice framed border for the box.

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
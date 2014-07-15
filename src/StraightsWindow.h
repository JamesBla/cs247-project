#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>

#include "DeckGUI.h"
#include "PlayerView.h"

class StraightsWindow : public Gtk::Window {
public:
	StraightsWindow();
	virtual ~StraightsWindow();
	
private:
	 //Signal handlers:
  	virtual void onNewGame();
  	virtual void onEndGame();

	DeckGUI                         deck;             // Knows all of the card pixel buffers.
	
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

};

#endif

#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

#include "Card.h"
#include "DeckGUI.h"

using std::vector;
using std::string;

class Controller;

class CardButtonView : public Gtk::Button {
public:
	CardButtonView(Controller*, bool, Rank r = ACE, Suit s = CLUB);
	virtual ~CardButtonView();
private:
	void cardButtonClicked();
	Controller* _controller;
	Gtk::Image* image;
	DeckGUI deck;
};

#endif
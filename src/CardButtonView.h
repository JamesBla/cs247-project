#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

#include "View.h"

using std::vector;
using std::string;

class Controller;
class View;
class Card;

class CardButtonView : public Gtk::Button {
public:
	CardButtonView(Controller*, View*);
	void setCard(Card*);
	virtual ~CardButtonView();
private:
	void cardButtonClicked();
	Controller* _controller;
	View* _view;
	Gtk::Image* image;
	Card* currentCard;
};

#endif
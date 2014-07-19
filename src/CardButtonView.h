#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <vector>
#include <string>

#include "View.h"

using std::vector;
using std::string;

class View;
class Card;

class CardButtonView : public Gtk::Button {
public:

	CardButtonView(Model*, View*, int);

	void setCard(Card*, bool);
	virtual ~CardButtonView();

private:
	void mouseEnter();
	void mouseLeave();
	void cardButtonClicked();
	Model* _model;
	View* _view;
	Gtk::Image* _image;
	Card* _currentCard;


	int _screenWidth;

};

#endif
#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <gtkmm/button.h>
#include <gtkmm/image.h>

class Model;
class View;
class Controller;
class Card;

class CardButtonView : public Gtk::Button {
public:

	CardButtonView(Model*, View*, Controller*, int);

	void setCard(Card*, bool);		// sets the card represented by this view
	virtual ~CardButtonView();

private:
	void mouseEnter();				// handlers for mouseover effect
	void mouseLeave();
	void cardButtonClicked();   	// click handler
	Model* _model;
	View* _view;
	Controller* _controller;
	Gtk::Image* _image;
	Card* _currentCard;

	int _screenWidth;

};

#endif
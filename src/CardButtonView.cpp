#include "CardButtonView.h"
#include "Controller.h"
#include "Card.h"
#include "Model.h"

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <algorithm>
#include <iterator>
#include <string>

#include <iostream>

using namespace std;

void CardButtonView::cardButtonClicked() {
	_controller->getModel()->playATurn(currentCard);
}

CardButtonView::CardButtonView(Controller* controller, View* view) {
	_controller = controller;
	_view = view;

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = _view->getNullCardImage();

	signal_clicked().connect( sigc::mem_fun( *this, &CardButtonView::cardButtonClicked ) );

	image = new Gtk::Image(nullCardPixbuf);
	set_image(*image);
}

CardButtonView::~CardButtonView() {
	delete image;
}

void CardButtonView::setCard(Card* card) {
	currentCard = card;

	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = (card == NULL) ? _view->getNullCardImage() : _view->getCardImage(card->getRank(), card->getSuit());
	
	delete image;
	image = new Gtk::Image(cardPixbuf);
	set_image(*image);
}

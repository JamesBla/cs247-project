#include "CardButtonView.h"
#include "Controller.h"
#include "Card.h"
#include "DeckGUI.h"
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

CardButtonView::CardButtonView(Controller* controller, bool nothing, Rank r, Suit s) {
	_controller = controller;

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage(r, s);

	signal_clicked().connect( sigc::mem_fun( *this, &CardButtonView::cardButtonClicked ) );

	image = new Gtk::Image(nothing ? nullCardPixbuf : cardPixbuf);
	set_image(*image);
}

CardButtonView::~CardButtonView() {
	delete image;
}

void CardButtonView::setCard(Card* card){

	currentCard = card;

	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = (card == NULL) ? deck.getNullCardImage() : deck.getCardImage(card->getRank(), card->getSuit());
	

	
	delete image;
	image = new Gtk::Image(cardPixbuf);
	set_image(*image);



	// cout << "hello" << endl;
}

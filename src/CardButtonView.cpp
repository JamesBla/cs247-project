#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "CardButtonView.h"
#include "Card.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

CardButtonView::CardButtonView(Model* model, View* view, Controller* controller, int width) : _model(model), _view(view),
_controller(controller), _screenWidth(width) {
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = _view->getNullCardImage();

	signal_clicked().connect( sigc::mem_fun( *this, &CardButtonView::cardButtonClicked ) );
	signal_enter().connect( sigc::mem_fun( *this, &CardButtonView::mouseEnter ) );
	signal_leave().connect( sigc::mem_fun( *this, &CardButtonView::mouseLeave ) );

	_image = new Gtk::Image(nullCardPixbuf);
	set_image(*_image);
}

void CardButtonView::cardButtonClicked() {
	_controller->playATurn(_currentCard);
}

void CardButtonView::mouseEnter(){
	if (get_sensitive()){
		// violates Demeter?
		bool isPlay = _model->getLegalPlays(_model->getCurrentPlayer()).size() > 0;
			
		Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = 
				_view->getCardImage(_currentCard->getRank(), _currentCard->getSuit())->copy();

		Glib::RefPtr<Gdk::Pixbuf> overlay;

		if (isPlay){
			overlay = _view->getPlayOverlay(); 
		}
		else{
			overlay = _view->getDiscardOverlay();
		}

		int cardWidth = _screenWidth / 30;
		int cardHeight = (int)(cardWidth/0.69);

		overlay->composite(cardPixbuf, 0, 0, cardWidth, cardHeight,
				 0, 0, 1, 1, Gdk::INTERP_BILINEAR, 255);

		delete _image;
		_image = new Gtk::Image(cardPixbuf);
		set_image(*_image);
	}
}

void CardButtonView::mouseLeave(){
	if (get_sensitive()){
		const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = 
			_view->getCardImage(_currentCard->getRank(), _currentCard->getSuit());
		delete _image;
		_image = new Gtk::Image(cardPixbuf);
		set_image(*_image);
	}
}


CardButtonView::~CardButtonView() {
	delete _image;
}

void CardButtonView::setCard(Card* card, bool enable) {
	_currentCard = card;

	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = (card == NULL) ? _view->getNullCardImage() : _view->getCardImage(card->getRank(), card->getSuit());
	set_sensitive(enable);
	delete _image;
	_image = new Gtk::Image(cardPixbuf);
	set_image(*_image);
}

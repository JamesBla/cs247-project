#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "Card.h"
#include "CardButtonView.h"

using namespace std;

// TODO: implement observer pattern (list of observers)
void View::update() {
	
	if (_model->resetView()){
		frame.set_label( "Cards in your hand:" );
		set_title("Straights UI");
		setHandView(NULL, NULL);

		setPlayedCardsView(true);
		
		for (int i = 0; i < 4; i++){
			playerViews[i]->resetLabels();
		}

		// hack-ish
		if (_model->getDeck().size() > 0){
			for (int i = 0; i < 4; i++) {
				playerViews[i]->setButton(true, (_model->getPlayer(i)->isHuman()) ? PlayerView::humanLabel() : PlayerView::computerLabel());
			}
		}
		
		return;
	}
		
	if (_model->isStartOfNewRound()) {
		
		for (int i = 0; i < 4; i++){
			playerViews[i]->setButton(false, PlayerView::rageLabel());
		}

		string playerNumString = intToString(_model->getFirstPlayer()->getNumber());
		string message = "A new round begins. It's player " + playerNumString + "'s turn to play.";

		showDialogue("", message);
	}

	if (_model->isRoundFinished()) {

		for (int i = 0; i < 4; i++) {
			playerViews[i]->update();
		}

		setPlayedCardsView(false);

		string message = "";

		// build end-of-round message
		for (int i = 0; i < 4; i++) {
			Player* player = _model->getPlayer(i);
			vector<Card*> discards = _model->getDiscardedCards(i);
			string playerNumber = intToString(i+1);
			message += "Player " + playerNumber + "'s discards: ";
			for (unsigned int i = 0; i < discards.size(); i++) {
				message += discards.at(i)->toString();
				if (i != discards.size() - 1){
					message += " ";
				}
			}
			message += "\n";
			message += "Player " + playerNumber + "'s score: " + intToString(player->getOldScore()) + 
			" + " + intToString(player->getRoundScore()) + " = " + intToString(player->getScore()) + "\n";
			message += "\n";
		}

		showDialogue("End of Round", message);
	}

	if (_model->doneGame()){
		vector<Player*> winners = _model->getWinners();
		string message = "";
		for (int i = 0; i < winners.size(); i++){
			message += ("Player " + intToString(winners[i]->getNumber()) + " wins!\n");
		}
		showDialogue("End of Game", message);
  		return;
	}	

	if (_model->isRoundInProgress()) {
		int playerNum = _model->getCurrentPlayer()->getNumber();

		if (_model->getCurrentPlayer()->isHuman()){
			vector<Card*> curHand = _model->getCurrentPlayer()->getHand();

			vector<Card*> legalPlays = _model->getLegalPlays(_model->getCurrentPlayer());

			setHandView(&curHand, &legalPlays);

			for (int i = 0; i < 4; i++){
				playerViews[i]->setButton(i == playerNum-1, PlayerView::rageLabel());
			}

			string numberString = static_cast<ostringstream*>( &(ostringstream() << playerNum) )->str();
			set_title("Straights UI - Player " + numberString + "'s Turn");
		}
		else{
			set_title("Straights UI");
		}
		
		setPlayedCardsView(false);	
	}	
}

void View::showDialogue(string title, string message){
	Gtk::MessageDialog dialogue(*this, title);
  	dialogue.set_secondary_text(message);
  	dialogue.run();
}

void View::setHandView(vector<Card*> * hand, vector<Card*> * legalPlays){
	for (unsigned int i = 0; i < 13; i++){
		bool cardExists = hand && i < (*hand).size();
		bool enableButton = false;

		if (legalPlays && cardExists){
			if ((*legalPlays).size() == 0){
				enableButton = true;
				frame.set_label( "Cards in your hand: (must discard)" );
			}
			else{
				frame.set_label( "Cards in your hand:" );
			}
			for (int j = 0; j < (*legalPlays).size(); j++){
				if (*((*legalPlays)[j]) == *((*hand)[i])){
					enableButton = true;
				}
			}
		}

		cardButtonViews[i]->setCard(cardExists ? (*hand)[i] : NULL, enableButton);
	}
}

void View::setPlayedCardsView(bool clear){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = deck.getCardImage(static_cast<Rank>(j), static_cast<Suit>(i));
			cardsPlayed[i][j]->set( (!clear && _model->beenPlayed(i,j)) ? cardPixbuf : nullCardPixbuf);
		}
	}
}

bool View::getPlayerType(int playerNumber) const{
	return playerViews[playerNumber]->isHuman();
}


void View::onNewGame(){
	srand48( atoi(static_cast<string>(seedEntry.get_text()).c_str()) );

	_controller->run();

	
}

void View::onEndGame(){
	_model->cleanUp();
}


View::View(Controller* controller, Model* model) : deck(this->get_screen()->get_width()), hbox( true, 10 ), newGameButton("Start new game with seed:"), endGameButton("End current game"), 
 cardsOnTable(4, 13, true) {
	

	controller->setView(this);
	model->subscribe(this);
	_model = model;
	_controller = controller;

	nullCardPixbuf = deck.getNullCardImage();

	set_title("Straights UI");
	// Sets the border width of the window.
	set_border_width( 10 );

	topContainer.pack_start(toolbar);
	topContainer.pack_start(cardsOnTableFrame);
	topContainer.pack_start(playersContainer);
	topContainer.pack_end(frame);

	toolbar.pack_start(newGameButton);
	toolbar.pack_start(seedEntry);
	toolbar.pack_end(endGameButton);

	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::onNewGame ) );
	seedEntry.set_text("0");
	seedEntry.set_alignment(0.5);
	endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::onEndGame ) );

	cardsOnTableFrame.set_label("Cards on the table");
	cardsOnTable.set_row_spacings(5);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cardsPlayed[i][j] = new Gtk::Image(nullCardPixbuf);
			cardsOnTable.attach(*cardsPlayed[i][j], j, j+1, i, i+1);
		}
	}

	cardsOnTableFrame.add(cardsOnTable);

	for (int i = 0; i < 4; i++) {
		playerViews[i] = new PlayerView(i+1, _model, this);
		playersContainer.pack_start(*playerViews[i]);
	}

	// Set the look of the frame.
	frame.set_label( "Cards in your hand:" );
	
	// Add the vbox to the window. Windows can only hold one widget, same for frames.
	add( topContainer );
	
	// Add the horizontal box for laying out the images to the frame.	
	frame.add( hbox );
	
	
	for (int i = 0; i < 13; i++ ) {
		cardButtonViews[i] = new CardButtonView(_controller, this, this->get_screen()->get_width());
		hbox.add( *cardButtonViews[i] );
	} // for
	setHandView(NULL, NULL);
	show_all();
}

View::~View() {
	for (int i = 0; i < 13; i++ ) {
		if (!card[i])
			delete card[i];
		delete cardButtonViews[i];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) delete cardsPlayed[i][j];
	}
	
	for (int i = 0; i < 4; i++) {
		delete playerViews[i];
	}
}

Glib::RefPtr<Gdk::Pixbuf> View::getPlayOverlay() const {
	return deck.getPlayOverlay();
}

Glib::RefPtr<Gdk::Pixbuf> View::getDiscardOverlay() const {
	return deck.getDiscardOverlay();
}

Glib::RefPtr<Gdk::Pixbuf> View::getNullCardImage() const {
	return deck.getNullCardImage();
}

Glib::RefPtr<Gdk::Pixbuf> View::getCardImage(Rank r, Suit s) const {
	return deck.getCardImage(r, s);
}

string View::intToString(int n) {
	ostringstream ostr;
	ostr << n;
	return ostr.str();
}
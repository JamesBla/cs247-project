#include <iostream>
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

void View::notify() {
	//foreach (state in Model.States){
		//if (state.changed)
			//view.updateWindow(state)
	//}

	if (_model->isStartOfNewRound()) {
		// cout << "A new round begins. It's player " << _model->getFirstPlayer()->getNumber() << "'s turn to play." << endl;
		int Number = _model->getFirstPlayer()->getNumber();       // number to be converted to a string

		string numberString = static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
		string message = "A new round begins. It's player " + numberString + "'s turn to play.";

		Gtk::MessageDialog dialog(*this, "");
  		dialog.set_secondary_text(message);

  		dialog.run();
	}

	cout << "ron" << endl;
	
	if (_model->getCurrentPlayer()->isHuman()){
		
		int playerNum = _model->getCurrentPlayer()->getNumber();
		string numberString = static_cast<ostringstream*>( &(ostringstream() << playerNum) )->str();
		set_title("Straights UI - Player " + numberString + "'s Turn");
		vector<Card*> curHand = _model->getCurrentPlayer()->getHand();

		for (int i = 0; i < curHand.size(); i++ ) {
			cardButtonViews[i]->setCard(curHand[i]);
		} // for
		
		for (int i = curHand.size(); i < 13; i++){
			cardButtonViews[i]->setCard(NULL);
		}
		
	}


	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			
			const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = deck.getCardImage(static_cast<Rank>(j), static_cast<Suit>(i));
			if (_model->beenPlayed(i,j)){
				cout << "played" << endl;
			}
			cardsPlayed[i][j]->set( _model->beenPlayed(i,j) ? cardPixbuf : nullCardPixbuf);
		}
	}
	

	// for (int i = 0; i < 4; i++) {
	// 	for (int j = 0; j < 13; j++) {
			
	// 		delete cardsPlayed[i][j];

	// 		const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	// 		const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = deck.getCardImage(static_cast<Rank>(j), static_cast<Suit>(i));

	// 		cout << "hello" << endl;
	// 		cardsPlayed[i][j] = new Gtk::Image( _model->beenPlayed(i,j) ? cardPixbuf : nullCardPixbuf);
	// 		cout << "bye" << endl;
	// 		cardsOnTable.attach(*cardsPlayed[i][j], j, j+1, i, i+1);
	// 	}
	// }





}

void View::printNewScore(std::vector<Card*>& discards, int oldScore, int gainedScore, int newScore, Player* player) const{
	cout << "Player " << player->getNumber() << "'s discards: ";
	for (unsigned int i = 0; i < discards.size(); i++){
		cout << *(discards[i]);
		if (i != discards.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
	cout << "Player " << player->getNumber() << "'s score: " << oldScore << " + " << gainedScore << " = " << newScore << endl;
}

bool View::requestPlayerType(int playerNumber) const{
	return playerViews[playerNumber]->isHuman();
}

void View::announceNewRound(Player* firstPlayer){
	

	// cout << "A new round begins. It's player " << firstPlayer->getNumber() << "'s turn to play." << endl;
}

void View::printCardsOnTable(const bool (&cardMap)[4][13]) const{
	string onTable[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			if (cardMap[i][j]) {
				string rankPrintForm;
				switch(j) {
					case 0:
						rankPrintForm = "A";
						break;
					case 9:
						rankPrintForm = "10";
						break;
					case 10:
						rankPrintForm = 'J';
						break;
					case 11:
						rankPrintForm = 'Q';
						break;
					case 12:
						rankPrintForm = 'K';
						break;
					default:
						rankPrintForm = static_cast<char>(j+49);
				}
				onTable[i] = onTable[i] + rankPrintForm + " ";
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (onTable[i] != "") {
			onTable[i] = onTable[i].substr(0, onTable[i].length()-1);
		}
	}

	cout << "Cards on the table:\n";
	cout << "Clubs: " << onTable[0] << endl;
	cout << "Diamonds: " << onTable[1] << endl;
	cout << "Hearts: " << onTable[2] << endl;
	cout << "Spades: " << onTable[3] << endl;
}

void View::printCardsInHand(const std::vector<Card*> &cards) const{
	cout << "Your hand:";
	for (vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); it++) {
		cout << " " << **it;
	}
	cout << endl;
}

void View::printLegalPlays(const std::vector<Card*> &cards) const{
	cout << "Legal plays:";
	for (vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); it++) {
		cout << " " << **it;
	}
	cout << endl;
}

void View::printPrompt() const{
	cout << ">";
}

void View::printLegalPlay(Player* player, Card* card) const{
	cout << "Player " << player->getNumber() << " plays " << *card << "." << endl;
};

void View::printIllegalPlay() const{
	cout << "This is not a legal play.\n";
}

void View::printDiscard(Player* player, Card* card) const{
	cout << "Player " << player->getNumber() << " discards " << *card << "." << endl;
}

void View::printMayNotDiscard() const{
	cout << "You have a legal play. You may not discard." << endl;
}

void View::announceWinners(std::vector<Player*> winners) const{
	for (unsigned int i = 0; i < winners.size(); i++){
		cout << "Player " << winners[i]->getNumber() << " wins!" << endl;
	}
}

void View::printDeck(vector<Card*> &deck) const{
	for (unsigned int i = 0; i < deck.size(); i++){
		cout << *deck[i];
		if ((i + 1) % 13 == 0){
			cout << endl;
		}
		else{
			cout << " ";
		}
	}
	cout << endl;
}

void View::printRagequit(HumanPlayer* player) const {
	cout << "Player " << player->getNumber() << " ragequits. A computer will now take over.\n";
}

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.

void View::onNewGame(){
	srand48( atoi(static_cast<string>(seedEntry.get_text()).c_str()) );
	_controller->run();
}

void View::onEndGame(){

}


View::View(Controller* controller, Model* model) : hbox( true, 10 ), newGameButton("Start new game with seed:"), endGameButton("End current game"), 
cardsOnTable(4, 13, true) {

	controller->setView(this);
	model->setView(this);
	_model = model;
	_controller = controller;

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

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );

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
		playerViews[i] = new PlayerView(i+1);
		playersContainer.pack_start(*playerViews[i]);
	}

	// Set the look of the frame.
	frame.set_label( "Cards:" );
	
	// Add the vbox to the window. Windows can only hold one widget, same for frames.
	add( topContainer );
	
	// Add the horizontal box for laying out the images to the frame.	
	frame.add( hbox );
	
	// Initialize 4 empty cards and place them in the box.
	for (int i = 0; i < 13; i++ ) {
		cardButtonViews[i] = new CardButtonView(_controller, true);
		hbox.add( *cardButtonViews[i] );
	} // for

	// // Initialize the 5th card and place the image into the button.
	// card[4] = new Gtk::Image( cardPixbuf );	
	// button.set_image( *card[4] );	
			
	// // Add the button to the box.
	// hbox.add( button );
	
	// The final step is to display this newly created widget.
	show_all();
}

View::~View() {
	for (int i = 0; i < 13; i++ ) {
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
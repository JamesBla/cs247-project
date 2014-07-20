#include <sstream>
#include <string>
#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm.h>
#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Player.h"
#include "Card.h"
#include "CardButtonView.h"

using namespace std;

View::View(Controller* controller, Model* model) : _controller(controller), _model(model), 
deck((get_screen()->get_width() > 1600) ? 1600 : get_screen()->get_width()), hbox( true, 10 ), 
newGameButton("Start new game with seed:"), endGameButton("End current game"), 
 cardsOnTable(4, 13, true) {
 	int screenWidth = (get_screen()->get_width() > 1600) ? 1600 : get_screen()->get_width();

	_model->subscribe(this);

	nullCardPixbuf = deck.getNullCardImage();

	set_title("Straights UI");
	// Sets the border width of the window.
	set_border_width( 10 );

	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup = Gtk::ActionGroup::create();
	m_refActionGroup->add( Gtk::Action::create("MenuFile", "_File") );
	m_refActionGroup->add( Gtk::Action::create("Open", Gtk::Stock::OPEN),
	  sigc::mem_fun(*this, &View::onActionFileOpen) );
	m_refActionGroup->add( Gtk::Action::create("Save", Gtk::Stock::SAVE),
	  sigc::mem_fun(*this, &View::onActionFileSave) );
	m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),
	  sigc::mem_fun(*this, &View::onActionFileQuit) );
	m_refActionGroup->add( Gtk::Action::create("MenuHelp", "_Help") );
	m_refActionGroup->add( Gtk::Action::create("About", Gtk::Stock::ABOUT),
	  sigc::mem_fun(*this, &View::onActionHelpAbout) );

  	//Define how the actions are presented in the menus and toolbars:
 	Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();
 	m_refUIManager->insert_action_group(m_refActionGroup);
  	add_accel_group(m_refUIManager->get_accel_group());
	Glib::ustring ui_info =
	    "<ui>"
	    "  <menubar name='MenuBar'>"
	    "    <menu action='MenuFile'>"
	    "      <menuitem action='Open'/>"
	    "      <menuitem action='Save'/>"
	    "      <separator/>"
	    "      <menuitem action='Quit'/>"
	    "    </menu>"
	    "    <menu action='MenuHelp'>"
	    "      <menuitem action='About'/>"
	    "    </menu>"
	    "  </menubar>"
	    "</ui>";

	m_refUIManager->add_ui_from_string(ui_info);
	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	//pBox->add(*pMenuBar, Gtk::PACK_SHRINK);

	topContainer.pack_start(*pMenubar);
	topContainer.pack_start(toolbar);
	topContainer.pack_start(cardsOnTableFrame);
	topContainer.pack_start(playersContainer);
	topContainer.pack_end(frame);

	toolbar.pack_start(newGameButton);
	toolbar.pack_start(seedEntry);
	toolbar.pack_end(endGameButton);

	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::onNewGame ) );
	seedEntry.set_text(intToString(_model->getSeed()));
	
	seedEntry.set_alignment(0.5);
	seedEntry.signal_changed().connect( sigc::mem_fun( *this, &View::onSeedInput ) );
	
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
		playerViews[i] = new PlayerView(i+1, _model, this, _controller);
		playersContainer.pack_start(*playerViews[i]);
	}

	// Set the look of the frame.
	frame.set_label( "Cards in your hand:" );

	// Add the vbox to the window. Windows can only hold one widget, same for frames.
	add( topContainer );

	// Add the horizontal box for laying out the images to the frame.	
	frame.add( hbox );

	for (int i = 0; i < 13; i++ ) {
		cardButtonViews[i] = new CardButtonView(_model, this, _controller, screenWidth);

		hbox.add( *cardButtonViews[i] );
	}

	setHandView(NULL, NULL);
	show_all();
}

void View::update() {
	if (_model->getState() == Model::BAD_SAVEFILE){
		showDialogue("Error", "Invalid savefile");
		onActionFileOpen();
	}
	else if (_model->getState() == Model::RESET_VIEW){
		seedEntry.set_text(intToString(_model->getSeed()));
		frame.set_label( "Cards in your hand:" );
		set_title("Straights UI");
		setHandView(NULL, NULL);

		setPlayedCardsView(true);

		for (int i = 0; i < 4; i++){
			playerViews[i]->resetLabels();
		}

		if (_model->getDeck().size() > 0){
			for (int i = 0; i < 4; i++) {
				playerViews[i]->setButton(true, (_model->getPlayer(i)->isHuman()) ? PlayerView::humanLabel() : PlayerView::computerLabel());
			}
		}
	}
	else if (_model->getState() == Model::ROUND_STARTED) {

		for (int i = 0; i < 4; i++){
			playerViews[i]->setButton(false, PlayerView::rageLabel());
			playerViews[i]->update();
		}

		string playerNumString = intToString(_model->getFirstPlayer()->getNumber());
		string message = "A new round begins. It's player " + playerNumString + "'s turn to play.";

		showDialogue("", message);
	}
	else if (_model->getState() == Model::ROUND_ENDED) {

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
	else if (_model->getState() == Model::GAME_ENDED){
		vector<Player*> winners = _model->getWinners();
		string message = "";
		for (unsigned int i = 0; i < winners.size(); i++){
			message += ("Player " + intToString(winners[i]->getNumber()) + " wins!\n");
		}
		showDialogue("End of Game", message);
  		return;
	}	
	else if (_model->getState() == Model::IN_PROGRESS) {
		int playerNum = _model->getCurrentPlayer()->getNumber();

		for (int i = 0; i < 4; i++){
			playerViews[i]->update();
		}

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
		bool cardExists = hand && i < hand->size();
		bool enableButton = false;

		if (legalPlays && cardExists){
			if (legalPlays->empty()){
				enableButton = true;
				frame.set_label( "Cards in your hand: (must discard)" );
			}
			else{
				frame.set_label( "Cards in your hand:" );
			}
			for (unsigned int j = 0; j < legalPlays->size(); j++){
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

void View::onSeedInput(){
	_controller->setSeed(atoi(static_cast<string>(seedEntry.get_text()).c_str()));
}

void View::onNewGame(){
	_controller->run();
}

void View::onEndGame(){
	_controller->endGame();
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

int View::showFileChooser(Gtk::FileChooserDialog& dialog, Gtk::BuiltinStockID stockId) {
	dialog.set_transient_for(*this);
	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(stockId, Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:

	Gtk::FileFilter filter_text;
	filter_text.set_name("Straights Game File");
	filter_text.add_mime_type("text/plain");
	dialog.add_filter(filter_text);

	Gtk::FileFilter filter_any;
	filter_any.set_name("Any files");
	filter_any.add_pattern("*");
	dialog.add_filter(filter_any);

	//Show the dialog and wait for a user response:
	return dialog.run();
}

void View::onActionFileQuit() {
	hide();
}

void View::onActionFileOpen() {
	Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);

	int result = showFileChooser(dialog, Gtk::Stock::OPEN);
	//Handle the response:
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
		  string filename = dialog.get_filename();
		  _controller->loadSavedFile(filename);
		  break;
		}
		default:
		{
		  break;
		}
	}
}

void View::onActionFileSave() {
	if (_model->getState() != Model::NONE && _model->getState() != Model::GAME_ENDED && _model->getState() != Model::RESET_VIEW) {
		Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_SAVE);
		int result = showFileChooser(dialog, Gtk::Stock::SAVE);
		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
			  string filename = dialog.get_filename();
			  _controller->saveGame(filename);
			  break;
			}
			default:
			{
			  break;
			}
		}
	}
}

void View::onActionHelpAbout() {
	string mainMsg = "About";
	string secondaryMsg = "Ron Meng and Michael Tu\nCopyright \u00A9 2014\n";
	showDialogue(mainMsg, secondaryMsg);
}
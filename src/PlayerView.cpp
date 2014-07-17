#include "PlayerView.h"
#include "Model.h"
#include "HumanPlayer.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <sstream>
#include <string>

#include <iostream>

using namespace std;

void PlayerView::setButton(bool sensitive, std::string text){
	cout << "set to " << sensitive <<", " << text << endl;
	togglePlayer.set_sensitive(sensitive);
	togglePlayer.set_label(text);
}

PlayerView::PlayerView(int playerNumber, Model* model) : playerIndex(playerNumber-1), _model(model), togglePlayer("Human"), points("0 points"), discards("0 discards") {
	// required because ustring cannot append int directly
	Glib::ustring playerNumberStr = intToString(playerNumber);

	set_label("Player " + playerNumberStr);
	container.pack_start(togglePlayer);
	container.pack_start(points);
	container.pack_end(discards);
	add(container);

	togglePlayer.signal_clicked().connect( sigc::mem_fun( *this, &PlayerView::onClick ) );
}

PlayerView::~PlayerView() {

}

void PlayerView::onClick(){
	if (togglePlayer.get_label() == "Rage!"){
		_model->computerizePlayer(_model->getCurrentPlayer());
	}
	else {
		togglePlayer.set_label( (togglePlayer.get_label() == "Human") ? "Computer" : "Human" );
	}
}

bool PlayerView::isHuman() const{
	return (togglePlayer.get_label() == "Human");
}

void PlayerView::update() {
	int newScore = _model->getPlayerScore(playerIndex);
	int newDiscardsCount = _model->getPlayerDiscardedCount(playerIndex);
	points.set_label(intToString(newScore) + " points");
	discards.set_label(intToString(newDiscardsCount) + " discards");
}

Glib::ustring PlayerView::intToString(int n) {
	ostringstream ostr;
	ostr << n;
	return ostr.str();
}
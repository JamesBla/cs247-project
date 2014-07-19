#include "PlayerView.h"
#include "Model.h"
#include "View.h"

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <string>

using namespace std;

const string PlayerView::HUMAN_LABEL = "Human";
const string PlayerView::COMPUTER_LABEL = "Computer";
const string PlayerView::RAGE_LABEL = "Rage!";

string PlayerView::humanLabel(){
	return HUMAN_LABEL;
}
string PlayerView::computerLabel(){
	return COMPUTER_LABEL;
}
string PlayerView::rageLabel(){
	return RAGE_LABEL;
}

void PlayerView::setButton(bool sensitive, std::string text){
	togglePlayer.set_sensitive(sensitive);
	togglePlayer.set_label(text);
}

void PlayerView::resetLabels(){
	points.set_label("0 points");
	discards.set_label("0 discards");
}

PlayerView::PlayerView(int playerNumber, Model* model, View* view) : playerIndex(playerNumber-1), _model(model), _view(view), togglePlayer("Human"), points("0 points"), discards("0 discards") {
	// required because ustring cannot append int directly
	Glib::ustring playerNumberStr = _view->intToString(playerNumber);

	set_label("Player " + playerNumberStr);
	container.pack_start(togglePlayer);
	container.pack_start(points);
	container.pack_end(discards);
	add(container);

	setButton(true, HUMAN_LABEL);

	togglePlayer.signal_clicked().connect( sigc::mem_fun( *this, &PlayerView::onClick ) );
}

PlayerView::~PlayerView() {

}

void PlayerView::onClick(){
	if (togglePlayer.get_label() == RAGE_LABEL){
		//tricky business
		
		setButton(false, RAGE_LABEL);
		_view->setHandView(NULL, NULL);

		_model->computerizePlayer(_model->getCurrentPlayer());
		
	}
	else {
		togglePlayer.set_label( (togglePlayer.get_label() == HUMAN_LABEL) ? COMPUTER_LABEL : HUMAN_LABEL );
	}
}

bool PlayerView::isHuman() const{
	return (togglePlayer.get_label() == HUMAN_LABEL);
}

void PlayerView::update() {
	int newScore = _model->getPlayerScore(playerIndex);
	int newDiscardsCount = _model->getPlayerDiscardedCount(playerIndex);
	points.set_label(_view->intToString(newScore) + " points");
	discards.set_label(_view->intToString(newDiscardsCount) + " discards");
}
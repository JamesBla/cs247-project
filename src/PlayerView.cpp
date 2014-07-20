#include "PlayerView.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

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

// set button with label and sensitivity
void PlayerView::setButton(bool sensitive, string text){
	togglePlayer.set_sensitive(sensitive);
	togglePlayer.set_label(text);
}

void PlayerView::resetLabels(){
	points.set_label("0 points");
	discards.set_label("0 discards");
}

PlayerView::PlayerView(int playerNumber, Model* model, View* view, Controller* controller) : playerIndex(playerNumber-1),
 _model(model), _view(view), _controller(controller), togglePlayer("Human"), points("0 points"), discards("0 discards") {
	// required because ustring cannot append int directly
	Glib::ustring playerNumberStr = _view->intToString(playerNumber);

	set_label("Player " + playerNumberStr);
	container.pack_start(togglePlayer);
	container.pack_start(points);
	container.pack_end(discards);
	add(container);

	// sets button label based on player type in model
	(_model->getPlayerType(playerNumber-1) == 'h') ? setButton(true, HUMAN_LABEL) : setButton(true, COMPUTER_LABEL);

	// connect click event to event handler
	togglePlayer.signal_clicked().connect( sigc::mem_fun( *this, &PlayerView::onClick ) );
}

PlayerView::~PlayerView() {

}

// click handler
void PlayerView::onClick(){
	if (togglePlayer.get_label() == RAGE_LABEL){
		// if ragequit is clicked, computerize player
		setButton(false, RAGE_LABEL);
		_view->setHandView(NULL, NULL);
		_controller->computerizePlayer(playerIndex);
	}
	else {
		// otherwise toggles label
		togglePlayer.set_label( (togglePlayer.get_label() == HUMAN_LABEL) ? COMPUTER_LABEL : HUMAN_LABEL );
		_controller->togglePlayer(playerIndex);
	}
}

// refreshes the view
void PlayerView::refresh() {
	int score = _model->getPlayerScore(playerIndex);
	if (_model->getState() == Model::IN_PROGRESS) {
		score += _model->getPlayerCurrentRoundScore(playerIndex);
	}
	int newDiscardsCount = _model->getPlayerDiscardedCount(playerIndex);
	points.set_label(_view->intToString(score) + " points");
	discards.set_label(_view->intToString(newDiscardsCount) + " discards");
}

#include "PlayerView.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <sstream>

PlayerView::PlayerView(int playerNumber) : togglePlayer("Human"), points("0 points"), discards("0 discards") {
	// required because ustring cannot append int directly
	std::ostringstream ostr;
	ostr << playerNumber;
	Glib::ustring playerNumberStr = ostr.str();

	set_label("Player " + playerNumberStr);
	container.pack_start(togglePlayer);
	container.pack_start(points);
	container.pack_end(discards);
	add(container);
}

PlayerView::~PlayerView() {

}
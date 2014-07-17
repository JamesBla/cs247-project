#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

class Model;

class PlayerView : public Gtk::Frame {
public:
	PlayerView(int, Model*);
	virtual ~PlayerView();
	bool isHuman() const;
	void update();
private:
	int playerIndex;
	Model* _model;
	Gtk::VBox container;
	Gtk::Button togglePlayer;
	Gtk::Label points;
	Gtk::Label discards;

	void onTypeChange();
	Glib::ustring intToString(int);
};

#endif
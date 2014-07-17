#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include <string>

class Model;

class PlayerView : public Gtk::Frame {
public:
	PlayerView(int, Model*);
	virtual ~PlayerView();
	void setButton(bool sensitive, std::string text);
	bool isHuman() const;
	void update();
private:
	int playerIndex;
	Model* _model;
	Gtk::VBox container;
	Gtk::Button togglePlayer;
	Gtk::Label points;
	Gtk::Label discards;

	void onClick();
	Glib::ustring intToString(int);
};

#endif
#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

class PlayerView : public Gtk::Frame {
public:
	PlayerView(int);
	virtual ~PlayerView();
private:
	Gtk::VBox container;
	Gtk::Button togglePlayer;
	Gtk::Label points;
	Gtk::Label discards;
};

#endif
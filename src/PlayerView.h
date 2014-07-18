#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include <string>

class Model;
class View;

class PlayerView : public Gtk::Frame {
public:
	PlayerView(int, Model*, View*);
	virtual ~PlayerView();
	void setButton(bool sensitive, std::string text);
	void resetLabels();
	bool isHuman() const;
	void update();
	static std::string humanLabel();
	static std::string computerLabel();
	static std::string rageLabel();
private:
	int playerIndex;
	Model* _model;
	View* _view;
	Gtk::VBox container;
	Gtk::Button togglePlayer;
	Gtk::Label points;
	Gtk::Label discards;
	static const std::string HUMAN_LABEL;
	static const std::string COMPUTER_LABEL;
	static const std::string RAGE_LABEL;

	void onClick();
	Glib::ustring intToString(int);
};

#endif
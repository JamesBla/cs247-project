#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include <string>

class Model;
class View;
class Controller;

class PlayerView : public Gtk::Frame {
public:
	PlayerView(int, Model*, View*, Controller*);
	virtual ~PlayerView();
	void setButton(bool sensitive, std::string text);	// sets button in this view
	void resetLabels();									// reset labels
	void refresh();										// update this view
	static std::string humanLabel();
	static std::string computerLabel();
	static std::string rageLabel();
private:
	int playerIndex;
	Model* _model;
	View* _view;
	Controller* _controller;
	Gtk::VBox container;
	Gtk::Button togglePlayer;
	Gtk::Label points;
	Gtk::Label discards;
	static const std::string HUMAN_LABEL;
	static const std::string COMPUTER_LABEL;
	static const std::string RAGE_LABEL;

	void onClick();										// click handler for button
};

#endif
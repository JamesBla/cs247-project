/*
 *  Deck.cc
 *  
 *
 *  Created by Caroline Kierstead on 25/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>

#include <iostream>

using std::string;
using std::transform;
using namespace std;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {   
	"img/0_0.png", "img/0_1.png", "img/0_2.png", "img/0_3.png", "img/0_4.png", "img/0_5.png", "img/0_6.png", "img/0_7.png", "img/0_8.png", "img/0_9.png", "img/0_j.png", "img/0_q.png", "img/0_k.png", 
	"img/1_0.png", "img/1_1.png", "img/1_2.png", "img/1_3.png", "img/1_4.png", "img/1_5.png", "img/1_6.png", "img/1_7.png", "img/1_8.png", "img/1_9.png", "img/1_j.png", "img/1_q.png", "img/1_k.png", 
	"img/2_0.png", "img/2_1.png", "img/2_2.png", "img/2_3.png", "img/2_4.png", "img/2_5.png", "img/2_6.png", "img/2_7.png", "img/2_8.png", "img/2_9.png", "img/2_j.png", "img/2_q.png", "img/2_k.png", 
	"img/3_0.png", "img/3_1.png", "img/3_2.png", "img/3_3.png", "img/3_4.png", "img/3_5.png", "img/3_6.png", "img/3_7.png", "img/3_8.png", "img/3_9.png", "img/3_j.png", "img/3_q.png", "img/3_k.png",
	"img/nothing.png", "img/P_overlay.png", "img/D_overlay.png"
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name, int screenWidth) {
	// dynamically size cards according to screen width
	int cardWidth = screenWidth / 30;
	return Gdk::Pixbuf::create_from_file( name )->scale_simple(cardWidth, (int)(cardWidth/0.69), Gdk::INTERP_BILINEAR);
}

DeckGUI::DeckGUI(int width)  {
	
	_screenWidth = width;

	// we create a pixbuf from each png file and add it to our deck
	for (unsigned int i = 0; i < G_N_ELEMENTS(image_names); i++){
		string imgName = std::string(image_names[i]);
		_deck.push_back(createPixbuf(imgName,_screenWidth));
	}

}

DeckGUI::~DeckGUI() {
}

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage( Rank r, Suit s ) const {
	int index = ((int) s)*13 + ((int) r );
	return _deck[ index ];
}

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() const {
	int size = _deck.size();
	return _deck[ size-3 ];
}

// overlay for a play
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getPlayOverlay() const {
	int size = _deck.size();
	return _deck[ size-2 ];
}

// overlay for a discard
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getDiscardOverlay() const {
	int size = _deck.size();
	return _deck[ size-1 ];
} 
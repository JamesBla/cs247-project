/*
 *  Deck.h
 *  
 * Loads a series of pixmaps used for displaying the cards, as well as a card back used as a place marker in the
 * display when we don't have a card yet to display. Use pixel buffers to share images since widgets cannot be
 * shared.
 *
 *  Created by Caroline Kierstead on 25/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#ifndef DECK_GUI_H
#define DECK_GUI_H

#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"

using std::vector;

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Rank r, Suit s ) const;   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;                 // Returns the image to use for the placeholder.
	Glib::RefPtr<Gdk::Pixbuf> getPlayOverlay() const;
	Glib::RefPtr<Gdk::Pixbuf> getDiscardOverlay() const;
private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
}; // DeckGUI

#endif
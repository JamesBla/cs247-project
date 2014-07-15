#include "StraightsWindow.h"

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.

void StraightsWindow::onNewGame(){}
void StraightsWindow::onEndGame(){}

StraightsWindow::StraightsWindow() : hbox( true, 10 ), newGameButton("Start new game with seed:"), endGameButton("End current game"), 
cardsOnTable(4, 13, true) {
	set_title("Straights UI");
	// Sets the border width of the window.
	set_border_width( 10 );

	topContainer.pack_start(toolbar);
	topContainer.pack_start(cardsOnTableFrame);
	topContainer.pack_start(playersContainer);
	topContainer.pack_end(frame);

	toolbar.pack_start(newGameButton);
	toolbar.pack_start(seedEntry);
	toolbar.pack_end(endGameButton);

	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &StraightsWindow::onNewGame ) );
	seedEntry.set_text("0");
	seedEntry.set_alignment(0.5);
	endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &StraightsWindow::onEndGame ) );

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );

	cardsOnTableFrame.set_label("Cards on the table");
	cardsOnTable.set_row_spacings(5);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cardsPlayed[i][j] = new Gtk::Image(nullCardPixbuf);
			cardsOnTable.attach(*cardsPlayed[i][j], j, j+1, i, i+1);
		}
	}
	cardsOnTableFrame.add(cardsOnTable);

	for (int i = 0; i < 4; i++) {
		playerViews[i] = new PlayerView(i+1);
		playersContainer.pack_start(*playerViews[i]);
	}

	// Set the look of the frame.
	frame.set_label( "Cards:" );
	
	// Add the vbox to the window. Windows can only hold one widget, same for frames.
	add( topContainer );
	
	// Add the horizontal box for laying out the images to the frame.	
	frame.add( hbox );
	
	// Initialize 4 empty cards and place them in the box.
	for (int i = 0; i < 13; i++ ) {
		card[i] = new Gtk::Image( (i % 2 == 0) ? nullCardPixbuf : cardPixbuf);
		hbox.add( *card[i] );
	} // for

	// // Initialize the 5th card and place the image into the button.
	// card[4] = new Gtk::Image( cardPixbuf );	
	// button.set_image( *card[4] );	
			
	// // Add the button to the box.
	// hbox.add( button );
	
	// The final step is to display this newly created widget.
	show_all();
}

StraightsWindow::~StraightsWindow() {
	for (int i = 0; i < 13; i++ ) delete card[i];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) delete cardsPlayed[i][j];
	}
	
	for (int i = 0; i < 4; i++) {
		delete playerViews[i];
	}
}

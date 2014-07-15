#include <cstdlib>
#include <gtkmm.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "StraightsWindow.h"

int main( int argc, char * argv[] ) {
	// Creates a Gtk::Main object initialized from argument list. Necessary in all gtkmm applications.
	Gtk::Main kit( argc, argv );

	// Creates a window, which is displayed in the next command.
	StraightsWindow window;

	// Shows the window and enters the main gtkmm processing loop, which will finish when the window is closed.
	Gtk::Main::run( window );

	srand48( (argc > 1)? atoi(argv[1]) : 0);

	Model model; // Create model
	Controller controller( &model ); // Create controller
	View view( &controller, &model ); // Create the view

	controller.run();
	
	return 0;
}
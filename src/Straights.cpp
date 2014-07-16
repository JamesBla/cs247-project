#include <cstdlib>
#include <gtkmm.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

int main( int argc, char * argv[] ) {
	// Creates a Gtk::Main object initialized from argument list. Necessary in all gtkmm applications.
	Gtk::Main kit( argc, argv );

	// Creates a window, which is displayed in the next command.
	

	// Shows the window and enters the main gtkmm processing loop, which will finish when the window is closed.
	

	

	Model model; // Create model
	Controller controller( &model ); // Create controller
	View view( &controller, &model ); // Create the view
	Gtk::Main::run( view );
	// controller.run();
	
	return 0;
}
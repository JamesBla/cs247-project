#include <cstdlib>
#include <gtkmm.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

int main( int argc, char * argv[] ) {
	// Creates a Gtk::Main object initialized from argument list. Necessary in all gtkmm applications.
	Gtk::Main kit( argc, argv );

	Model model; // Create model
	Controller controller( &model ); // Create controller
	View view( &controller, &model ); // Create the view
	Gtk::Main::run( view );

	return 0;
}

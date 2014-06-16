#include "Model.h"
#include "View.h"
#include "Controller.h"


int main( int argc, char * argv[] ) {
	Model model; // Create model
	Controller controller( &model ); // Create controller
	View view( &controller, &model ); // Create the view

	controller.run();
	
	return 0;
}
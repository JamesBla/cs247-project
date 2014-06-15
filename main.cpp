


int main( int argc, char * argv[] ) {
	Model model; // Create model
	Controller controller( &model ); // Create controller
	View view( &controller, &model ); // Create the view

	return 0;
}
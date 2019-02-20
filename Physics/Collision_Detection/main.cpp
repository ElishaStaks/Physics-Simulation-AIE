#include "Collision_DetectionApp.h"

int main() {
	
	// allocation
	auto app = new Collision_DetectionApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
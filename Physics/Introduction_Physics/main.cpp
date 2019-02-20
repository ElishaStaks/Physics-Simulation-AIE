#include "Introduction_PhysicsApp.h"
#include <memory>

int main() {
	
	// This function will dump memory leaks to the visual studio output window upon termination
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new Introduction_PhysicsApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
#include "Fixed_TimestepApp.h"

int main() {

	// This function will dump memory leaks to the visual studio output window upon termination
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// allocation
	auto app = new Fixed_TimestepApp();

	// initialise and loop
	app->run("AIE", 1080, 720, false);

	// deallocation
	delete app;

	return 0;
}
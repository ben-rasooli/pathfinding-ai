//----------------------------------------------------------------------------
// This is the entry-point for your game.
// Creates and runs the Game2D class which contains the game loop.
//----------------------------------------------------------------------------
#include <crtdbg.h>
#include <iostream>
#include <string>
#include "Game2D.h"

using namespace std;

int main() 
{
	// Check for memeory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	string myStr_1 = "value";
	string myStr_2 = "value";
	const char* myChar_1 = "value";
	const char* myChar_2 = "value";

	if (myStr_1 == myStr_2)
		cout << "equal";

	if (myChar_1 == myChar_2)
		cout << "equal";


	// Create the Application.
	Game2D* game = new Game2D("AIE", 1280, 720, false);

	// Run the game loop.
	game->Run();

	// Clean up.
	delete game;

	return 0;
}
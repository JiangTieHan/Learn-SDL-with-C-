#include "Core/engine.h"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init failed" << endl;
	}

	return 0;
} 
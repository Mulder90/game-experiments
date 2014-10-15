#include "Game.h"
#include "PlayState.h"

int main()
{
	Game game{ "Arkanoid" };
	game.changeState(new PlayState());
	game.run();
	return 0;
}
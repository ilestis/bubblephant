#include <string>
#include "gameengine.h"
#include "play.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
	printf("Start");

	// Init engine
	GameEngine game;
	game.Init("Bubblephant v0.1");

	// Set state
	game.ChangeState(PlayState::Instance());

	while (game.Running()) {
		if (game.DoLoop()) {
			game.HandleEvents();
			game.Update();
			game.Draw();
		}
	}

	game.Cleanup();

	return 0;
}
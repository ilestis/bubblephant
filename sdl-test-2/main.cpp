#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <sstream>
#include <map>
#include <random>
#include "gameengine.h"
#include "play.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
EntityManager entityManager;
Timer timer; // Timer for events
SDL_Rect gBubbleSprites[3];
SDL_Texture *bubbles;



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

	// Make the Elephant
	/*Elephant elephant;
	elephant.reset(Window::Box().w / 2, Window::Box().h / 2);
	elephant.texture(eleTex);

	// Blocks
	reset();
	
	//Our event structure
	SDL_Event e;

	//For tracking if we want to quit
	bool quit = false;
	Uint32 lastTick = 0;

	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			//If user closes he window
			if (e.type == SDL_QUIT)
				quit = true;
			//If user presses any key
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
				case SDLK_RETURN:
					break;
					//For quitting, escape key
				case SDLK_ESCAPE: case SDLK_q:
					quit = true;
					break;
				default:
					break;
				}
			}

			// Handle elephant movement
			elephant.handleEvent(e);
		}*/


		
		/*// Timer
		std::stringstream ssTicks;
		float ticks = (float) timer.Ticks() / 1000;
		ticks = floor((ticks * 10) + 0.5) / 10;
		ssTicks << "Timer: " << ticks;
		Window::DrawText(ssTicks.str(), fontFile, white, 12, 0, 0);

		// Text preperation
		std::stringstream ssGuiX, ssGuiY, ssGuiMouse, ssGuiScore;

		// Score
		ssGuiScore << "Score: " << score;
		Window::DrawText(ssGuiScore.str(), fontFile, white, 32, 0, Window::Box().w / 2 - 50);

		// Debug
		ssGuiX << "VelX: " << elephant.velocityX();
		Window::DrawText(ssGuiX.str(), fontFile, white, 12, 430, 550);

		ssGuiY << "VelY: " << elephant.velocityY();
		Window::DrawText(ssGuiY.str(), fontFile, white, 12, 442, 550);

		ssGuiMouse << "MouX: " << elephant.mouseX();
		Window::DrawText(ssGuiMouse.str(), fontFile, white, 12, 454, 550);*/

		
		//Window::Present();
	//}
	//SDL_DestroyTexture(ticks);
	//Window::Quit();

	return 0;
}
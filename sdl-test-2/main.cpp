#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <sstream>
#include "window.h"
#include "timer.h"
#include "elephant.h"
#include "entity.h"
#include "entityManager.h"
#include <map>
#include <random>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
EntityManager entityManager;
Timer timer; // Timer for events
SDL_Texture *bubbles;
int score;

// Generate an item
void generateItem(int nbr)
{
	Entity* entity = new Entity();
	entity->position(-64, rand() % 500);
	entity->size(64, 64);
	entity->texture(bubbles);
	entity->type(1);
	entity->name("bubble" + nbr);
	entityManager.add(entity->name(), entity);
}

// Reset some items on the map
void reset()
{
	// Delete old the old items
	entityManager.clear();

	// Start timer
	timer.Start();

	score = 0;
}

int main(int argc, char** argv)
{
	// Start SDL window
	try {
		Window::Init("SDL test");
	}
	catch (const std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	// Load some stuff
	SDL_Texture *ticks, *eleTex, *guiMsg, *guiDebug, *guiScore;
	SDL_Color white = { 255, 255, 255 }; 
	std::string fontFile = "../res/font/cnl.ttf";

	try {
		// Load image first

		std::string imgFile = "../res/img/elephant.png";
		eleTex = Window::LoadImage(imgFile);
		// Bubbles
		imgFile = "../res/img/bubbles.png";
		bubbles = Window::LoadImage(imgFile);
	}
	catch (const std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	// Make the Elephant
	Elephant elephant;
	elephant.reset(Window::Box().w / 2, Window::Box().h / 2);
	elephant.texture(eleTex);

	// Blocks
	reset();
	

	//Set a position to draw it with
	SDL_Rect pos = { Window::Box().w / 2 - 150 / 2, Window::Box().h / 2 - 150 / 2, 150, 150 };

	//Our event structure
	SDL_Event e;

	//For tracking if we want to quit
	bool quit = false;


	// Gui positions
	SDL_Rect gui = { 0.00, 0.00, 150, 10 };
	SDL_Rect timerPos = { 150.00, 0.00, 30, 10 };
	SDL_Rect posDebugX = { 320, 0, 50, 15 };
	SDL_Rect posDebugY = { 380, 0, 50, 15 };
	SDL_Rect posDebugMouse = { 430, 0, 50, 15 };
	SDL_Rect posScore = { Window::Box().w / 2 - 50, 0, 100, 32 };

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
		}

		// Generate new items every 1 second
		if (timer.Ticks() >= 1000) {
			timer.Restart();
			if (rand() % 100 <= 30) { // 30% chance of generating
				generateItem(rand() % 5 + 100);
			}
		}

		// If the elephant hits the sides, restart
		if (elephant.outOfRange(Window::Box())) {
			elephant.reset(Window::Box().w / 2, Window::Box().h / 2);

			reset();
		}

		//RENDERING
		Window::Clear();

		std::map<std::string, Entity*> entities = entityManager.all();
		std::map<std::string, Entity*>::const_iterator itr = entities.begin();
		while(itr != entities.end())
		{
			// IF colide
			if ( entityManager.checkCollision(elephant.collider(), itr->second->collider()) ) {
				entityManager.remove(itr->second->name());
				score++;
			}
			else {
				itr->second->move();

				Window::Draw(itr->second->texture(), itr->second->position(), NULL);

				// Draw their collision box
				Window::DrawCollider(itr->second->collider(), 255);
			}
			itr++;
		}


		// Timer
		std::stringstream ssTicks;
		ssTicks << timer.Ticks() % 100;
		ticks = Window::RenderText(ssTicks.str(), fontFile, white, 9);
		Window::Draw(ticks, timerPos, NULL);

		
		// Update the elephant
		elephant.move();
		Window::Draw(elephant.texture(), elephant.position());
		Window::DrawCollider(elephant.collider(), 255);


		// Debug
		std::stringstream ssGuiX, ssGuiY, ssGuiMouse, ssGuiScore;
		ssGuiX << "VelX: " << elephant.velocityX();
		guiDebug = Window::RenderText(ssGuiX.str(), fontFile, white, 15);
		Window::Draw(guiDebug, posDebugX, NULL);

		ssGuiY << "VelY: " << elephant.velocityY();
		guiDebug = Window::RenderText(ssGuiY.str(), fontFile, white, 15);
		Window::Draw(guiDebug, posDebugY, NULL);

		ssGuiMouse << "MouX: " << elephant.mouseX();
		guiDebug = Window::RenderText(ssGuiMouse.str(), fontFile, white, 15);
		Window::Draw(guiDebug, posDebugMouse, NULL);

		// Score
		ssGuiScore << "Score: " << score;
		guiScore = Window::RenderText(ssGuiScore.str(), fontFile, white, 32);
		Window::Draw(guiScore, posScore, NULL);

		
		Window::Present();
	}
	//SDL_DestroyTexture(ticks);
	Window::Quit();

	return 0;
}
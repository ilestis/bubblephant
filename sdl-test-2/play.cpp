#include <stdio.h>

#include "SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "play.h"
#include "entityManager.h"
#include "elephant.h"
#include "timer.h"
#include <sstream>

PlayState PlayState::m_PlayState;

void PlayState::Init(GameEngine* game)
{
	m_elephant = Renderer::loadTexture("../res/img/elephant.png");
	m_bubble = Renderer::loadTexture("../res/img/bubbles.png");

	// Make elephant
	elephant.reset(game->m_width, game->m_height);
	elephant.texture(m_elephant);

	// Font
	m_font = "../res/font/cnl.ttf";

	// Make bubble
	timer.Start();

	m_color = { 255, 255, 255 };
	m_score = 0;

	printf("Play State initialised\n");
}

void PlayState::Cleanup()
{
	entityManager.clear();
	SDL_DestroyTexture(m_elephant);
	SDL_DestroyTexture(m_bubble);
}

void PlayState::GenerateItem(int nbr)
{
	Entity* entity = new Entity();
	entity->position(-64, rand() % 500);
	entity->size(64, 64);
	entity->texture(m_bubble);
	entity->type(1);
	entity->name("bubble" + nbr);
	entityManager.add(entity->name(), entity);
}

void PlayState::Pause()
{

}

void PlayState::Resume()
{

}

void PlayState::HandleEvents(GameEngine* game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e)){
		//If user closes he window
		if (e.type == SDL_QUIT) {
			game->Quit();
			break;
		}
		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym){
			case SDLK_m:
				break;
				//For quitting, escape key
			case SDLK_ESCAPE: case SDLK_q:
				game->Quit();
				break;
			default:
				break;
			}
		}

		// Handle elephant movement
		elephant.handleEvent(e);
	}
}

void PlayState::Update(GameEngine* game)
{
	elephant.move();

	// Generate new items every 0.5 second
	if (timer.Ticks() - m_lastTick >= 500) {
		m_lastTick = timer.Ticks();
		if (rand() % 100 <= 40) { // 40% chance of generating
			GenerateItem(rand() % 5 + 100);
		}
	}

	// If the elephant hits the sides, restart
	if (elephant.outOfRange(game->m_width, game->m_height)) {
		elephant.reset(game->m_width / 2, game->m_height / 2);
		Reset();
	}

	// Update all the entities
	std::map<std::string, Entity*> entities = entityManager.all();
	std::map<std::string, Entity*>::const_iterator itr = entities.begin();
	while (itr != entities.end()) {
		// Collison
		if (entityManager.checkCollision(elephant.collider(), itr->second->collider())) {
			entityManager.remove(itr->second->name());
			m_score++;
		}
		// Move and draw
		else {
			itr->second->move();
		}
		itr++;
	}


}

void PlayState::Draw(GameEngine* game)
{
	// Always clear first
	Renderer::Clear();

	// Draw all the entities
	std::map<std::string, Entity*> entities = entityManager.all();
	std::map<std::string, Entity*>::const_iterator itr = entities.begin();

	while (itr != entities.end()) {
		Renderer::renderTexture(itr->second->texture(), itr->second->position(), &itr->second->clip(timer.Ticks()));
		itr++;
	}

	// Draw elephant
	Renderer::renderTexture(elephant.texture(), elephant.position());


	// Gui timer
	std::stringstream ssTicks;
	float ticks = (float) timer.Ticks() / 1000;
	ticks = floor((ticks * 10) + 0.5) / 10;
	ssTicks << "Timer: " << ticks;
	Renderer::renderText(ssTicks.str(), m_font, m_color, 12, 0, 0);

	// Text preperation
	std::stringstream ssGuiX, ssGuiY, ssGuiMouse, ssGuiScore;

	// Score
	ssGuiScore << "Score: " << m_score;
	Renderer::renderText(ssGuiScore.str(), m_font, m_color, 32, 0, game->m_width / 2 - 50);

	// Debug
	ssGuiX << "VelX: " << elephant.velocityX();
	Renderer::renderText(ssGuiX.str(), m_font, m_color, 12, 430, 550);

	ssGuiY << "VelY: " << elephant.velocityY();
	Renderer::renderText(ssGuiY.str(), m_font, m_color, 12, 442, 550);

	ssGuiMouse << "MouX: " << elephant.mouseX();
	Renderer::renderText(ssGuiMouse.str(), m_font, m_color, 12, 454, 550);


	Renderer::Present();
}

void PlayState::Reset()
{
	m_score = 0;
	entityManager.clear();
	timer.Start();
}
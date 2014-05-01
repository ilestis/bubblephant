#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "elephant.h"
#include "entityManager.h"
#include "timer.h"
#include "renderer.h"

class PlayState : public GameState
{
public:
	void Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	void GenerateItem(int nbr);
	void Reset();

	static PlayState* Instance() {
		return &m_PlayState;
	}

protected:
	PlayState() { }

private:
	static PlayState m_PlayState;

	SDL_Texture *m_elephant, *m_bubble;
	SDL_Color m_color;
	std::string m_font;
	Elephant elephant;
	EntityManager entityManager;
	Timer timer;
	SDL_Rect gBubbleSprites[3];
	int m_score;
	Uint32 m_lastTick;
};
#endif
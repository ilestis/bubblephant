#pragma once
#include "entity.h"
#include <string>
#include <SDL.h>
#include <map>


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void add(std::string name, Entity* entity);
	void remove(std::string name);
	void clear();
	int objectCount() const;
	Entity* get(std::string name) const;

	void DrawAll(SDL_Window& window);
	std::map<std::string, Entity*> all();

	bool checkCollision(SDL_Rect a, SDL_Rect b);

private:
	std::map<std::string, Entity*> _entities;

};
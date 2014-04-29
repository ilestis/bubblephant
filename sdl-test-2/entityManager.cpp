#include "entityManager.h"
#include <algorithm>

EntityManager::EntityManager()
{

}
EntityManager::~EntityManager()
{

}

void EntityManager::add(std::string name, Entity* entity)
{
	_entities.insert(std::pair<std::string, Entity*>(name, entity));
}
void EntityManager::remove(std::string name)
{
	std::map<std::string, Entity*>::iterator results = _entities.find(name);
	if (results != _entities.end())
	{
		delete results->second;
		_entities.erase(results);
	}
}

Entity* EntityManager::get(std::string name) const
{
	std::map<std::string, Entity*>::const_iterator results = _entities.find(name);
	if (results == _entities.end())
		return NULL;
	return results->second;
}

void EntityManager::clear()
{
	_entities.clear();
}

void EntityManager::DrawAll(SDL_Window& window)
{

	std::map<std::string, Entity*>::const_iterator itr = _entities.begin();
	while (itr != _entities.end())
	{
		/*itr->second->Draw(window);
		itr++;*/
	}
}

std::map<std::string, Entity*> EntityManager::all()
{
	return _entities;
}

int EntityManager::objectCount() const{
	return _entities.size();
}

bool EntityManager::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// Compare the values
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}
	return true;
}
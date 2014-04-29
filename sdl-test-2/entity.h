#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "window.h"

class Entity
{
public:
	Entity();
	void move(); // Move the entity onthe screen

	// Rendering
	SDL_Texture* texture(); // Getting the texture
	void texture(SDL_Texture* tex); // Setting the entity texture

	SDL_Rect position();
	void position(int top, int left);

	void size(int height, int width);

	void remove();
	void draw(SDL_Window& window);

	void type(int type);
	int type();

	void name(std::string name);
	std::string name();

	SDL_Rect collider();

private:

	int mPosX, mPosY; // Position
	int mHeight, mWidth; // Spirite size
	int mType;
	std::string mName;

	SDL_Texture* mTexture;
	SDL_Rect mCollider;

	bool loaded;
};

#endif
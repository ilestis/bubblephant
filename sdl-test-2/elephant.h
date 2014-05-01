#ifndef ELEPHANT_H
#define ELEPHANT_H

#include <SDL.h>

class Elephant
{
public:
	static const int WIDTH = 32;
	static const int HEIGHT = 32;

	Elephant();

	void handleEvent(SDL_Event& e);

	void move();
	void update();
	void reset(int x, int y);

	SDL_Texture* texture();
	void texture(SDL_Texture* tex);

	SDL_Rect position();
	void position(int top, int left);

	float velocityX();
	float velocityY();
	int mouseX();

	bool outOfRange(int width, int height);
	SDL_Rect collider();

	int energy();

private:
	int mPosX, mPosY; // Position
	int mHeight, mWidth; // Spirite size

	bool moving; // Status
	int mMouseX;
	float mVelX, mVelY; // Velocity
	float mMaxVelX, mMaxVelY; // Max velocity
	float mMinVelX, mMinVelY;
	int mEnergy;

	SDL_Texture* mTexture;
	SDL_Rect mCollider;
};

#endif
#include "elephant.h"

Elephant::Elephant()
{
	// Set the elephant at the center of the page
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	mMaxVelY = 5;
	mMinVelY = -2;
	mMaxVelX = 5;
	mMinVelX = -5;

	mWidth = 32;
	mHeight = 32;

	mEnergy = 255;
	moving = false;
}

// Handle input from SDL
void Elephant::handleEvent(SDL_Event& e)
{

	// Mouse keydown
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		moving = true;		
	}
	// Mouse up
	else if (e.type == SDL_MOUSEBUTTONUP) {
		moving = false;
	}

	if (moving) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		mMouseX = x;
	}
}

void Elephant::move()
{
	// Update Velocity
	update();
	
	// Left or Right
	mPosX += mVelX;
	mCollider.x = mPosX;

	// Up or Down
	mPosY += mVelY;
	mCollider.y = mPosY;
}

void Elephant::texture(SDL_Texture* tex)
{
	mTexture = tex;
}

void Elephant::update()
{
	// Still moving
	if (moving) {
		// Going up
		mVelY -= 0.1;
		if (mVelY < mMinVelY) {
			mVelY = mMinVelY;
		}
		else if (mVelY < 0) {
			mVelY -= 0.1;
		}

		// Moving towards where the mouse was clicked
		int realPosX = mPosX + (mWidth / 2);
		int errorMargin = 5;

		// Move to the right
		if (mMouseX > (realPosX - errorMargin) && mMouseX > (realPosX + errorMargin)) {
			mVelX += 0.1;
			if (mVelX > mMaxVelX) {
				mVelX = mMaxVelX;
			}
		}
		// Move left
		else if (mMouseX < (realPosX - errorMargin) && mMouseX < (realPosX + errorMargin)) {
			mVelX -= 0.1;
			if (mVelX < mMinVelX) {
				mVelX = mMinVelX;
			}
		}
		// Close enough, slow down
		else {
			//mVelX = 0; // Stop it
			if (mVelX > 0.1) {
				mVelX -= 0.2;
			}
			else if(mVelX < 0) {
				mVelX += 0.2;
			}
			else {
				mVelX = 0.0;
			}
		}
	}
	// Stopped moving
	else {
		// Decelerate top movement
		mVelY += 0.1;
		//mVelY = 0;
		if (mVelY > mMaxVelY) {
			mVelY = mMaxVelY;
		}

		// Slow down side movement
		if (mVelX > 0.1) {
			mVelX -= 0.02;
		}
		else if (mVelX < 0.0) {
			mVelX += 0.02;
		}
		else {
			mVelX = 0.0;
		}
	}
}

SDL_Texture* Elephant::texture()
{
	return mTexture;
}

// Set and get position
void Elephant::position(int top, int left)
{
	mPosX = top;
	mPosY = left;

	mCollider.y = top;
	mCollider.x = left;
}
SDL_Rect Elephant::position()
{
	SDL_Rect pos = { mPosX, mPosY, mWidth, mHeight };
	return pos;
}

int Elephant::energy()
{
	return mEnergy;
}

float Elephant::velocityX()
{
	return mVelX;
}
float Elephant::velocityY()
{
	return mVelY;
}

int Elephant::mouseX()
{
	return mMouseX;
}

/**
 * Check wether the elephant is out of the window, forcing a game other
 */
bool Elephant::outOfRange(SDL_Rect box)
{
	bool outX = mPosX <= 0 || (mPosX + mWidth >= box.w);
	return (mPosX <= 0) || (mPosX + mWidth >= box.w) ||
		(mPosY <= 0) || (mPosY + mHeight >= box.h);
}

void Elephant::reset(int x, int y)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0;
	mVelY = 0;
	mEnergy = 255;

	mCollider.y = mPosY;
	mCollider.x = mPosX;
	mCollider.h = mHeight;
	mCollider.w = mWidth;
}

SDL_Rect Elephant::collider()
{
	return mCollider;
}
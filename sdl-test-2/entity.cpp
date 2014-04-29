#include "entity.h";

Entity::Entity()
{
	// Default stuff
	loaded = true;
}

// Only move item downwards
void Entity::move()
{
	mPosY += 1;
	mCollider.y = mPosY;
}

// Set and get texture
void Entity::texture(SDL_Texture* tex) {
	mTexture = tex;
}
SDL_Texture* Entity::texture() {
	return mTexture;
}

// Set and get position
void Entity::position(int top, int left)
{
	mPosX = left;
	mPosY = top;

	mCollider.y = top;
	mCollider.x = left;
}
SDL_Rect Entity::position()
{
	SDL_Rect pos = { mPosX, mPosY, mWidth, mHeight };
	return pos;
}

// Size
void Entity::size(int height, int width)
{
	mHeight = height;
	mWidth = width;

	mCollider.w = width;
	mCollider.h = height;
}

// Get and set type
void Entity::type(int type) {
	mType = type;
}
int Entity::type() {
	return mType;
}

// Remove the entity
void Entity::remove() {

}

SDL_Rect Entity::collider() {
	return mCollider;
}

// Name setter and getter
void Entity::name(std::string name) {
	mName = name;
}

std::string Entity::name() {
	return mName;
}

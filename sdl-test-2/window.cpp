#include <string>
#include <stdexcept>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "window.h"

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> Window::mWindow
	= std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> Window::mRenderer
	= std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
//Other static members
SDL_Rect Window::mBox;

void Window::Init(std::string title) {
	// Initialize SDL and subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL init failed");
	if (TTF_Init() == -1)
		throw std::runtime_error("TTF init failed");

	// Set up display
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = 640;
	mBox.h = 480;

	// Create the SDL window
	mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN));
	//Make sure it created ok
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to create window");

	//Create the renderer
	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	//Make sure it created ok
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to create renderer");
}

// Quit and release
void Window::Quit() {
	TTF_Quit();
	SDL_Quit();
}

void Window::Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle,
	int xPivot, int yPivot, SDL_RendererFlip flip)
{
	//Convert pivot pos from relative to object's center to screen space
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	//SDL expects an SDL_Point as the pivot location
	SDL_Point pivot = { xPivot, yPivot };
	//Draw the texture
	SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dstRect, angle, &pivot, flip);
}

void Window::DrawCollider(SDL_Rect collider, int color) {
	SDL_SetRenderDrawColor(mRenderer.get(), 255, 255, 255, 255);
	SDL_RenderDrawRect(mRenderer.get(), &collider);
}

// Load image
SDL_Texture* Window::LoadImage(const std::string &file){
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}

// Render text
SDL_Texture* Window::RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize){
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

void Window::DrawText(const std::string &message, const std::string &font, SDL_Color color, int size,
	int top, int left)
{	
	TTF_Font *ttffont = nullptr;
	ttffont = TTF_OpenFont(font.c_str(), size);
	if (ttffont == nullptr)
		throw std::runtime_error("Failed to load font: " + font + TTF_GetError());

	SDL_Surface *surface = TTF_RenderUTF8_Blended(ttffont, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surface);

	SDL_Rect destination = { 0, 0, 0, 0 };
	destination.x = left;
	destination.y = top;

	TTF_SizeUTF8(ttffont, message.c_str(), &destination.w, &destination.h);
	
	// Draw
	SDL_RenderCopy(mRenderer.get(), texture, NULL, &destination);

	// Close
	SDL_FreeSurface(surface);
	TTF_CloseFont(ttffont);

}

// Clear
void Window::Clear() {
	SDL_RenderClear(mRenderer.get());
}

// Present
void Window::Present() {
	SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0);
	SDL_RenderPresent(mRenderer.get());
}

// Box
SDL_Rect Window::Box() {
	// Update mBox to match the current window size
	SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
	return mBox;
}
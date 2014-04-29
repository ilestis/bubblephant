#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif


class Window {
public:
	//Start SDL and TTF, create the window and renderer
	static void Init(std::string title = "Window");
	//Quit SDL and TTF
	static void Quit();
	//Draw an SDL_Texture
	static void Draw(SDL_Texture*, SDL_Rect &dstRect, SDL_Rect *clip = NULL,
		float angle = 0.0, int xPivot = 0, int yPivot = 0,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Draw rectangle
	static void DrawCollider(SDL_Rect collider, int color);

	//Load an image
	static SDL_Texture* LoadImage(const std::string &file);
	//Render some text
	static SDL_Texture* RenderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize);
	static void DrawText(const std::string &message, const std::string &fontfile,
		SDL_Color color, int fontSize, int top, int left);
	//Clear window
	static void Clear();
	//Present renderer
	static void Present();
	//Get the window's box
	static SDL_Rect Box();

private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> mWindow;
	static std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> mRenderer;
	static SDL_Rect mBox;
};


#endif
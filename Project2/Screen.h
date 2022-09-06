#pragma once
#include <SDL.h>
#include <iostream>

namespace ScreenP {
	class Screen {
	public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;
	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		Uint32* m_buffer1;
		Uint32* m_buffer2;

	public:
		Screen();
		bool init();
		bool processEvents();
		void close();
		void update();
		void boxBlur();
		void setPixel(int x, int y, Uint32 red, Uint32 green, Uint32 blue);
		void Clear();

	};



}


#include "Screen.h"

namespace ScreenP {

	Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {

	}


	bool Screen::init() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			SDL_Quit();
			return false;
		}

		m_window = SDL_CreateWindow("Partical Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //must check if not null *use exption //to do for later 
		m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //must check if not null *use exption //to do for later 
		std::memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); //put 255 in every pixel in the screen
		std::memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); //put 255 in every pixel in the screen



		return  true;
	}
	bool Screen::processEvents() {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return  false;
			}
		}
		return  true;

	}
	void Screen::close() {
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
	void Screen::setPixel(int x, int y, Uint32 red, Uint32 green, Uint32 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}
		Uint32 color = 0;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;
		m_buffer1[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32)); ///one line at the time
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::boxBlur()
	{//swap buffers 
		Uint32* temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;


		for (int x = 0; x < SCREEN_WIDTH; x++){
			for (int y = 0; y < SCREEN_HEIGHT; y++){

				/*
						000
						010
						000
				*/
				int redTotal = 0, GreenTotal = 0, blueTotal = 0;
				for (int row = -1; row <= 1; row++){
					for (int  col = -1; col <= 1; col++){
						int currentX = x + col;
						int currenty = y + row;
						if (currentX >= 0 && currentX < SCREEN_WIDTH && currenty >= 0 && currenty < SCREEN_HEIGHT) {
							Uint32 color = m_buffer2[(currenty * SCREEN_WIDTH) + currentX];
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							GreenTotal += green;
							blueTotal += blue;
						}

					}

				}
				Uint8 red = redTotal/9;
				Uint8 green = GreenTotal/9;
				Uint8 blue = blueTotal/9;

				setPixel(x,y,red,green,blue);

			}

		}

	}



}

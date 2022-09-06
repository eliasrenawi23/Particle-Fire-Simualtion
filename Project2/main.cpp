#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include <math.h>
#include <stdlib.h>
#include "Swarm.h"
using namespace ScreenP;
using namespace std;


int main(int argc, char* args[]) {

	srand(time(NULL));
	Screen screen;
	if (screen.init() == false) {
		cout << "Could not initialising SDL:  " << SDL_GetError() << "\n" << endl;
	}
	Swarm swarm;





	while (true) {
		//update particles
		//Drow particles
		int elapsed = SDL_GetTicks();
		//screen.Clear();
		swarm.update(elapsed);
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.003)) * 128);

		const Particle* const pParticles = swarm.getParticles();  //get the pinter to the partical array and put ther postion pixels

		for (int i = 0; i < Swarm::NPARTICLES; i++){
			Particle particle = pParticles[i];
			int x = (particle.m_x + 1)*Screen::SCREEN_WIDTH/2;
			int y = particle.m_y*Screen::SCREEN_WIDTH /2 + Screen::SCREEN_HEIGHT/2;
			screen.setPixel(x, y, red, green, blue);


		}
		screen.boxBlur();
		screen.update();
		//check for messages/events
		if (screen.processEvents() == false) {
			break;
		}
	}


	screen.close();

	return 0;
}
//Using SDL and standard IO
#include <stdio.h>
#include <string>
#include "SDL/include/SDL.h"
#include "SDL_Image/Include/SDL_image.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")


const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 640;



int main(int argc, char* args[]) {
	int SDL_Init(SDL_INIT_VIDEO);
	int IMG_Init(IMG_INIT_PNG);


	float vel = 5;
	bool sumarx = true, sumary = true, shoot = false, right = false, left = false, up = false, down = false, recarga = true;


	SDL_Window* gWindow;				//The window we'll be rendering to

	SDL_Renderer* gScreenSurface;		//The surface contained by the window

	SDL_Rect rectangle;					//The render controlled by the player

	SDL_Rect projectile;				//Projectile we will shoot with space


	bool quit = false;
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gScreenSurface = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	//Event handler
	SDL_Event event;

	rectangle.x = 20;
	rectangle.y = 20;
	rectangle.w = 200;
	rectangle.h = 100;

	projectile.x = rectangle.x + 150;
	projectile.y = rectangle.y + 30;
	projectile.w = 100;
	projectile.h = 40;

	SDL_Surface *image;
	image = IMG_Load("Assets/shrek.png");
	if (!image) {
		quit = true;

	}



	//***GAME LOOP***
	while (!quit)
	{ 
		SDL_Delay(1);
		const Uint8 *state = SDL_GetKeyboardState(NULL);								// const state
		//INPUT INFO		
		while (SDL_PollEvent(&event) != 0)												//Handle events on queue
		{
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			
			
		}
//Events
			if (state[SDL_SCANCODE_UP]) {
				up = true;
			}
			if (state[SDL_SCANCODE_DOWN]) {
				down = true;
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				right = true;
			}
			if (state[SDL_SCANCODE_LEFT]) {
				left = true;
			}
			if (state[SDL_SCANCODE_SPACE]) {
				shoot = true;
			}
			if (state[SDL_SCANCODE_ESCAPE]) {
				quit = true;
			}
			
			//Simultaneous events
			if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_SPACE]) {
				down = true;
				shoot= true;
			}
			if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]) {
				down = true;
				left = true;
			}
			if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]) {
				down = true;
				right = true;
			}

			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_SPACE]) {
				up = true;
				shoot = true;
			}
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) {
				up = true;
				left = true;
			}
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) {
				up = true;
				right = true;
			}
			if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_SPACE]) {
				right = true;
				shoot = true;
			}
			if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_SPACE]) {
				left = true;
				shoot = true;
			}
			if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]) {
				right = true;
				left = true;
			}
	//POSITION CHANGES
																		//Red rectangle
	if (up == true && rectangle.y > 0) {
		rectangle.y -= 2;
		up = false;
	}
	if (down == true && rectangle.y < SCREEN_HEIGHT - 100) {
		rectangle.y += 2;
		down = false;
	}
	if (right == true && rectangle.x < SCREEN_WIDTH - 200) {
		rectangle.x += 2;
		right = false;
	}
	if (left == true && rectangle.x > 0){
		rectangle.x -= 2;
		left = false;
	}


	if (shoot == true) {										//Green rectangle
		if (recarga == true){
			projectile.x = rectangle.x + 150;
			projectile.y = rectangle.y + 30;
			recarga = false;
		}
		projectile.x += vel;
		if (projectile.x > SCREEN_WIDTH + 100) {
			shoot = false;
			projectile.x = rectangle.x + 150;
			projectile.y = rectangle.y + 30;
			recarga = true;
		}
	}


	//DRAW ON SCREEN
	SDL_SetRenderDrawColor(gScreenSurface, 0, 0, 0xff, 0xff);
	SDL_RenderClear(gScreenSurface);


	SDL_SetRenderDrawColor(gScreenSurface, 255, 0, 0, 0);							//Draw red rectangle, color
	SDL_RenderFillRect(gScreenSurface, &rectangle);									//Size


	if (shoot == true) {
		SDL_SetRenderDrawColor(gScreenSurface, 0, 255, 0, 0);
		SDL_RenderFillRect(gScreenSurface, &projectile);

	}

	SDL_RenderPresent(gScreenSurface);												//Show renders



}
//Free resources and close SDL
	SDL_DestroyRenderer(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

//Quit SDL subsystems
	IMG_Quit();	SDL_Quit();
	return 0;
}


//Using SDL and standard IO

#include <stdio.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"


#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image")

#define SHAPE_SIZE 16
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  960

int main(int argc, char* args[]) {
	int SDL_Init(SDL_INIT_VIDEO);
	int IMG_Init(IMG_INIT_PNG);
	float vel = 30;
	bool sumarx = true, sumary = true, shoot = false, right = false, left = false, up = false, down = false, recarga = true;


	SDL_Window* gWindow;				//The window we'll be rendering to

	SDL_Renderer* Main_Renderer;		//The surface contained by the window

	SDL_Rect rectangle;					//The render controlled by the player

	SDL_Rect projectile;				//Projectile we will shoot with space
	SDL_Surface * Loading_Surf;

	SDL_Texture* Image;
	SDL_Texture* Background;
	SDL_Texture* Bullet;

	SDL_Rect SrcR;
	SDL_Rect DestR;
	SDL_Rect SrcProj;
	SDL_Rect DestProj;

	bool quit = false;
/*
	rectangle.x = 20;
	rectangle.y = 20;
	rectangle.w = 200;
	rectangle.h = 100;

	projectile.x = rectangle.x + 150;
	projectile.y = rectangle.y + 30;
	projectile.w = 100;
	projectile.h = 40;
*/
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = 580;
	SrcR.h = 793;

	DestR.x = 20;
	DestR.y = 20;
	DestR.w = 200;
	DestR.h = 200;

	SrcProj.x = 0;
	SrcProj.y = 0;
	SrcProj.w = 410;
	SrcProj.h = 250;

	DestProj.x = DestR.x+ 70;
	DestProj.y = DestR.y;
	DestProj.w = 125;
	DestProj.h = 70;

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Main_Renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	//Event handler
	SDL_Event event;

	//crea textura fondo
	Loading_Surf = IMG_Load("Assets/back.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);
	
	//Crea textura jugador
	Loading_Surf = IMG_Load("Assets/player.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Image = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	//Crea textura jugador
	Loading_Surf = IMG_Load("Assets/bullet.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Bullet = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);
	
	//***GAME LOOP***
	while (!quit)
	{ 
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
	if (up == true && DestR.y > 0) {
		DestR.y -= 10;
		up = false;
	}
	if (down == true && DestR.y < SCREEN_HEIGHT - 100) {
		DestR.y += 10;
		down = false;
	}
	if (right == true && DestR.x < SCREEN_WIDTH - 200) {
		DestR.x += 10;
		right = false;
	}
	if (left == true && DestR.x > 0){
		DestR.x -= 10;
		left = false;
	}


	if (shoot == true) {										//Green rectangle
		if (recarga == true){
			DestProj.x = DestR.x+ 70;
			DestProj.y = DestR.y+50;
			recarga = false;
		}
		DestProj.x += vel;
		if (DestProj.x > SCREEN_WIDTH + 100) {
			shoot = false;
			DestProj.x = DestR.x+ 70;
			DestProj.y = DestR.y+50;
			recarga = true;
		}
	}


	//DRAW ON SCREEN
/*	SDL_SetRenderDrawColor(Main_Renderer, 0, 0, 0xff, 0xff);
	SDL_RenderClear(Main_Renderer);

	SDL_SetRenderDrawColor(Main_Renderer, 255, 0, 0, 0);							//Draw red rectangle, color
	SDL_RenderFillRect(Main_Renderer, &rectangle);									//Size

	*/
	SDL_RenderCopy(Main_Renderer, Background, NULL, NULL);
	SDL_RenderCopy(Main_Renderer, Image, &SrcR, &DestR);

	if (shoot == true) {
		SDL_RenderCopy(Main_Renderer, Bullet, &SrcProj, &DestProj);

	}
	SDL_RenderPresent(Main_Renderer);												//Show renders
}
//Free resources and close SDL
	//SDL_DestroyTexture(Image);

	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return 0;
}


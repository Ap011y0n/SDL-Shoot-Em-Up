#include <stdio.h>
#include <string>
#include "SDL/include/SDL.h"
#include "SDL_image/Include/SDL_image.h"
#include "SDL_Mixer/Include/SDL_mixer.h"


#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

#define SHAPE_SIZE 16
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  760
#define BULLETNUM 5
#define BULLETDELAY 10
#define ENEMYNUM 6
#define ENEMYDELAY 15



int main(int argc, char* args[]) {
	int SDL_Init(SDL_INIT_VIDEO);
	int IMG_Init(IMG_INIT_PNG);
	int	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	int i, a, p = 0, j = 0, d = 0, cont = BULLETDELAY, cont2 = ENEMYDELAY, cont3 = ENEMYDELAY, conty[ENEMYNUM], conty2[ENEMYNUM], posinicial = SCREEN_HEIGHT/2, movy[ENEMYNUM], movy2[ENEMYNUM], respawntimer1 = 500, respawntimer2 = 0;
	float vel = 30;
	bool sumarx = true, sumary = true, shoot = false, right = false, left = false, up = false, down = false, recarga = true, respawn = false, respawn2 = false;
	for (i = 0; i < ENEMYNUM; i++) {
		conty[i] = 10;
		movy[i] = 2;
	}
	for (i = 0; i < ENEMYNUM; i++) {
		conty2[i] = 10;
		movy[i] = 2;
	}

	SDL_Window* gWindow;				//The window we'll be rendering to

	SDL_Renderer* Main_Renderer;		//The surface contained by the window

	SDL_Rect rectangle;					//The render controlled by the player

	SDL_Rect projectile;				//Projectile we will shoot with space
	SDL_Surface * Loading_Surf;

	SDL_Texture* Image;
	SDL_Texture* Background;
	SDL_Texture* Bullet[BULLETNUM];
	SDL_Texture* Enemy[ENEMYNUM];
	SDL_Texture* Enemy2[ENEMYNUM];


	SDL_Rect SrcR;
	SDL_Rect DestR;
	SDL_Rect SrcProj;
	SDL_Rect DestProj[BULLETNUM];
	SDL_Rect SrcEnem;
	SDL_Rect DestEnem[ENEMYNUM];
	SDL_Rect DestEnem2[ENEMYNUM];

	Mix_Music *shootSE;
	Mix_Chunk *backMus;

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

	for (i = 0; i < BULLETNUM; i++) {
		DestProj[i].x = 2000;
		DestProj[i].y = 2000;
		DestProj[i].w = 125;
		DestProj[i].h = 70;
	}
	SrcEnem.x = 0;
	SrcEnem.y = 0;
	SrcEnem.w = 410;
	SrcEnem.h = 250;

	for (i = 0; i < ENEMYNUM; i++) {
		DestEnem[i].x = 6000;
		DestEnem[i].y = 2000;
		DestEnem[i].w = 125;
		DestEnem[i].h = 70;
	}
	for (i = 0; i < ENEMYNUM; i++) {
		DestEnem2[i].x = 6000;
		DestEnem2[i].y = 2000;
		DestEnem2[i].w = 125;
		DestEnem2[i].h = 70;
	}


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
	for (i = 0; i < BULLETNUM; i++) {
		Bullet[i] = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	}
	if (!Loading_Surf) {
		quit = true;
	}

	Loading_Surf = IMG_Load("Assets/enemy.png");
	if (!Loading_Surf) {
		quit = true;
	}
	for (i = 0; i < ENEMYNUM; i++) {
		Enemy[i] = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	}
	if (!Loading_Surf) {
		quit = true;
	}

	SDL_FreeSurface(Loading_Surf);

	shootSE = Mix_LoadMUS("Assets/bulletSE.wav");
	if (!shootSE) {
		quit = true;
	}
	backMus = Mix_LoadWAV("Assets/Backmusic.ogg");
	if (!backMus) {
		quit = true;
	}
	Mix_PlayChannel(-1, backMus, 0);
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

		if (state[SDL_SCANCODE_SPACE]) {
			shoot = true;
		}

		if (state[SDL_SCANCODE_RIGHT]) {
			right = true;
		}
		if (state[SDL_SCANCODE_LEFT]) {
			left = true;
		}
		if (state[SDL_SCANCODE_UP]) {
			up = true;
		}
		if (state[SDL_SCANCODE_DOWN]) {
			down = true;
		}

		if (state[SDL_SCANCODE_ESCAPE]) {
			quit = true;
		}

		//POSITION CHANGES															
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
		if (left == true && DestR.x > 0) {
			DestR.x -= 10;
			left = false;
		}
		cont++;
		if (shoot == true && cont <= BULLETDELAY) {
			shoot = false;
		}
		if (shoot == true && cont > BULLETDELAY) {
			recarga = true;
			shoot = false;
			cont = 0;
			Mix_PlayMusic(shootSE, 0);
			DestProj[j].x = DestR.x + 70;
			DestProj[j].y = DestR.y + 50;

			j++;
			if (j >= BULLETNUM) {
				j = 0;
			}
		}
		for (i = 0; i < BULLETNUM; i++) {
			DestProj[i].x += vel;
		}

		//POSICION INICIAL
		//Linea de enemigos 1
		respawntimer1++;
		if (respawntimer1 > 300) {
			respawn = true;
		}
		cont2++;
		if (respawn == true) {
			if (cont2 > ENEMYDELAY) {
				cont2 = 0;
				DestEnem[p].x = 1280;
				DestEnem[p].y = SCREEN_HEIGHT / 2;
				p++;
				if (p == ENEMYNUM - 1) {
					p = 0;
					respawn = false;
					respawntimer1 = 0;
				}
			}
		}
	
		for (i = 0; i < ENEMYNUM; i++) {
		DestEnem[i].x -= 8;

	if (DestEnem[i].x < 1000){
			if (conty[i] <= 5) {
				movy[i]++;
			}
			if ( conty[i] >= 30) {
				movy[i]++;
			}
			if (movy[i] % 2 != 0) {
				conty[i]--;
				DestEnem[i].y -= 3;
			}
			else {
				conty[i]++;
				DestEnem[i].y+=3;
			}
			
	}		
}

		//Linea de enemigos 2
	cont3++;
	respawntimer2++;
	if (respawntimer2 > 200) {
		respawn2 = true;
	}
	if (respawn2 == true) {
		if (cont3 > ENEMYDELAY) {
			cont3 = 0;
			DestEnem2[d].x = 1280;
			DestEnem2[d].y = SCREEN_HEIGHT / 4;
			d++;
			if (d == ENEMYNUM - 1) {
				d = 0;
				respawn2 = false;
				respawntimer2 = false;
			}
		}
	}

	for (i = 0; i < ENEMYNUM; i++) {
		DestEnem2[i].x -= 8;

		if (DestEnem2[i].x < 1000) {
			if (conty2[i] <= 5) {
				movy2[i]++;
			}
			if (conty2[i] >= 30) {
				movy2[i]++;
			}
			if (movy2[i] % 2 != 0) {
				conty2[i]--;
				DestEnem2[i].y -= 3;
			}
			else {
				conty2[i]++;
				DestEnem2[i].y += 3;
			}

		}
	}
	for (i = 0; i < ENEMYNUM; i++) {
		for (a = 0; a< BULLETNUM; a++) {
			if (DestProj[a].y > DestEnem[i].y - 25 && DestProj[a].y < DestEnem[i].y + 25 && DestProj[a].x > DestEnem[i].x - 25 && DestProj[a].x < DestEnem[i].x + 25) {
				DestEnem[i].y += 5000;
				DestProj[a].y += 6000;

			}
		}
	}
	for (i = 0; i < ENEMYNUM; i++) {
		for (a = 0; a< BULLETNUM; a++) {
			if (DestProj[a].y > DestEnem2[i].y - 25 && DestProj[a].y < DestEnem2[i].y + 25 && DestProj[a].x > DestEnem2[i].x - 25 && DestProj[a].x < DestEnem2[i].x + 25) {
				DestEnem2[i].y += 5000;
				DestProj[a].y += 6000;

			}
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

		for (i = 0; i < BULLETNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Bullet[i], &SrcProj, &DestProj[i]);
		}
		for (i = 0; i < ENEMYNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Enemy[i], &SrcEnem, &DestEnem[i]);
		}
		for (i = 0; i < ENEMYNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Enemy2[i], &SrcEnem, &DestEnem2[i]);
		}
		
		SDL_RenderPresent(Main_Renderer);												//Show renders
	}


	//Free resources and close SDL
	Mix_FreeMusic(shootSE);	Mix_FreeChunk(backMus);
	SDL_DestroyTexture(Image);
	SDL_DestroyTexture(Background);
	for (i = 0; i < BULLETNUM; i++) {
		SDL_DestroyTexture(Bullet[i]);
	}

	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

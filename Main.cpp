#include <stdio.h>
#include <string>
#include "SDL/include/SDL.h"
#include "SDL_image/Include/SDL_image.h"
#include "SDL_Mixer/Include/SDL_mixer.h"
#include <time.h>   


#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

#define SHAPE_SIZE 16
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT  760
#define BULLETNUM 5
#define BULLETDELAY 7
#define ENEMYNUM 6
#define ENEMYDELAY 15
#define BOSSDELAY 10
#define BOSSPROJNUM 100



int main(int argc, char* args[]) {

	SDL_Window* gWindow;				//The window we'll be rendering to

	SDL_Renderer* Main_Renderer;		//The surface contained by the window
	SDL_Surface * Loading_Surf;

	SDL_Texture* Image;
	SDL_Texture* Background0;
	SDL_Texture* Background1;
	SDL_Texture* Background2;
	SDL_Texture* Background1bis;
	SDL_Texture* Background2bis;
	SDL_Texture* Gameover;
	SDL_Texture* Win;
	SDL_Texture* Bullet[BULLETNUM];
	SDL_Texture* Enemy[ENEMYNUM];
	SDL_Texture* Enemy2[ENEMYNUM];
	SDL_Texture* Health[5];
	SDL_Texture* Boss;
	SDL_Texture* projboss[BOSSPROJNUM];

	SDL_Rect Bossdest;
	SDL_Rect Bossprojdest[BOSSPROJNUM];
	SDL_Rect Backcoord;
	SDL_Rect Backcoord2;
	SDL_Rect Backcoordbis;
	SDL_Rect Backcoordbis2;
	SDL_Rect GOsrc;
	SDL_Rect GOdest;
	SDL_Rect Windest;
	SDL_Rect HPsrc;
	SDL_Rect HPdest[5];
	SDL_Rect SrcR;
	SDL_Rect DestR;
	SDL_Rect SrcProj;
	SDL_Rect DestProj[BULLETNUM];
	SDL_Rect SrcEnem;
	SDL_Rect DestEnem[ENEMYNUM];
	SDL_Rect DestEnem2[ENEMYNUM];

	Mix_Music *shootSE;
	Mix_Music *hit;
	Mix_Music *hit2;

	Mix_Chunk *backMus;

	srand(time(NULL));
	int SDL_Init(SDL_INIT_VIDEO);
	int IMG_Init(IMG_INIT_PNG);
	int	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	int i, s = 0, hp = 5, a, p = 0, j = 0, d = 1, cont = BULLETDELAY, cont2 = ENEMYDELAY, cont3 = ENEMYDELAY, cont4 = BOSSDELAY, conty[ENEMYNUM], conty2[ENEMYNUM], posinicial = SCREEN_HEIGHT / 2, movy[ENEMYNUM], movy2[ENEMYNUM], respawntimer1 = 500, respawntimer2 = 0, randomy;
	int vel = 30, round = 0, y[BOSSPROJNUM], yneg[BOSSPROJNUM], bosshp=200;
	bool sumarx = true, sumary = true, shoot = false, right = false, left = false, up = false, down = false, recarga = true, respawn = false, respawn2 = false, generatenum = true, bossphase = false, showboss = true, showship = true;
	for (i = 0; i < ENEMYNUM; i++) {
		conty[i] = 10;
		movy[i] = 2;
	}
	for (i = 0; i < ENEMYNUM; i++) {
		conty2[i] = 10;
		movy[i] = 2;
	}

	bool quit = false;

	Bossdest.x = SCREEN_WIDTH + 100;
	Bossdest.y = 60;
	Bossdest.h = SCREEN_HEIGHT;
	Bossdest.w = Bossdest.h + 100;
	for (i = 0; i < BOSSPROJNUM; i++) {
		Bossprojdest[i].x = 3000;
		Bossprojdest[i].y = 3000;
		Bossprojdest[i].h = 50;
		Bossprojdest[i].w = 80;
	}

	Backcoord.x = 0;
	Backcoord.y = 0;
	Backcoord.w = SCREEN_WIDTH;
	Backcoord.h = SCREEN_HEIGHT;

	Backcoord2.x = 0;
	Backcoord2.y = 0;
	Backcoord2.w = SCREEN_WIDTH;
	Backcoord2.h = SCREEN_HEIGHT;

	Backcoordbis.x = SCREEN_WIDTH;
	Backcoordbis.y = 0;
	Backcoordbis.w = SCREEN_WIDTH;
	Backcoordbis.h = SCREEN_HEIGHT;

	Backcoordbis2.x = SCREEN_WIDTH;
	Backcoordbis2.y = 0;
	Backcoordbis2.w = SCREEN_WIDTH;
	Backcoordbis2.h = SCREEN_HEIGHT;


	GOsrc.x = 0;
	GOsrc.y = 0;
	GOsrc.h = 480;
	GOsrc.w = 350;

	GOdest.w = 580;
	GOdest.h = 350;
	GOdest.x = SCREEN_WIDTH / 2 - GOdest.w / 2 - 60;
	GOdest.y = SCREEN_HEIGHT / 2 - GOdest.h / 2;

	Windest.w = 580;
	Windest.h = 350;
	Windest.x = SCREEN_WIDTH / 2 - Windest.w / 2 - 60;
	Windest.y = SCREEN_HEIGHT / 2 - Windest.h / 2;

	HPsrc.x = 0;
	HPsrc.y = 0;
	HPsrc.h = 413;
	HPsrc.w = 549;

	for (i = 0; i < 5; i++) {
		HPdest[i].x = 0 + p;
		HPdest[i].y = 30;
		HPdest[i].h = 50;
		HPdest[i].w = 70;
		p += 50;
	}
	p = 0;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = 580;
	SrcR.h = 793;

	DestR.x = 50;
	DestR.y = SCREEN_HEIGHT/2;
	DestR.w = 150;
	DestR.h = 150;

	SrcProj.x = 0;
	SrcProj.y = 0;
	SrcProj.w = 410;
	SrcProj.h = 250;

	for (i = 0; i < BULLETNUM; i++) {
		DestProj[i].x = 2000;
		DestProj[i].y = 2000;
		DestProj[i].w = 75;
		DestProj[i].h = 45;
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


	gWindow = SDL_CreateWindow("My Awesome Game :D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Main_Renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	//Event handler
	SDL_Event event;

	//crea textura fondo
	Loading_Surf = IMG_Load("Assets/backlayer0.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background0 = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/backlayer1.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background1 = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);
	Loading_Surf = IMG_Load("Assets/backlayer1.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background1bis = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/backlayer2.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background2 = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/backlayer2.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Background2bis = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/boss.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Boss = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/bala2.png");
	if (!Loading_Surf) {
		quit = true;
	}
	for (i=0;i< BOSSPROJNUM;i++){
	projboss[i] = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
}
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/player.png");
	if (!Loading_Surf) {
		quit = true;
	}


	Image = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/gameover.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Gameover = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);

	Loading_Surf = IMG_Load("Assets/win.png");
	if (!Loading_Surf) {
		quit = true;
	}
	Win = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	SDL_FreeSurface(Loading_Surf);


	Loading_Surf = IMG_Load("Assets/life.png");
	if (!Loading_Surf) {
		quit = true;
	}
	for (i = 0; i < 5; i++) {
		Health[i] = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
	}
	SDL_FreeSurface(Loading_Surf);

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
	hit = Mix_LoadMUS("Assets/hit.wav");
	if (!hit) {
		quit = true;
	}
	hit2 = Mix_LoadMUS("Assets/hit2.wav");
	if (!hit2) {
		quit = true;
	}
	/*
	defeat = Mix_LoadMUS("Assets/hit.wav");
	if (!defeat) {
		quit = true;
	}*/

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
		
	if(hp > 0 && bosshp > 0){

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

		showship = true;
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

		Backcoord.x--;
		Backcoordbis.x--;
		Backcoord2.x -= 5;
		Backcoordbis2.x -= 5;
		if (Backcoord.x < 0 - SCREEN_WIDTH) {
			Backcoord.x = SCREEN_WIDTH;
		}
		if (Backcoord2.x < 0 - SCREEN_WIDTH) {
			Backcoord2.x = SCREEN_WIDTH;
		}
		if (Backcoordbis.x < 0 - SCREEN_WIDTH) {
			Backcoordbis.x = SCREEN_WIDTH;
		}
		
		if (Backcoordbis2.x < 0 - SCREEN_WIDTH) {
			Backcoordbis2.x = SCREEN_WIDTH;
		}
		//Linea de enemigos 1
		respawntimer1++;
		if (respawntimer1 > 200) {
			respawn = true;
		}
		cont2++;
		if (respawn == true) {
			if (generatenum == true) {
				randomy = 300 + rand() % SCREEN_HEIGHT - 600;
				generatenum = false;
			}
			if (cont2 > ENEMYDELAY) {
				cont2 = 0;
				DestEnem[p].x = 1280;
				DestEnem[p].y = randomy;
				p++;
				if (p == ENEMYNUM - 1) {
					p = 0;
					respawn = false;
					respawntimer1 = 0;
					generatenum = true;
				}
			}
		}

		for (i = 0; i < ENEMYNUM; i++) {
			DestEnem[i].x -= 8;

			if (DestEnem[i].x < 1300) {
				if (conty[i] <= 5) {
					movy[i]++;
				}
				if (conty[i] >= 30) {
					movy[i]++;
				}
				if (movy[i] % 2 != 0) {
					conty[i]--;
					DestEnem[i].y -= 3;
				}
				else {
					conty[i]++;
					DestEnem[i].y += 3;
				}
			}
		}
		//Linea de enemigos 2

		respawntimer2++;
		if (respawntimer2 > 150) {
			respawn2 = true;
		}
		cont3++;
		if (respawn2 == true) {
			if (generatenum == true) {
				randomy = 300 + rand() % SCREEN_HEIGHT - 600;
				generatenum = false;
			}
			if (cont3 > ENEMYDELAY) {
				cont3 = 0;
				DestEnem2[d].x = 1280;
				DestEnem2[d].y = 300;
				d++;
				if (d == ENEMYNUM) {
					d = 0;
					respawn2 = false;
					respawntimer2 = false;
					generatenum = true;
					round++;
				}
			}
		}

		for (i = 0; i < ENEMYNUM; i++) {
			DestEnem2[i].x -= 8;

			if (DestEnem2[i].x < 1300) {
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
		
		if (Bossdest.x > SCREEN_WIDTH -500 && round >2 ) {
			Bossdest.x-=4;
			 bossphase = true;
		}	
		if (bossphase == true) {
			cont4++;
			showboss = true;
			if (cont4 > BOSSDELAY && Bossdest.x <= SCREEN_WIDTH - 500) {

				Bossprojdest[s].x = Bossdest.x+100;
				Bossprojdest[s].y = 400;
					cont4 = 0;
					if (s==0){
						for (i = 0; i < BOSSPROJNUM; i++) {
							y[i] = rand() % 15;
							yneg[i] = rand() % 15;
					}
					}
					s++;
					if (s == BOSSPROJNUM) {
						s = 0;
					}
			}
			
			for (i = 0; i < BOSSPROJNUM; i++) {
				Bossprojdest[i].x -=6;
				Bossprojdest[i].y += y[i];
				Bossprojdest[i].y -= yneg[i];
			}
		}
		for (i = 0; i < ENEMYNUM; i++) {
			for (a = 0; a < BULLETNUM; a++) {
				if (DestProj[a].y > DestEnem[i].y && DestProj[a].y < DestEnem[i].y + 90 && DestProj[a].x > DestEnem[i].x && DestProj[a].x < DestEnem[i].x + 125) {
					DestEnem[i].y += 5000;
					DestProj[a].y += 6000;
					Mix_PlayMusic(hit2, 0);

				}
			}
		}
		for (i = 0; i < ENEMYNUM; i++) {
			for (a = 0; a < BULLETNUM; a++) {
				if (DestProj[a].y > DestEnem2[i].y && DestProj[a].y < DestEnem2[i].y + 90 && DestProj[a].x > DestEnem2[i].x && DestProj[a].x < DestEnem2[i].x + 125) {
					DestEnem2[i].y += 5000;
					DestProj[a].y += 6000;
					Mix_PlayMusic(hit2, 0);
				}
			}
		}

		for (i = 0; i < ENEMYNUM; i++) {
			if (DestEnem2[i].x > DestR.x && DestEnem2[i].x < DestR.x +120 && DestEnem2[i].y > DestR.y + 30 && DestEnem2[i].y < DestR.y + 120) {
				DestEnem2[i].y += 5000;
				Mix_PlayMusic(hit, 0);
				hp--;
				showship = false;
			}
			if (DestEnem[i].x > DestR.x && DestEnem[i].x < DestR.x + 120 && DestEnem[i].y > DestR.y +30 && DestEnem[i].y < DestR.y + 120) {
				DestEnem[i].y += 5000;
				Mix_PlayMusic(hit, 0);
				hp--;
				showship = false;
			}
		}
		for (i = 0; i < BOSSPROJNUM; i++) {
			if (Bossprojdest[i].x > DestR.x && Bossprojdest[i].x < DestR.x + 100 && Bossprojdest[i].y > DestR.y +50 && Bossprojdest[i].y < DestR.y + 100) {
				Bossprojdest[i].y += 5000;
				Mix_PlayMusic(hit, 0);
				hp--;
				showship = false;
			}
		}

		for (i = 0; i < BULLETNUM; i++) {
			
				if (DestProj[i].x >= Bossdest.x && DestProj[i].x <= Bossdest.x +50 && Bossdest.x <= SCREEN_WIDTH - 500) {
					DestProj[a].y += 6000;
					Mix_PlayMusic(hit2, 0);
					showboss = false;
					bosshp--;
				
			}
		}
	}
		SDL_RenderCopy(Main_Renderer, Background0, NULL, NULL);
		SDL_RenderCopy(Main_Renderer, Background1, NULL, &Backcoord);
		SDL_RenderCopy(Main_Renderer, Background1, NULL, &Backcoordbis);
		SDL_RenderCopy(Main_Renderer, Background2, NULL, &Backcoord2);
		SDL_RenderCopy(Main_Renderer, Background2, NULL, &Backcoordbis2);
		if (showboss == true) { SDL_RenderCopy(Main_Renderer, Boss, NULL, &Bossdest); }
		for (i=0;i< BOSSPROJNUM;i++){
		SDL_RenderCopy(Main_Renderer, projboss[i], NULL, &Bossprojdest[i]);}
		if (showship == true) { SDL_RenderCopy(Main_Renderer, Image, &SrcR, &DestR); }

		for (i = 0; i < BULLETNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Bullet[i], &SrcProj, &DestProj[i]);
		}
		for (i = 0; i < ENEMYNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Enemy[i], &SrcEnem, &DestEnem[i]);
		}
		for (i = 0; i < ENEMYNUM; i++) {
			SDL_RenderCopy(Main_Renderer, Enemy2[i], &SrcEnem, &DestEnem2[i]);
		}
		for (i = 0; i < hp; i++) {
			SDL_RenderCopy(Main_Renderer, Health[i], &HPsrc, &HPdest[i]);
		}
		if (hp <= 0) {
			SDL_RenderCopy(Main_Renderer, Gameover, &GOsrc, &GOdest);		
		}
		if (hp == 0) {
			Mix_HaltChannel(-1);
			hp = -1;
		}
		if (bosshp <= 0) {
			SDL_RenderCopy(Main_Renderer, Win, NULL, &Windest);
		}
		SDL_RenderPresent(Main_Renderer);
	}


	//Free resources and close SDL
	Mix_FreeChunk(backMus);
	Mix_FreeMusic(shootSE);
	Mix_FreeMusic(hit);
	Mix_FreeMusic(hit2);

	for (i = 0; i < ENEMYNUM; i++) {
		SDL_DestroyTexture(Enemy[i]);
	}
	for (i = 0; i < BULLETNUM; i++) {
		SDL_DestroyTexture(Bullet[i]);
	}
	for (i = 0; i < 5; i++) {
		SDL_DestroyTexture(Health[i]);
	}
	SDL_DestroyTexture(Boss);
	SDL_DestroyTexture(Image);
	SDL_DestroyTexture(Gameover);
	SDL_DestroyTexture(Background2bis);
	SDL_DestroyTexture(Background1bis);
	SDL_DestroyTexture(Background2);
	SDL_DestroyTexture(Background1);
	SDL_DestroyTexture(Background0);
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

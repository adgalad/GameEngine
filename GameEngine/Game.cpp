//
//  Game.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/11/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Game.h"
#include "Camera.h"

Game::Game(int width, int height)
{
	this->event         = new SDL_Event();
	this->player        = NULL;
	this->background	= NULL;
	this->renderer		= NULL;
	this->camera		= NULL;
	this->maxFPS        = 24;
	this->sideScrolling = false;
	this->width			= width;
	this->height		= height;
	this->X				= 0;
	this->Y				= 0;
}

void Game::setMaxFPS(int FPS)
{
	this->maxFPS = 1000/FPS;
}
bool Game::init()
{
	/* Init SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		fprintf(stderr, "ERROR Game::init() Couldn't initialize SDL\n\t%s\n",SDL_GetError());
		return false;
	}
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	this->width  = dm.w/1.5;
	this->height = dm.h/1.5;
	if (NULL==( mainWindow = SDL_CreateWindow("Game Engine - SDL",
											   SDL_WINDOWPOS_UNDEFINED,
											   SDL_WINDOWPOS_UNDEFINED,
											   this->width, this->height,
											   SDL_WINDOW_OPENGL |
											   SDL_WINDOW_RESIZABLE))
		)
	{
		fprintf(stderr, "ERROR Game::init() Main Window is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	
	this->renderer = SDL_CreateRenderer(this->mainWindow, -1,
										SDL_RENDERER_TARGETTEXTURE |
										SDL_RENDERER_ACCELERATED );
	if (this->renderer == NULL)
	{
		
		fprintf(stderr,"ERROR Game::init() Renderer assigned is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	
	this->camera = new Camera();

	/*Enable Music mixer */
//	Mix_Music *moveSound;
//	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
//	moveSound = Mix_LoadMUS("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Chess/Chess/Resource/moveSound.wav");
//	if (moveSound == NULL)
//	{
//		printf("Couldn't load sound\n");
//		return false;
//	}
	
	
	if (TTF_Init() != 0){
		fprintf(stderr,"ERROR Game::init() Couldn't load TTF\n\t%s\n",SDL_GetError());
		return false;
	}
	
	this->running = true;
	
	return true;
}

bool Game::run()
{
	this->updateGameXYPos();
	this->setEnvironmentValues( &this->width, &this->height,
							    &this->X, &this->Y
							);
	while (this->running) {
		
		if (!this->eventHandler())
		{
			return false;
		}
		this->updateGameXYPos();
		this->loop();
		this->render();
		
		SDL_Delay(this->maxFPS);
	}
	return true;
}

void Game::addPlayer(Player *player)
{
	if (player == NULL)
	{
		fprintf(stderr, "WARNING Game::addPlayer(Player*) player assigned is NULL pointer");
		return;
	}
	this->player = std::unique_ptr<Player>(player);
	if (this->background != NULL)
	{
		this->player->setBackground(this->background.get());
	}
	else
	{
		fprintf(stderr, "WARNING Game::addPlayer(Player*): this->background is NULL pointer");
	}
}
void Game::addBackground(Background *bg)
{
	this->background = std::unique_ptr<Background>(bg);
}

void Game::setRenderer(SDL_Renderer *renderer)
{
	this->renderer = renderer;
}

bool Game::render()
{
	if ( this->background->render(this->renderer) and
		 this->player->render(this->renderer)
		)
	{
		SDL_RenderPresent(this->renderer);
		SDL_RenderClear(this->renderer);
		return true;
	}
	this->running = false;
	return false;
}



bool Game::eventHandler()
{
	Uint8 *keyStates = (Uint8*)	SDL_GetKeyboardState(NULL);
	if(SDL_PollEvent(this->event))
	{
		switch (this->event->type) {
			case SDL_QUIT:
				this->running = false;
				break;
			case SDL_KEYDOWN:
				if (keyStates[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
				{
					this->running = false;
				}
				if (keyStates[SDL_GetScancodeFromKey(SDLK_m)])
				{
					this->player->X = 500;
					this->player->Y = 300;
				}
				switch (this->event->key.keysym.sym) {
					case SDLK_n:
						this->running = false;
						break;

					default:
						break;
				}
			default:

				break;
		}
	}
	if(this->player != NULL)
	{
		//		printf("(%d %d)   (%d %d)\n",player->X, player->Y, this->player->X - this->width/2, this->player->Y - this->height/2);
		this->player->eventHandler(event, keyStates,this->renderer);
	}
	return true;
}
bool Game::loop()
{
	this->background->loop();
	this->player->movement();
	this->player->collision();
	return false;
}

void Game::release()
{
	SDL_DestroyWindow(this->mainWindow);

	free(this->event);
	this->player->release();
	this->player.release();
	this->background->release();
	this->background.release();
	GameParameter::_textures.release();
}

void Game::updateGameXYPos()
{
	int w,h;
	SDL_GetWindowSize(this->mainWindow, &w, &h);
	this->width = w;
	this->height = h;
	if (this->player != NULL)
	{
		this->X = this->player->X - this->width/2  + GameParameter::_cameraX;
		this->Y = this->player->Y - this->height/2 + GameParameter::_cameraY;
	}
	else
	{
		this->X = this->Y = 0;
	}
}

void Game::setEnvironmentValues( int *winWidth, int *winHeight,
								 int *cameraX,  int *cameraY
							)
{
	this->background->setBackgroundEnviromentValues( winWidth, winHeight,
													  cameraX,  cameraY
													 );
	this->player->setEnvironmentValues(winWidth, winHeight, cameraX, cameraY);
}


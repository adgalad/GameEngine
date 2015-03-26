//
//  Game.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/11/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Game.h"
#include "Camera.h"

Game::Game()
{
	this->event         = new SDL_Event();
	this->player        = std::unique_ptr<Player>(new Player());
	this->background	= std::unique_ptr<Background>(new Background());
	this->maxFPS        = 24;
	this->sideScrolling = false;
	this->width			= 628;
	this->height		= 628;
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
		return false;
	}
	/*
				Uso futuro
		const SDL_VideoInfo *VideoInfo;
		VideoInfo = SDL_GetVideoInfo();
		int h=VideoInfo->current_h;
		int w=VideoInfo->current_w;
	*/

	/* Set Video Mode */
	if (NULL==( mainSurface = SDL_SetVideoMode(this->width,this->height, 32,
											   SDL_HWSURFACE|SDL_DOUBLEBUF)
				                              )
		)
	{
		return false;
	}

	canvas = new SDL_Surface();

	


	/* Set Unicode Translate */
	SDL_EnableUNICODE(1);
	
	/* Enable Key Repeat */
	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
	
	/*Enable Music mixer */
//	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
//	moveSound = Mix_LoadMUS("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Chess/Chess/Resource/moveSound.wav");
//	if (moveSound == NULL)
//	{
//		printf("Couldn't load sound\n");
//		return false;
//	}
	if (TTF_Init() != 0){
		printf("Couldn't load TTF\n");
		return false;
	}
	
	this->running = true;
	
	return true;
}

bool Game::run()
{
	while (this->running) {
		this->render();
		this->loop();

		if (SDL_PollEvent(this->event))
		{
			if (!this->eventHandler())
			{
				return false;
			}
		}
		else{

			if (!this->keyHandler())
			{
				return false;
			}
		}
		SDL_Delay(this->maxFPS);
	}
	return true;
}

void Game::addPlayer(Player *player)
{
	this->player = std::unique_ptr<Player>(player);
	if (this->background != NULL)
	{
		this->player->setBackground(this->background.get());
	}
}
void Game::addBackground(Background *bg)
{
	this->background = std::unique_ptr<Background>(bg);
	Uint32 rmask, gmask, bmask, amask;
	
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	 on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	
	this->canvas = SDL_CreateRGBSurface(
										0,
										this->background->surface->w,
										this->background->surface->h,
										32,
										amask,
										bmask,
										gmask,
										rmask
								   );
}
bool Game::render()
{
	this->background->render(this->canvas);
	this->player->render(this->canvas);
	
	this->camera->render(this->canvas,
						 this->mainSurface,
						 this->player->X,
						 this->player->Y,
						 this->mainSurface->w,
 						 this->mainSurface->h);
	
	SDL_Flip(this->mainSurface);
	SDL_FillRect(this->mainSurface, NULL, 0x000000);
	return true;
}

bool Game::keyHandler()
{
	Uint8 *keystates = SDL_GetKeyState( NULL );

	if (keystates[SDLK_ESCAPE])
	{
		this->running = false;
	}
	if(keystates[SDLK_RIGHT])
	{
		this->player->moveRight(this->event);
	}
	else if(keystates[SDLK_LEFT])
	{
		this->player->moveLeft(this->event);
	}
	else
	{
		this->player->stop();
	}
	
	if(keystates[SDLK_UP] || keystates[SDLK_SPACE])
	{
		this->player->jump(this->event);
	}
	else
	{
		switch (this->event->key.keysym.unicode) {
			case 'n':
				this->running = false;
				break;
			default:
				break;
		}
	}
	return true;
}

bool Game::eventHandler()
{

	switch (this->event->type) {
		case SDL_QUIT:
			this->running = false;
			break;

		default:
			this->keyHandler();
			break;
	}
	return true;
}
bool Game::loop()
{
	return true;
}

void Game::release()
{
	SDL_FreeSurface(this->mainSurface);
	SDL_FreeSurface(this->canvas);
	free(this->event);
	this->player->release();
	this->player.release();
	this->background->release();
	this->background.release();
}


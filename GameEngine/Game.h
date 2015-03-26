//
//  Game.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/11/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Game__
#define __GameEngine__Game__

#include <memory.h>
#include <stdio.h>
#include "Background.h"
#include "Player.h"

class Camera;

class Game
{
protected:
	SDL_Event               *event;
	Camera					*camera;
	bool					sideScrolling;
	bool                    running;
	int                     maxFPS;
	
public:
	int width;
	int height;
	std::unique_ptr<Player>      player;
	std::unique_ptr<Background>  background;
	SDL_Surface *mainSurface, *canvas;

public:
	Game();
	
	void setMaxFPS(int FPS);
	
	bool init();
	
	bool run();
	
	void addPlayer(Player *player);
	
	void addBackground(Background *bg);
	
	bool render();
	
	bool keyHandler();
	
	bool eventHandler();
	
	bool loop();
	
	void release();

};

#endif /* defined(__GameEngine__Game__) */

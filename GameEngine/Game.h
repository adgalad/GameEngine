//
//  Game.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/11/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Game__
#define __GameEngine__Game__


#include "SDLHeader.h"
#include <stdio.h>
#include "Background.h"
#include "Player.h"


class Camera;


#define DEFAULT_WINDOW_SIZE 628

class Game
{
protected:
	SDL_Event*		event;
	Camera*			camera;
	bool			sideScrolling;
	bool			running;
	int				maxFPS;
	
public:
	SDL_Renderer*	renderer;
	int				width, height;
	int				X,Y;
	Player*			player;
	Background*		background;
	vector<Entity*> entities;
	SDL_Window*		mainWindow;
	SDL_Texture*	canvas;

public:
	Game(int width  = DEFAULT_WINDOW_SIZE,
		 int height = DEFAULT_WINDOW_SIZE
		);
	
	~Game();
	
	void setMaxFPS(int FPS);
	
	bool init();
	
	bool run();
	
	void addPlayer(Player *player);
	
	void addBackground(Background *bg);
	
	void setRenderer(SDL_Renderer *renderer);
	
	bool render();
	
	bool eventHandler();
	
	bool loop();
	
	void release();
	
private:
	
	void updateGameXYPos();
	
	void setEnvironmentValues(int *winWidth, int *winHeight,
							  int *cameraX,  int *cameraY
							);

};

#endif /* defined(__GameEngine__Game__) */

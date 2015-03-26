//
//  Player.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Player__
#define __GameEngine__Player__

#include <stdio.h>
#include "Entity.h"

class Player : public Entity
{
	
public:
	Player();
	
	void moveLeft(SDL_Event *event);
	
	void moveRight(SDL_Event *event);
	
	void moveUp(SDL_Event *event);
	
	void moveDown(SDL_Event *event);
	
	void jump(SDL_Event *event);
	
	void stop();
	
	void release();
};
#endif /* defined(__GameEngine__Player__) */

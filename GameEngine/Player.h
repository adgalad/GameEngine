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
#include "SDLHeader.h"
#include "Entity.h"

class Player : public Entity
{
	
public:
	Player();
	
	/* Movement Methods */
	void moveLeft(Uint8 *keyStatus);
	
	void moveRight(Uint8 *keyStatus);
	
	void moveUp(Uint8 *keyStatus);
	
	void moveDown(Uint8 *keyStatus);
	
	void jump(Uint8 *keyStatus);
	
	void stop();
	
	/* Control Methods */
	void eventHandler(SDL_Event *event,Uint8 *keyStates);
	
	void release();
};
#endif /* defined(__GameEngine__Player__) */

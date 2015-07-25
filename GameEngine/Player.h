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
#include "TemporalEntity.h"

class PlayerAction
{
public:
	int spritePosition;
	uint key;
};


class Player : public Entity
{
	friend class Game;
protected:
	vector<PlayerAction*> actions;
	
	
public:
	
	Player();
	
	int keyUp;
	int keyDown;
	int keyRight;
	int keyLeft;
	int keyStanding;
	
	bool addAction(int position, uint key);
	
	/* Movement Methods */
	void moveLeft(Uint8 *keyStatus);
	
	void moveRight(Uint8 *keyStatus);
	
	void moveUp(Uint8 *keyStatus);
	
	void moveDown(Uint8 *keyStatus);
	
	void jump(Uint8 *keyStatus);
	
	void stop();
	
	/* Control Methods */
	void eventHandler(SDL_Event *event,Uint8 *keyStates,SDL_Renderer *renderer);
	
	void release();
};
#endif /* defined(__GameEngine__Player__) */

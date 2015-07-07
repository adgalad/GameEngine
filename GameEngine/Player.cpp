//
//  Player.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Player.h"

Player::Player()
{
	Entity::Entity();
	this->movable = true;
}


void Player::moveLeft(Uint8 *keyStates)
{
	if (this->velocityX > 0) this->velocityX = 0;
	
	if (this->velocityX > -_maxWalkVelocityX)
	{
		this->velocityX -= _maxWalkVelocityX/4;
	}
	
	if(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)] and
	   this->velocityX > -2*_maxSprintVelocityX)
	{
		this->velocityX -= _maxWalkVelocityX/2;
	}
	else if (!(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)]) and
			   this->velocityX < -_maxWalkVelocityX)
	{
		this->velocityX += _maxWalkVelocityX/2;
	}
	
	this->currentFrameY = 3;
	this->direction = 1;
	this->animated = true;
}

void Player::moveRight(Uint8 *keyStates)
{
	if (this->velocityX < 0) this->velocityX = 0;
	
	if (this->velocityX < _maxWalkVelocityX)
	{
		this->velocityX += _maxWalkVelocityX/4;
	}
	
	if (keyStates[SDL_GetScancodeFromKey(SDLK_LALT)] and
	   this->velocityX < 2*_maxSprintVelocityX)
	{
		this->velocityX += _maxWalkVelocityX/2;
	}
	else if (!(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)]) and
			   this->velocityX > _maxWalkVelocityX)
	{
		this->velocityX -= _maxWalkVelocityX/2;
	}
	
	this->currentFrameY = 3;
	this->direction = 0;
	this->animated = true;
}

//void Player::moveUp();
//
//void Player::moveDown();

void Player::jump(Uint8 *keyStates)
{
	if (this->velocityY == 0)
	{
		this->velocityY = this->jumpVelocity;
	}
	this->currentFrameY = 8;
}

void Player::stop()
{

	this->stoped = true;
	if (this->velocityX == 0 && !this->standingAnimated)
	{
		this->currentFrameY = 0;
		this->setAnimated(false);
	}
	this->currentFrameY = 1;
}

void Player::eventHandler(SDL_Event *event, Uint8 *keyStates)
{
	
	if(keyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] and
	   !keyStates[SDL_GetScancodeFromKey(SDLK_LEFT)])
	{
		this->stoped = false;
		this->moveRight(keyStates);
	}
	else if(keyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] and
			!keyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)])
	{
		this->stoped = false;
		this->moveLeft(keyStates);
	}
	else
	{
		if (this->velocityY == 0)
			this->stop();
	}
	
	if( keyStates[SDL_GetScancodeFromKey(SDLK_UP)] or
	    keyStates[SDL_GetScancodeFromKey(SDLK_SPACE)]
	   )
	{
		this->jump(keyStates);
	}
	if (keyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
		this->currentFrameY = 9;
	}
	
	switch (event->key.keysym.sym)
	{
		case SDLK_m:
			this->X = 300;
			this->Y = 600;
			break;
		default:
			break;
	}
}


void Player::release()
{
	Object::release();
}
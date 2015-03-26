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
}


void Player::moveLeft(SDL_Event *event)
{
	if (this->velocityX > 0) this->velocityX = 0;
	if(this->velocityX > -8)
	{
		this->velocityX -= 4;
	}
	if(event->key.keysym.mod & KMOD_ALT && this->velocityX > -32)
	{
		this->velocityX -= 4;
	}
	else if (!(event->key.keysym.mod & KMOD_ALT) && this->velocityX < -8)
	{
		this->velocityX = -8;
	}
	this->currentFrameX = 1;
	this->animated = true;
}

void Player::moveRight(SDL_Event *event)
{
	if (this->velocityX < 0) this->velocityX = 0;
	if(this->velocityX < 8)
	{
		this->velocityX += 4;
	}
	if(event->key.keysym.mod & KMOD_ALT && this->velocityX < 32)
	{
		this->velocityX += this->velocityX;
	}
	else if (!(event->key.keysym.mod & KMOD_ALT) && this->velocityX > 8)
	{
		this->velocityX = 8;
	}
	this->currentFrameX = 0;
	this->animated = true;
}

//void Player::moveUp();
//
//void Player::moveDown();

void Player::jump(SDL_Event *event)
{
	if (this->velocityY == 0)
	{
		this->velocityY = this->jumpAcceleration;
	}
}

void Player::stop()
{
	if (this->X != 0)
	{
		this->velocityX = 0;
	}
	this->currentFrameY = 0;
	this->setAnimated(false);
}

void Player::release()
{
	Object::release();
}
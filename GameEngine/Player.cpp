//
//  Player.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Player.h"
#include "Background.h"

Player::Player()
{
	this->keyUp			= SDLK_UP;
	this->keyDown		= SDLK_DOWN;
	this->keyRight		= SDLK_RIGHT;
	this->keyLeft		= SDLK_LEFT;

	this->movable		= true;
}

bool Player::addAction(int position, uint key)
{
	for (int i = 0 ; i < this->actions.size(); i++)
	{
		if (this->actions[i]->spritePosition == position or
			this->actions[i]->key            == key)
		{
			fprintf(stderr,"WARNING Player::addAction(int, uint): Trying to add an action key that already exists\n.");
			return false;
		}
	}
	PlayerAction *newAction   = new PlayerAction;
	newAction->key            = key;
	newAction->spritePosition = position;
	this->actions.push_back(newAction);
	return true;
}

void Player::moveLeft(Uint8 *keyStates)
{
	if (this->velocityX > 0) this->velocityX = 0;
	
	if (this->velocityX > -GameParameter::_maxWalkVelocityX)
	{
		this->velocityX -= GameParameter::_maxWalkVelocityX/4;
	}
	
	if(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)] and
	   this->velocityX > -2*GameParameter::_maxSprintVelocityX)
	{
		this->velocityX -= GameParameter::_maxWalkVelocityX/2;
	}
	else if (!(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)]) and
			   this->velocityX < -GameParameter::_maxWalkVelocityX)
	{
		this->velocityX += GameParameter::_maxWalkVelocityX/2;
	}
	
	if (this->verticalAnimation)
	{
		this->currentFrameX = this->posLeft;
	}
	else
	{
		this->currentFrameY = this->posLeft;
	}
	this->direction = 1;
	this->animated = true;
}

void Player::moveRight(Uint8 *keyStates)
{
	if (this->velocityX < 0) this->velocityX = 0;
	
	if (this->velocityX < GameParameter::_maxWalkVelocityX)
	{
		this->velocityX += GameParameter::_maxWalkVelocityX/4;
	}

	if (keyStates[SDL_GetScancodeFromKey(SDLK_LALT)] and
	   this->velocityX < 2*GameParameter::_maxSprintVelocityX)
	{
		this->velocityX += GameParameter::_maxWalkVelocityX/2;
	}
	else if (!(keyStates[SDL_GetScancodeFromKey(SDLK_LALT)]) and
			   this->velocityX > GameParameter::_maxWalkVelocityX)
	{
		this->velocityX -= GameParameter::_maxWalkVelocityX/2;
	}
	if (this->verticalAnimation)
		this->currentFrameX = this->posRight;
	else
		this->currentFrameY = this->posRight;
	this->direction = 0;
	this->animated = true;
}

//void Player::moveUp();
//
void Player::moveDown(Uint8 *keyStates)
{
	if(this->velocityY == 0)
	{
		if (this->verticalAnimation)
			this->currentFrameX = this->posDown;
		else
			this->currentFrameY = this->posDown;
	}
}

void Player::jump(Uint8 *keyStates)
{
	if (this->velocityY == 0)
	{
		this->velocityY = this->jumpVelocity;
	}
	if (this->verticalAnimation)
		this->currentFrameX = this->posUp;
	else
		this->currentFrameY = this->posUp;
}

void Player::stop()
{

	this->stoped = true;
	if (this->velocityX == 0 && !this->standingAnimated)
	{
		this->currentFrameY = 0;
		this->setAnimated(false);
	}
	if (this->verticalAnimation)
		this->currentFrameX = this->posStanding;
	else
		this->currentFrameY = this->posStanding;


}

void Player::eventHandler(SDL_Event *event, Uint8 *keyStates, SDL_Renderer *renderer)
{
	

	for (int i = 0; i < this->actions.size(); i++)
	{
		if(keyStates[SDL_GetScancodeFromKey(this->actions[i]->key)])
		{
			
			if (this->verticalAnimation and
				this->currentFrameX != this->actions[i]->spritePosition)
			{
				this->previousSpritePosition = this->currentFrameX;
				this->currentFrameX = this->actions[i]->spritePosition;
				this->currentFrameY = 0;
			}
			else if (this->currentFrameY != this->actions[i]->spritePosition)
			{
				this->previousSpritePosition = this->currentFrameY;
				this->currentFrameY = this->actions[i]->spritePosition;
				this->currentFrameX = 0;
			}
			this->specialAction = this->spriteMap[
										this->actions[i]->spritePosition
												];

			
			if(actions[i]->key == 'c')
			{
				TemporalEntity *e = new TemporalEntity;
				e->animated = true;
				e->loadTexture(GameParameter::_textures.getTextureByName("sprite")->SDLtexture);
				e->setAnimateValues(8, 1);
				e->X = ( this->direction == RIGHT_DIR ? 1:-1)*200 + this->X;
				e->Y = Y;
				e->velocityX = 10;
				e->movable = true;
				e->setDisappearOnColission(true);
				e->gravity = GameParameter::_gravtiyAcceleration;
				e->setTime(3000);
				e->setEnvironmentValues(winWidth, winHeight,		   cameraX, cameraY);
				e->verticalAnimation = false;
				printf("%d\n",e->id);
				
				background->addTemporalEntity(e);
			}
			
			return;
		}
	}
	
	if(keyStates[SDL_GetScancodeFromKey(this->keyRight)] and
	   !keyStates[SDL_GetScancodeFromKey(this->keyLeft)])
	{
		this->stoped = false;
		this->moveRight(keyStates);
	}
	else if(keyStates[SDL_GetScancodeFromKey(this->keyLeft)] and
			!keyStates[SDL_GetScancodeFromKey(this->keyRight)])
	{
		this->stoped = false;
		this->moveLeft(keyStates);
	}
	else
	{
		if (this->velocityY == 0 and !this->specialAction)
			this->stop();
	}
	
	if( keyStates[SDL_GetScancodeFromKey(this->keyUp)] or
	   keyStates[SDL_GetScancodeFromKey(SDLK_SPACE)]
	   )
	{
		this->jump(keyStates);
	}
	if (keyStates[SDL_GetScancodeFromKey(this->keyDown)]) {
		this->moveDown(keyStates);
	}
}


void Player::release()
{
	
}
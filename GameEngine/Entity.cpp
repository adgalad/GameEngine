//
//  Entity.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Entity.h"


int globalID = 1;

Entity::Entity()
{
	Object::Object();
	
	this->active			= true;
	this->movable			= false;
	this->iscollision		= true;
	this->_id				= globalID++;
	this->direction			= 1;
	this->velocityX			= 0.0;
	this->velocityY			= 0.0;
	this->jumpAcceleration	= -40.0;
	this->gravity			= 6.0;
}

Entity::Entity(SDL_Surface *surface)
{
	Object::Object();
	
	this->surface   = surface;
	if (this->surface != NULL)
	{
		this->width		= this->surface->w;
		this->height	= this->surface->h;
		this->active    = true;
		this->movable   = false;
		this->iscollision = true;
		this->_id       = globalID++;
		this->direction = 1;
		this->velocityX    = 0.0;
		this->velocityY    = 0.0;
		this->gravity   = 4.9;
	}
	else
	{
		fprintf(stderr, "Entity::Entity(SDL_Surface *): Surface assigned is NULL pointer\n");
	}
}

void Entity::setBackground(Background *bg)
{
	this->background = std::unique_ptr<Background>(bg);
}
void Entity::moveTo(int x, int y)
{
	this->X = x;
	this->Y = y;
}

bool Entity::collision()
{
	bool collision = false;
	for(int i = 0 ; i < this->background->entities.size(); i++)
	{

		if(!( this->background->entities[i] == NULL           ||
			   this->_id == this->background->entities[i]->_id ||
			  !this->background->entities[i]->iscollision
			 )
		)
		{
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;
			
			leftA   = this->X;
			topA    = this->Y;
			rightA  = this->width  + leftA;
			bottomA = this->height + topA;
			
			leftB   = this->background->entities[i]->X;
			topB    = this->background->entities[i]->Y;
			rightB  = this->background->entities[i]->width  + leftB;
			bottomB = this->background->entities[i]->height + topB;
			if((bottomA > topB  && topA  < bottomB &&
				rightA  > leftB && leftA < rightB
			   ))
			{
				float tempvelocityX = this->velocityX;
				if (tempvelocityX < 0) tempvelocityX = -tempvelocityX;
				
				float tempvelocityY = this->velocityY;
				if (tempvelocityY < 0) tempvelocityY = -tempvelocityY;
				//	the right side of square 1 collided
				//	with the left side of square 2
				if (leftA < leftB)
				{
					if (rightA  - leftB <= tempvelocityX)
					{
						this->X = leftB - this->width ;
						this->velocityX = 0;
					}

				}
				//	the left side of square 1 collided
				//	with the right side of square 2
				else if (leftA > leftB)
				{
					if (rightB - this->X <= tempvelocityX)
					{
						this->X = rightB;
						this->velocityX = 0;
					}
				}
				//	the bottom side of square 1 collided
				//	with the top side of square 2
				if (topA < topB)
				{
					if (bottomA - topB <= tempvelocityY)
					{
						this->Y = topB - this->height ;
						this->velocityY = 0;
					}
				}
				//	the top side of square 1 collided
				//	with the bottom side of square 2
				else if ( topA > topB)
				{
					if (bottomB - this->Y <= tempvelocityY)
					{
						this->Y = bottomB;
						this->velocityY = 0.1;
					}
				}
				collision = true;
			}
		}
	}
	return collision;
}

void Entity::movement()
{

	if(this->movable)
	{

		
		this->X += this->velocityX;
		this->velocityY += this->gravity;
		this->Y += (this->velocityY);
		
		if ((this->collision()))
		{

		}

		

	}
}

bool Entity::render(SDL_Surface *surface)
{
	this->movement();
	return Object::render(surface);
	
}

void Entity::release()
{
	Object::release();
}

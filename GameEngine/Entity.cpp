//
//  Entity.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Entity.h"




Entity::Entity()
{
	Object::Object();
	
	this->active			= true;
	this->movable			= false;
	this->stoped			= true;
	this->iscollision		= true;
	this->direction			= 1;
	this->velocityX			= 0.0;
	this->velocityY			= 0.0;
	this->jumpVelocity		= jumpAcceleration;
	this->gravity			= gravtiyAcceleration;
}



Entity::Entity(SDL_Surface* surface, SDL_Renderer *renderer)
{
	Object::Object();
	
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (this->texture != NULL)
	{
		SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
		this->active		= true;
		this->movable		= false;
		this->iscollision	= true;
		this->direction		= 1;
		this->velocityX		= 0.0;
		this->velocityY		= 0.0;
		this->gravity		= 4.9;
	}
	else
	{
		fprintf(stderr, "Entity::Entity(SDL_Texture *): Texture assigned is NULL pointer\n");
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
		Entity *auxEntity = this->background->entities[i].get();
		
		if(not( auxEntity              == NULL       or
			    auxEntity->id          == this->id   or
			    auxEntity->iscollision == false
			   )
		   )
		{
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;
			
			leftA   = this->X + this->velocityX;
			topA    = this->Y + this->velocityY;
			rightA  = this->width  + leftA;
			bottomA = this->height + topA;
			
			leftB   = this->background->entities[i]->X;
			topB    = this->background->entities[i]->Y;
			rightB  = this->background->entities[i]->width  + leftB;
			bottomB = this->background->entities[i]->height + topB;
			
			if( leftA - this->velocityX > leftB and rightA < rightB and
			   bottomA - this->velocityY < bottomB and topA > topB)
			{
				//printf("Dentro de B\n");
				this->velocityY = 0;
				this->velocityX = 0;
				this->Y = topB - this->height;
		
			}
			if(     ( bottomA > topB  and topA  < bottomB and
					  rightA  > leftB and leftA < rightB)
				 or ( leftA > leftB and rightA < rightB and
					  bottomA < bottomB and topA > topB)
			   )
			{
				collision = true;
				
				leftA   = this->X;
				topA    = this->Y;
				rightA  = this->width  + leftA;
				bottomA = this->height + topA;
				
				
				if(bottomA == topB)
				{
//					printf("1.1\n");
					this->X += this->velocityX;
					this->velocityY = 0;
					
				}
				else if(leftA == rightB or leftB == rightA)
				{
//					printf("2.1\n");
					this->Y += this->velocityY;
					this->velocityX = 0;

				}
				else
				{
					
					float speedX = this->velocityX >= 0 ?
										this->velocityX : -this->velocityX;
					
					float speedY = this->velocityY >= 0 ?
										this->velocityY : -this->velocityY;
//					printf("speed %f %f\n",speedX,speedY);
					float *timeUntilCollisionX = new float;
					float *timeUntilCollisionY = new float;

					if (this->velocityX > 0)
					{
						if (this->velocityY < 0)
						{
//							printf("3.1.1\n");
							*timeUntilCollisionX = (leftB - rightA)/
														speedX;
							
							*timeUntilCollisionY = (topA - bottomB)/
														speedY;
						}
						else if (this->velocityY > 0)
						{
//							printf("3.1.2\n");
							*timeUntilCollisionX = (leftB - rightA)/
														speedX;
							
							*timeUntilCollisionY = (topB - bottomA)/
														speedY;
						}
						else
						{
//							printf(" 3.1.3\n");
							*timeUntilCollisionX = (leftB - rightA)/
														speedX;

							timeUntilCollisionY = NULL;
						}
					}
					else if (this->velocityX < 0)
					{
						if (this->velocityY < 0)
						{
//							printf("3.2.1\n");
							*timeUntilCollisionX = (leftA - rightB)/
							speedX;
							
							*timeUntilCollisionY = (topA - bottomB)/
							speedY;
						}
						else if (this->velocityY > 0)
						{
//							printf("3.2.2\n");
							*timeUntilCollisionX = (leftA - rightB)/
							speedX;
							
							*timeUntilCollisionY = (topB - bottomA)/
							speedY;
						}
						else
						{
//							printf("3.2.3\n");
							*timeUntilCollisionX = (leftB - rightA)/
							speedX;
							
							timeUntilCollisionY = NULL;
						}
					}
					else
					{
						if (this->velocityY < 0)
						{
//							printf("3.3.1\n");
							timeUntilCollisionX = NULL;
							
							*timeUntilCollisionY = (topA - bottomB)/speedY;
						}
						else if (this->velocityY > 0)
						{
//							printf("3.3.2\n");
							timeUntilCollisionX = NULL;
							
							*timeUntilCollisionY = (topB - bottomA)/speedY;
						}
						else
						{
//							printf("3.3.3\n");
							timeUntilCollisionX = NULL;
							
							timeUntilCollisionY = NULL;
						}
					}
					

					if (timeUntilCollisionX != NULL && timeUntilCollisionY != NULL)
					{
						if(*timeUntilCollisionX > 0 && *timeUntilCollisionY > 0)
						{

							if (*timeUntilCollisionX <= *timeUntilCollisionY)
							{
//								printf("H.1\n");
								this->X += (int)*timeUntilCollisionX *
												this->velocityX;
								
								this->Y += (int)*timeUntilCollisionX *
												this->velocityY;
								this->velocityX = 0;
							}
							else
							{
//								printf("H.2\n");
								this->X += (int)	*timeUntilCollisionY *
												this->velocityX;
								
								this->Y += (int)	*timeUntilCollisionY *
												this->velocityY;
								this->velocityY = 0;
							}
						}
						else if (*timeUntilCollisionX < 0 && *timeUntilCollisionY >= 0)
						{
//							printf("H.3\n");
							this->Y += *timeUntilCollisionY * this->velocityY;
							this->X += this->velocityX;
							this->velocityY = 0;
						}
						else if (*timeUntilCollisionY < 0 && *timeUntilCollisionX >= 0)
						{
//							printf("H.4\n");
							this->X += *timeUntilCollisionX * this->velocityX;
							this->Y += this->velocityY;
							this->velocityX = 0;
						}
					}
					else if (timeUntilCollisionX == NULL and timeUntilCollisionY != NULL)
					{
//						printf("J.1\n");
						if (this->velocityY > 0)
							this->Y = topB - this->height;
						else
							this->Y = bottomB;
						this->velocityY = 0;
					}
					else if(timeUntilCollisionY == NULL and timeUntilCollisionX != NULL)
					{
//						printf("J.2\n");
						if (this->velocityX > 0)
							this->X = leftB - this->width;
						else
							this->X = rightB;
						this->velocityX = 0;
					}
				}
			}
		}
	}

	if (not collision)
	{
		this->X += this->velocityX;
		this->Y += this->velocityY;
	}
	return collision;
}

void Entity::movement()
{
	
	if(this->movable)
	{
		this->velocityY += this->gravity;
		if(this->stoped)
		{
			if (this->velocityX < 0) {
				this->velocityX += 8;
				if (this->velocityX > -2)
				{
					this->velocityX = 0;
				}
			}
			else if (this->velocityX > 0)
			{
				this->velocityX -= 8;
				if (this->velocityX < 2)
				{
					this->velocityX = 0;
				}
			}
		}
		this->collision();
	}
}

bool Entity::render(SDL_Renderer *renderer)
{
	this->movement();
	return Object::render(renderer);
	
}

void Entity::release()
{
	Object::release();
}

void Entity::eventHandler(SDL_Event *event,Uint8 *keyStates)
{
	
}

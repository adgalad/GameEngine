//
//  Object.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Object.h"

int Object::_id = 0;

Object::Object()
{

	this->texture           = NULL;
	this->id				= this->_id++;
	this->X                 = 0;
	this->Y                 = 0;
	this->isSprite			= false;
	this->isStatic			= false;
	this->animated          = false;
	this->verticalAnimation = true;
	this->spriteMap			= NULL;

}

Object::Object(SDL_Surface *surface, SDL_Renderer *renderer)
{
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (this->texture != NULL)
	{
		SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
		this->id				= this->_id++;
		this->X					= 0;
		this->Y					= 0;
		this->isSprite			= false;
		this->isStatic			= false;
		this->animated			= false;
		this->verticalAnimation = true;
		this->spriteMap			= NULL;
	}
	else
	{
		fprintf(stderr, "Object::Object(SDL_Texture *): Surface assigned is NULL pointer\n");
	}
}

void Object::setStatic(bool value)
{
	this->isStatic = value;
	if (this->isStatic)
	{
		this->cameraX = NULL;
		this->cameraY = NULL;
	}
}

bool Object::setCurrentFrame(int positionX, int positionY)
{
	if (this->animated)
	{
		this->currentFrameX = positionX;
		this->currentFrameY = positionY;
		return true;
	}
	else
	{
		fprintf(stderr, "Error: Object is not animated.\n");
		return false;
	}
}

void Object::setAnimated(bool value)
{
	this->animated = value;

}

void Object::setAnimateValues(int columns, int rows)
{
	if (this->texture != NULL)
	{
		if(columns > 0 and rows > 0)
		{
			this->columns		= columns;
			this->rows			= rows;
			this->width			= this->width/columns;
			this->height		= this->height/rows;
			this->currentFrameX = 0;
			this->currentFrameY = 0;
			this->isSprite		= true;
			this->spriteMap		= NULL;
		}
		else
		{
			fprintf(stderr, "WARNING Object::setAnimateValues(): Division by zero\n");
		}
	}
	else
	{
		fprintf(stderr, "WARNING Object::setAnimateValues(): Texture is null pointer\n");
	}
}


int Object::getCurrentFrameX()
{
	return this->currentFrameX;
}

int Object::getCurentFrameY()
{
	return this->currentFrameY;
}

void Object::addAction(ObjectAction *action)
{
	this->action.push_back(unique_ptr<ObjectAction>(action));
}


/**
 * Load an image to the SDL surface of the object
 */
bool Object::loadImage(string file, SDL_Renderer *renderer)
{
	SDL_Surface *surface;
	if ((surface = IMG_Load(&file[0]))==NULL)
	{
		fprintf(stderr, "Error Object::loadImage() Couldn't load the image into the surface\n");
		return false;
	}

	this->width  = surface->w;
	this->height = surface->h;
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return true;
}
bool Object::loadSurface(SDL_Surface *surface, SDL_Renderer *renderer)
{

	if (surface == NULL)
	{
		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Surface is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	if (renderer == NULL)
	{
		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Renderer is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (this->texture != NULL)
	{
		SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	}
	else
	{
		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Texture is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	return true;
}

bool Object::loadTexture(SDL_Texture *texture)
{
	if (texture == NULL)
	{
		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Texture assigned is NULL pointer\n\t%s\n",SDL_GetError());
		return false;
	}
	this->texture = texture;
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	
	return true;
}

/**
 * Render all the SDL surface of the object into the
 * (X,Y) position in the destiny surface
 */
bool Object::renderObject(SDL_Renderer *renderer, int X, int Y) {
	if(renderer == NULL or this->texture == NULL) {
		fprintf(stderr, "Error Object::renderObject() Couldn't render the object (not animated) \n");
		return false;
	}
	
	SDL_Rect rectangle;
	rectangle.x = X;
	rectangle.y = Y;
	rectangle.w = this->width;
	rectangle.h = this->height;
	SDL_RenderCopy( renderer,
				    this->texture,
				    NULL,
				    &rectangle
				);
	return true;
}

/**
 * Render a part of the SDL surface of the object into the
 * (X1,Y1) position inside the destiny surface
 */

bool Object::renderObject(SDL_Renderer *renderer,
						  int X1, int Y1,
						  int X2, int Y2,
						  int W,  int H
						)
{
	if(renderer == NULL or this->texture == NULL) {
		fprintf(stderr, "Error Object::renderObject() Couldn't render the object \n");
		return false;
	}
	
	SDL_Rect destRectangle;
	destRectangle.x = X1;
	destRectangle.y = Y1;
	destRectangle.w = W;
	destRectangle.h = H;

	SDL_Rect srcRectangle;
	srcRectangle.x = X2*W;
	srcRectangle.y = Y2*H;
	srcRectangle.w = W;
	srcRectangle.h = H;
	
	SDL_RenderCopy( renderer,
				   this->texture,
				   &srcRectangle,
				   &destRectangle
				   );
	return true;
}

/*
 * Generic render function. Call this->renderObject() with different
 * arguments depending on this->animated value
 */
bool Object::render(SDL_Renderer* renderer)
{
	if (this->isSprite)
	{
		if (this->animated)
		{
			if (!this->verticalAnimation)
			{
				if (this->columns-1 > this->currentFrameX)
				{
					this->currentFrameX += 1;
				}
				else
				{
					this->currentFrameX = 0;
				}
			}
			else
			{
				if (this->rows-1 > this->currentFrameY)
				{
					this->currentFrameY += 1;
				}
				else
				{
					this->currentFrameY = 0;
				}
			}
		}
		else
		{
			if (!this->verticalAnimation and this->currentFrameX != 0)
			{
				if (this->columns-1 > this->currentFrameX)
				{
					this->currentFrameX += 1;
				}
				else
				{
					this->currentFrameX = 0;
				}
			}
			else if (this->verticalAnimation and this->currentFrameY != 0)
			{
				if (this->rows-1 > this->currentFrameY)
				{
					this->currentFrameY += 1;
				}
				else
				{
					this->currentFrameY = 0;
				}
			}
		}
		if (this->cameraX != NULL)
		{
			return renderObject( renderer,
								this->X - *this->cameraX,
								this->Y - *this->cameraY,
								this->currentFrameX,
								this->currentFrameY,
								this->width,
								this->height
								);
		}
		else
		{
			return renderObject( renderer,
								this->X,
								this->Y,
								this->currentFrameX,
								this->currentFrameY,
								this->width,
								this->height
								);
		}


	}
	else
	{
		if (this->cameraX != NULL)
		{
			return renderObject( renderer,
								this->X - *this->cameraX,
								this->Y - *this->cameraY
								);
		}
		else
		{
			return renderObject( renderer,
								this->X,
								this->Y
								);
		}
	}
}





/**
 * Free allocated memory of Object class
 */
void Object::release()
{
	for (int i = 0 ; i < action.size() ; i++)
	{
		action[i].release();
	}
}

void Object::setEnvironmentValues( int *winWidth, int *winHeight,
								   int *cameraX,  int *cameraY
								)
{
	this->winWidth  = winWidth;
	this->winHeight = winHeight;
	if (!this->isStatic)
	{
		this->cameraX = cameraX;
		this->cameraY = cameraY;
	}
}
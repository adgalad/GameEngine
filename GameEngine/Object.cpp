//
//  Object.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Object.h"


Object::Object()
{
	this->surface           = NULL;
	this->X                 = 0;
	this->Y                 = 0;
	this->isSprite			= false;
	this->animated          = false;
	this->verticalAnimation = true;
}

Object::Object(SDL_Surface *surface)
{
	this->surface = surface;
	if (this->surface != NULL)
	{
		this->X					= 0;
		this->Y					= 0;
		this->width				= this->surface->w;
		this->height			= this->surface->h;
		this->isSprite			= false;
		this->animated			= false;
		this->verticalAnimation = true;
	}
	else
	{
		fprintf(stderr, "Object::Object(SDL_Surface *): Surface assigned is NULL pointer\n");
	}

}

Object::Object(SDL_Surface *surface,
					   int  columns,
					   int  rows,
			           int  width,
			           int  height
			   )
{
	this->surface			= surface;
	this->columns			= columns;
	this->rows				= rows;
	this->width				= width;
	this->height			= height;
	this->animated			= true;
	this->currentFrameX		= 0;
	this->currentFrameY		= 0;
	this->verticalAnimation = true;
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

void Object::setAnimate(int columns, int rows)
{
	if (this->surface != NULL)
	{
		this->columns		= columns;
		this->rows			= rows;
		this->width			= this->surface->w/columns;
		this->height		= this->surface->h/rows;
		this->currentFrameX = 0;
		this->currentFrameY = 0;
		this->isSprite		= true;

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
bool Object::loadImage(char* file)
{
	if ((this->surface = IMG_Load(file))==NULL)
	{
		fprintf(stderr, "Error Object::loadImage() Couldn't load the image into the surface\n");
		return false;
	}
	this->width  = this->surface->w;
	this->height = this->surface->h;
	return true;
}

/**
 * Render all the SDL surface of the object into the
 * (X,Y) position of the destiny surface
 */
bool Object::renderObject(SDL_Surface* surface, int X, int Y) {
	if(surface == NULL || this->surface == NULL) {
		return false;
	}
	
	SDL_Rect rectangle;
	
	rectangle.x = X;
	rectangle.y = Y;
	if (this->surface->w > surface->w || this->surface->h > surface->w)
	{
		SDL_Rect *srcRectangle= new SDL_Rect();
		srcRectangle->x = 0;
		srcRectangle->y = 0;
		srcRectangle->w = surface->w;
		srcRectangle->h = surface->h;
		SDL_BlitSurface(this->surface, srcRectangle, surface, &rectangle);
	}
	else
	{
		SDL_BlitSurface(this->surface, NULL, surface, &rectangle);
	}
	return true;
}

/**
 * Render a part of the SDL surface of the object into the
 * (X1,Y1) position inside the destiny surface
 */

bool Object::renderObject(SDL_Surface *surface,
						  int X1, int Y1,
						  int X2, int Y2,
						  int W,  int H
						)
{
	if(surface == NULL || this->surface == NULL) {
		return false;
	}
	
	SDL_Rect *destRectangle= new SDL_Rect();
	
	destRectangle->x = X1;
	destRectangle->y = Y1;
//	printf("%d %d\n",X1,Y1);
	SDL_Rect *srcRectangle= new SDL_Rect();
//	printf("%d %d %d %d\n\n",W,H,X2,Y2);
	srcRectangle->x = X2*W;
	srcRectangle->y = Y2*H;
	srcRectangle->w = W;
	srcRectangle->h = H;
	SDL_BlitSurface(
					 this->surface,
					 srcRectangle,
					 surface,
					 destRectangle
				);
	
	return true;
}

/*
 * Generic render function. Call this->renderObject() with different
 * arguments depending on this->animated value
 */
bool Object::render(SDL_Surface *surface)
{
	if (this->isSprite == true)
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
			if (!this->verticalAnimation && this->currentFrameX != 0)
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
			else if (this->verticalAnimation && this->currentFrameY != 0)
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
		return renderObject(surface,
							this->X, this->Y,
							this->currentFrameX, this->currentFrameY,
							this->width, this->height
							);
	}
	else
	{
		return renderObject(surface, X, Y);
	}
}

/**
 * Make the object surface's pixel with the same RBG transparents
 */

bool Object::makeTransparent(int R, int G, int B)
{
	if(this->surface == NULL)
	{
		return false;
	}
	  this->surface->format->Amask = 0xFF000000;
		this->surface->format->Ashift = 24;
	SDL_SetColorKey( this->surface,
					 SDL_SRCCOLORKEY | SDL_RLEACCEL,
					 SDL_MapRGB( this->surface->format,
							     R, G, B
							)
				);
	return true;
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
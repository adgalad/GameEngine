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
	this->objectSurface = NULL;
}

Object::Object(SDL_Surface *surface)
{
	this->objectSurface = surface;
	this->animated      = false;

}

Object::Object(SDL_Surface *surface,
					   int  columns,
					   int  rows,
			           int  width,
			           int  height
			   )
{
	this->objectSurface = surface;
	this->columns       = columns;
	this->rows          = rows;
	this->width         = width;
	this->height        = height;
	this->animated      = true;
	this->currentFrameX = 0;
	this->currentFrameY = 0;
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


/*
 * Load an image to the SDL surface of the object
 */
bool Object::loadImage(char* file)
{
	SDL_Surface *Surf,*Surf_Return;
	
	if ((Surf = IMG_Load(file))==NULL){
		return NULL;
		
	}
	Surf_Return = SDL_DisplayFormat(Surf);
	SDL_FreeSurface(Surf);
	return Surf_Return;
	
}

/* 
 * Render all the SDL surface of the object into the
 * (X,Y) position of the destiny surface
 */
bool Object::renderObject(SDL_Surface* surface, int X, int Y) {
	if(surface == NULL || this->objectSurface == NULL) {
		return false;
	}
	
	SDL_Rect rectangle;
	
	rectangle.x = X;
	rectangle.y = Y;
	SDL_BlitSurface(this->objectSurface, NULL, surface, &rectangle);
	
	return true;
}

/*
 * Render a part of the SDL surface of the object into the
 * (X1,Y1) position inside the destiny surface
 */
bool Object::renderObject(SDL_Surface *surface,
						  int X1, int Y1,
						  int X2, int Y2,
						  int W,  int H
						)
{
	if(surface == NULL || this->objectSurface == NULL) {
		return false;
	}
	
	SDL_Rect destRectangle;
	
	destRectangle.x = X1;
	destRectangle.y = Y1;
	
	SDL_Rect srcRectangle;
	
	srcRectangle.x = X2;
	srcRectangle.y = Y2;
	srcRectangle.w = W;
	srcRectangle.h = H;
	
	SDL_BlitSurface(
					 surface,
					 &srcRectangle,
					 this->objectSurface,
					 &destRectangle
				);
	
	return true;
	
}

bool Object::render(SDL_Surface *surface)
{
	if (this->animated)
	{
		return renderObject(surface,
							X, Y,
							currentFrameX, currentFrameY,
							width, height
							);
	}
	else
	{
		return renderObject(surface, X, Y);
	}
}

/*
 * Make the object surface's pixel with the same RBG transparents
 */
bool Object::makeTransparent(int R, int G, int B)
{
	if(this->objectSurface == NULL)
	{
		return false;
	}
	
	SDL_SetColorKey(
					this->objectSurface,
					SDL_SRCCOLORKEY | SDL_RLEACCEL,
					SDL_MapRGB(this->objectSurface->format, R, G, B)
				);
	
	return true;
}

void Object::release()
{
	for (int i = 0 ; i < action.size() ; i++)
	{
		action[i].release();
	}
	free(this->objectSurface);
}
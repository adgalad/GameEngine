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


	this->id				= this->_id++;
	this->X                 = 0;
	this->Y                 = 0;


}




/**
 * Free allocated memory of Object class
 */
Object::~Object()
{

}

//void Object::setStatic(bool value)
//{
//	this->isStatic = value;
//	if (this->isStatic)
//	{
//		this->cameraX = NULL;
//		this->cameraY = NULL;
//	}
//}
//
//bool Object::setCurrentFrame(int positionX, int positionY)
//{
//	if (this->animated)
//	{
//		this->currentFrameX = positionX;
//		this->currentFrameY = positionY;
//		return true;
//	}
//	else
//	{
//		fprintf(stderr, "Error: Object is not animated.\n");
//		return false;
//	}
//}

//void Object::setAnimated(bool value)
//{
//	this->animated = value;
//
//}
//
//void Object::setAnimateValues(int columns, int rows)
//{
//	if (this->texture != NULL)
//	{
//		if(columns > 0 and rows > 0)
//		{
//			this->columns		= columns;
//			this->rows			= rows;
//			this->width			= this->width/columns;
//			this->height		= this->height/rows;
//			this->currentFrameX = 0;
//			this->currentFrameY = 0;
//			this->isSprite		= true;
//			this->spriteMap		= NULL;
//		}
//		else
//		{
//			fprintf(stderr, "WARNING Object::setAnimateValues(): Division by zero\n");
//		}
//	}
//	else
//	{
//		fprintf(stderr, "WARNING Object::setAnimateValues(): Texture is null pointer\n");
//	}
//}






/**
 * Load an image to the SDL surface of the object
 */
//bool Object::loadImage(string file, SDL_Renderer *renderer)
//{
//	SDL_Surface *surface;
//	if ((surface = IMG_Load(&file[0]))==NULL)
//	{
//		fprintf(stderr, "Error Object::loadImage() Couldn't load the image into the surface\n");
//		return false;
//	}
//
//	this->width  = surface->w;
//	this->height = surface->h;
//	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_FreeSurface(surface);
//	return true;
//}
//bool Object::loadSurface(SDL_Surface *surface, SDL_Renderer *renderer)
//{
//
//	if (surface == NULL)
//	{
//		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Surface is NULL pointer\n\t%s\n",SDL_GetError());
//		return false;
//	}
//	if (renderer == NULL)
//	{
//		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Renderer is NULL pointer\n\t%s\n",SDL_GetError());
//		return false;
//	}
//	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
//	if (this->texture != NULL)
//	{
//		SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
//	}
//	else
//	{
//		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Texture is NULL pointer\n\t%s\n",SDL_GetError());
//		return false;
//	}
//	return true;
//}

//bool Object::loadTexture(SDL_Texture *texture)
//{
//	if (texture == NULL)
//	{
//		fprintf(stderr, "Object::loadSurface(SDL_Surface*, SDL_Renderer*): Texture assigned is NULL pointer\n\t%s\n",SDL_GetError());
//		return false;
//	}
//	this->texture = texture;
//	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
//	
//	return true;
//}


/*
 * Generic render function. Calls this->renderObject() with different
 * arguments depending on this->animated value
 */

void Object::setEnvironmentValues( int *winWidth, int *winHeight,
								   int *cameraX,  int *cameraY
								)
{
	this->winWidth  = winWidth;
	this->winHeight = winHeight;
	this->cameraX = cameraX;
	this->cameraY = cameraY;
}
//
//  Texture.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 10/7/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Texture.hpp"

int Sprite::_id = 0;
SDL_Renderer* Sprite::renderer = NULL;


Sprite::Sprite()
{
	id				= _id++;
	name			= "Texture_" + to_string(id);
	path			= "";
	columns			= 1;
	rows			= 1;
	width			= 1;
	height			= 1;
	direcction		= RIGHT_DIR;
	spriteMap		= NULL;
	spriteTexture	= NULL;
}

Sprite::~Sprite()
{
	free(spriteMap);
	SDL_free(spriteTexture);
	spritePosition.clear();
	if (renderer != NULL)
	{
		SDL_free(renderer);
		renderer = NULL;
	}
}

void Sprite::createRenderer(SDL_Window *window)
{
	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_TARGETTEXTURE |
								  SDL_RENDERER_ACCELERATED );
}

void Sprite::renderPresent()
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Sprite::setColumnsAndRows(int columns, int rows)
{
	if (spriteTexture == NULL)
	{
		fprintf(stderr,"ERROR Sprite::setColumnsAndRows: Set a SDL_Texture first.\n)");
		return;
	}
	this->columns	= columns;
	this->rows		= rows;
	width			= width/columns;
	height			= height/rows;
}

void Sprite::setName(string name)
{
	this->name = name;
}

bool Sprite::loadImage(string file, SDL_Renderer *renderer)
{
	SDL_Surface *surface;
	if ((surface = IMG_Load(&file[0]))==NULL)
	{
		fprintf(stderr, "ERROR Sprite::loadImage() Couldn't load the image into the surface\n");
		return false;
	}
	
	width	= surface->w;
	height	= surface->h;
	path	= file;
	spriteTexture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return true;
}


bool Sprite::renderTexture(int X, int Y)
{
	if(renderer == NULL or spriteTexture == NULL) {
		fprintf(stderr, "Error renderTexture() Couldn't render the object (not animated) \n");
		return false;
	}
	
	SDL_Rect rectangle;
	rectangle.x = X;
	rectangle.y = Y;
	rectangle.w = this->width;
	rectangle.h = this->height;
	SDL_RenderCopy( renderer,
				   spriteTexture,
				   NULL,
				   &rectangle
				   );
	return true;
}


bool Sprite::renderTexture(int X1, int Y1, int X2, int Y2, int W, int H)
{
	if(renderer == NULL or spriteTexture == NULL) {
		fprintf(stderr, "Error renderTexture() Couldn't render the object \n");
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
				   spriteTexture,
				   &srcRectangle,
				   &destRectangle
				   );
	return true;
}

bool Sprite::render(int X, int Y, int* cameraX, int* cameraY)
{
	if (columns == rows == 1)
	{
		if (this->animated)
		{
			if (!this->verticalAnimation)
			{
				if (this->columns-1 > this->currentFrame.x)
				{
					this->currentFrame.x += 1;
				}
				else
				{
					this->currentFrame.x = 0;
				}
			}
			else
			{
				if (this->rows-1 > this->currentFrame.y)
				{
					this->currentFrame.y += 1;
				}
				else
				{
					this->currentFrame.y = 0;
				}
			}
		}
		else
		{
			if (!this->verticalAnimation and this->currentFrame.x != 0)
			{
				if (this->columns-1 > this->currentFrame.x)
				{
					this->currentFrame.x += 1;
				}
				else
				{
					this->currentFrame.x = 0;
				}
			}
			else if (this->verticalAnimation and this->currentFrame.y != 0)
			{
				if (this->rows-1 > this->currentFrame.y)
				{
					this->currentFrame.y += 1;
				}
				else
				{
					this->currentFrame.y = 0;
				}
			}
		}
		if (cameraX != NULL)
		{
			return renderTexture(X - *cameraX,
									Y - *cameraY,
									this->currentFrame.x,
									this->currentFrame.y,
									this->width,
									this->height
									);
		}
		else
		{
			return renderTexture(X,
									Y,
									this->currentFrame.x,
									this->currentFrame.y,
									this->width,
									this->height
									);
		}
		
		
	}
	else
	{
		if (cameraX != NULL)
		{
			return renderTexture(X - *cameraX, Y - *cameraY);
		}
		else
		{
			return renderTexture(X, Y);
		}
	}
}
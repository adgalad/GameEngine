//
//  TextEntity.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 6/29/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "TextEntity.h"

TextEntity::TextEntity()
{
	this->font = NULL;
	Entity::Entity();
}

bool TextEntity::setColor(Uint8 R, Uint8 B , Uint8 G, Uint8 A)
{
	this->color.r = R;
	this->color.b = B;
	this->color.b = G;
	this->color.a = A;
	return true;
}

bool TextEntity::setFont(char *font, int size)
{
	this->font = TTF_OpenFont(font, size);
	if (!this->font)
	{
		fprintf(stderr,
				"WARNING TextEntity::setFont(char*, int) Unable to open TTF\n\t%s\n",
				SDL_GetError()
				);
	}
	return this->font;
}

bool TextEntity::setMessage(SDL_Renderer *renderer, const char* message, ...)
{
	
	char buf[1024];
	sprintf(buf, "");
	va_list ap;
	va_start(ap, message);
	vsprintf(buf + strlen(buf), message, ap);
	printf("%d %s",this->font,buf);
	SDL_Surface* textSurface = TTF_RenderText_Solid(this->font,
													buf,
													this->color
												);
	if(!textSurface)
	{
		fprintf(stderr,
				"WARNING TextEntity::setMessage(SDL_Renderer*, char*) Unable to create a surface with the text\n\t%s\n",
				SDL_GetError()
				);
		return false;
	}
		//Create texture from surface pixels
	this->texture = SDL_CreateTextureFromSurface( renderer, textSurface );
	if( this->texture == NULL )
	{
		fprintf(stderr,
				"WARNING TextEntity::setMessage(SDL_Renderer*, char*) Unable to create texture from rendered text! SDL Error: %s\n",
				SDL_GetError() );
	}
	else
	{
			//Get image dimensions
		this->width  = textSurface->w;
		this->height = textSurface->h;
	}
	
		//Get rid of old surface
	SDL_FreeSurface( textSurface );
	return true;
}





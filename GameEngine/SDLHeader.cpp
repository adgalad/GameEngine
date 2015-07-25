//
//  SDLHeader.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 6/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include <stdio.h>
#include "SDLHeader.h"


TextureList GameParameter::_textures;
int	  GameParameter::_cameraX			 = 0;
int   GameParameter::_cameraY			 = 0;
float GameParameter::_jumpAcceleration	 = -50.0;
float GameParameter::_maxWalkVelocityX	 = 10.0;
float GameParameter::_maxWalkVelocityY    = 40.0;
float GameParameter::_maxSprintVelocityX  = 32.0;
float GameParameter::_maxSprintVelocityY  = 32.0;
float GameParameter::_gravtiyAcceleration = 9.8;


TextureList::TextureList(){}
void TextureList::release()
{
	for(int i = 0 ; i < this->textures.size() ; i++)
	{
		SDL_free(textures[i]->SDLtexture);
		free(textures[i]);
	}
}

bool TextureList::addTexture(TextureInfo *ti)
{
	for(int i = 0 ; i < this->textures.size() ; i++)
	{
		if (this->textures[i]->_id == ti->_id)
		{
			fprintf(stderr,"WARNING TextureList::addTexture(TextureInfo*): Item's id already exists.\n");
			return false;
		}
	}
	this->textures.push_back(ti);
	return true;
}

TextureInfo* TextureList::getTextureById(int _id)
{
	for(int i = 0 ; i < this->textures.size() ; i++)
	{
		if (this->textures[i]->_id == _id)
		{
			return textures[i];
		}
	}
	fprintf(stderr,"WARNING TextureList::addTexture(TextureInfo*): Could not find item with id = %d.\n",_id);
	return NULL;
}

TextureInfo* TextureList::getTextureByName(const char *name)
{
	for(int i = 0 ; i < this->textures.size() ; i++)
	{
		if (!strcmp(this->textures[i]->name.c_str(), name))
		{
			return textures[i];
		}
	}
	fprintf(stderr,"WARNING TextureList::addTexture(TextureInfo*): Could not find item with name = \"%s\".\n",name);
	return NULL;
}
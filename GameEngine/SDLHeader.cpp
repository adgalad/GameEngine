//
//  SDLHeader.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 6/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include <stdio.h>
#include "SDLHeader.h"

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
//
//  Tile.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Tile.h"

Tile::Tile()
{
	
}

void Tile::addObject(Object *object)
{
	objects.push_back(unique_ptr<Object>(object));
}

bool Tile::render(SDL_Surface *surface)
{
	if (not(this->renderObject(surface, X, Y)))
	{
		return false;
	}
	for (int i = 0; i < objects.size(); i++) {
		if (not(objects[i]->render(surface)))
		{
			return false;
		}
	}
	return true;
}

void Tile::release()
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->release();
	}
	this->release();
}

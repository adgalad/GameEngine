//
//  Background.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Background.h"
#include "Entity.h"
Background::Background()
{

}

void Background::addEntity(Entity *entity)
{
	entity->setBackground(this);
	if(entity->background == NULL)
	{
		exit(EXIT_FAILURE);
	}
	this->entities.push_back(unique_ptr<Entity>(entity));
}

bool Background::render(SDL_Surface *surface)
{
	Object::render(surface);
	for (int i = 0; i < entities.size(); i++)
	{
		if (not(entities[i]->render(surface)))
		{
			fprintf(stderr, "Couldn't render the object\n");
			return false;
		}
	}

	return true;
}

void Background::release()
{
	for (int i = 0; i < this->entities.size(); i++) {
		this->entities[i]->release();
		this->entities[i].release();
	}
}

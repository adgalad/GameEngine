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
	this->X = 0;
	this->Y = 0;
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



void Background::setBackgroundEnviromentValues( int *winWidth, int *winHeight,
											    int *cameraX,  int *cameraY
									 )
{
	if (!isStatic)
	Object::setEnvironmentValues(winWidth, winHeight, cameraX, cameraY);
	
	for (int i = 0; i < (int)this->entities.size(); i++) {
		this->entities[i]
			->setEnvironmentValues( winWidth, winHeight,
									cameraX, cameraY
								);
	}
}

bool Background::render(SDL_Renderer *renderer)
{
	Object::render(renderer);
	bool returnValue = true;

	for (int i = 0; i < entities.size(); i++)
	{
		returnValue &= entities[i]->render(renderer);
	}

	return returnValue;
}

void Background::release()
{
	for (int i = 0; i < this->entities.size(); i++) {
		this->entities[i]->release();
		this->entities[i].release();
	}
}


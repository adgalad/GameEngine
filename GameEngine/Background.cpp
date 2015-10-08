//
//  Background.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Background.h"

Background::Background()
{

}

Background::~Background()
{
	
}

void Background::addEntity(Entity *entity)
{
	
	if(entity == NULL)
	{
		fprintf(stderr,"ERROR Background::addEntity(TemporalEntity *) Entity is NULL pointer\n\t%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	entity->setBackground(this);
	this->entities.push_back(unique_ptr<Entity>(entity));
}

void Background::addTemporalEntity(Entity *entity)
{
	if(entity == NULL)
	{
		fprintf(stderr,"ERROR Background::addTemporalEntity(TemporalEntity *) Entity is NULL pointer\n\t%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	entity->setBackground(this);
	this->tempEntities.pushFront(entity);
}

void Background::removeTemporalEntity(Entity *entity)
{
	this->tempEntities.remove(entity);
}

void Background::setEnvironmentValues( int *winWidth, int *winHeight,
											    int *cameraX,  int *cameraY
									 )
{
	if (!isStatic)
	Object::setEnvironmentValues(winWidth, winHeight, cameraX, cameraY);
	
	for (int i = 0; i < (int)this->entities.size(); i++) {
		this->entities[i]
			->setEnvironmentValues( winWidth, winHeight,
									cameraX , cameraY
								);
	}
}

void Background::loop()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->movement();
		entities[i]->collision();
	}
	this->tempEntities.loop();
}

bool Background::render(SDL_Renderer *renderer)
{
	Object::render(renderer);
	bool returnValue = true;
	
	for (int i = 0; i < entities.size(); i++)
	{
		returnValue &= entities[i]->render(renderer);
	}

	returnValue &= this->tempEntities.render(renderer);
	return returnValue;
}

void Background::release()
{
	for (int i = 0; i < this->entities.size(); i++) {
		this->entities[i]->release();
		this->entities[i].release();
	}
}


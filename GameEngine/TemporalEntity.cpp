//
//  TemporalEntity.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 7/20/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "TemporalEntity.h"
#include "Background.h"


TemporalEntity::TemporalEntity(){}

bool TemporalEntity::collision()
{
	return	(Entity::collision() &&	this->disappearOnColiision) ||
			(SDL_GetTicks() - this->beginTime > this->timeUntilDisappear);
}

void TemporalEntity::setTime(unsigned int miliseconds)
{
	this->timeUntilDisappear = miliseconds;
	this->beginTime = SDL_GetTicks();
}


bool TemporalEntity::render(SDL_Renderer *renderer)
{
	Entity::render(renderer);
	return true;
}

void TemporalEntity::setDisappearOnColission(bool value)
{
	this->disappearOnColiision = value;
}

//
//  Entity.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Entity__
#define __GameEngine__Entity__

#include <stdio.h>
#include "Object.h"
#include "Background.h"

class Background;

class Entity : public Object
{
public:
	std::unique_ptr<Background> background;
	
	bool active;
	bool movable;
	bool iscollision;

	int    _id;
	int    direction;
	float  velocityX;
	float  velocityY;
	float  jumpAcceleration;
	float  gravity;

public:

protected:
	bool collision();

public:
	Entity();
	
	Entity(SDL_Surface *surface);
	
	void setBackground(Background *bg);
	
	void moveTo(int x, int y);
	
	void movement();

	bool render(SDL_Surface *surface);
	
	void release();
	
	
};

#endif /* defined(__GameEngine__Entity__) */

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
#include "SDLHeader.h"
#include "Object.h"


class Background;
class EntityList;

class Texture
{
	
};

class Entity : public Object
{
	friend class EntityList;
	friend class Background;
public:
	Background *background;
	
	int specialAction;
	int previousSpritePosition;
	int posUp;
	int posDown;
	int posRight;
	int posLeft;
	int posStanding;
	
	bool active;
	bool movable;
	bool stoped;
	bool iscollision;
	bool standingAnimated;

	int    direction;
	float  velocityX;
	float  velocityY;
	float  jumpVelocity;
	float  gravity;

public:

protected:
	
	virtual bool collision();

public:
	Entity();
	
	Entity(SDL_Surface* surface, SDL_Renderer *renderer);
	
	~Entity();
	
	void setBackground(Background *bg);
	
	inline void setStadingAnimated(bool value);
	
	void moveTo(int x, int y);
	
	virtual void movement();

	virtual bool render(SDL_Renderer *renderer);
	
	void release();
	
	bool renderObject(SDL_Renderer *renderer,
					  int X1, int Y1,
					  int X2, int Y2,
					  int W,  int H
					  );
	
	virtual void eventHandler(SDL_Event *event,Uint8 *keyStates);
	
};

#endif /* defined(__GameEngine__Entity__) */

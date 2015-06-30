//
//  Background.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Tile__
#define __GameEngine__Tile__

#include <stdio.h>
#include "SDLHeader.h"
#include "Entity.h"

class Entity;

class Background : public Object
{
	
protected:

public:
	vector<unique_ptr<Entity>> entities;

protected:
	
public:
	Background();
	

	
	void addEntity(Entity *entity);

	void addBackgroundObject(Background *object);
	
	void setBackgroundEnviromentValues( int *winWidth, int *winHeight,
										int *cameraX,  int *cameraY
									);
	
	bool render(SDL_Renderer *renderer);
	
	void release();
	

};


#endif /* defined(__GameEngine__Tile__) */

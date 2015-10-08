//
//  Background.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Background__
#define __GameEngine__Background__

#include <stdio.h>
#include "SDLHeader.h"
#include "EntityList.h"

class Entity;

class Background : public Object
{
	
protected:

public:
	vector<unique_ptr<Entity>> entities;
	EntityList tempEntities;
protected:
	
public:
	Background();
	
	~Background();
	
	void addEntity(Entity *entity);

	void addTemporalEntity(Entity *entity);
	
	void removeTemporalEntity(Entity *entity);
	
	void addBackgroundObject(Background *object);
	
	void setEnvironmentValues(int *winWidth, int *winHeight,
							  int *cameraX,  int *cameraY   );
	
	void loop();
	
	bool render(SDL_Renderer *renderer);
	
	void release();
	

};


#endif /* defined(__GameEngine__Background__) */

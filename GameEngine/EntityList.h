//
//  EntityList.h
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 7/22/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__EntityList__
#define __GameEngine__EntityList__

#include <stdio.h>
#include "Entity.h"

class EntityList
{
	
private:
	Entity *entity;
	EntityList *next;
	EntityList *previous;
	
public:
	EntityList();
	
	void pushFront(Entity *entity);
	
	void remove(Entity *entity);
	
	bool render(SDL_Renderer *renderer);
	
	void loop();
};
#endif /* defined(__GameEngine__EntityList__) */

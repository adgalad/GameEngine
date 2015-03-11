//
//  Tile.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/9/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Tile__
#define __GameEngine__Tile__

#include <stdio.h>
#include "Object.h"
class Tile : public Object
{
	vector<unique_ptr<Object>> objects;
	
	Tile();
	
	void addObject(Object *object);
	
	bool render(SDL_Surface *surface);
	
	void release();
};


#endif /* defined(__GameEngine__Tile__) */

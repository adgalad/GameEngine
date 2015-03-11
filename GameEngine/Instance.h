//
//  Instance.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/6/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Instance__
#define __GameEngine__Instance__

#include "Tile.h"
#include <string>

class Instance
{
protected:
	std::vector<std::vector<Tile>> tiles;
	int tileSize;
	int width;
	int height;
	
public:
	
protected:
	
public:
	
	Instance();
	Instance(FILE *file);
	Instance(std::string fileName);
	
	bool loadFile(FILE *file);
	bool render();
};

#endif /* defined(__GameEngine__Instance__) */

//
//  GameLoader.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__GameLoader__
#define __GameEngine__GameLoader__

#include <cstdio>
#include <cstdlib>
#include "SDLHeader.h"

using namespace std;

class GameLoader
{
public:
	GameLoader();

	bool loadParameters(string file);
	
};




#endif /* defined(__GameEngine__GameLoader__) */

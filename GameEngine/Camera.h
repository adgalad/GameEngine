//
//  Camera.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Camera__
#define __GameEngine__Camera__

#include <stdio.h>
#include "SDLHeader.h"

class Camera
{
protected:


	
public:
	Camera();
	
	void release();
	
	bool render(SDL_Surface *src, SDL_Surface *dest,int X, int Y, int W, int H);
	
};



#endif /* defined(__GameEngine__Camera__) */

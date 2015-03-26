//
//  Camera.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/13/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Camera.h"

Camera::Camera()
{
	
}



void Camera::release()
{
	
}

bool Camera::render(SDL_Surface *src, SDL_Surface *dest,int X, int Y, int W, int H)
{
	if (src == NULL || dest == NULL)
	{
		fprintf(stderr,"Camera::render SDL_Surface is NULL pointer\n");
		return false;
	}

	SDL_Rect *destRectangle= new SDL_Rect();
	
	destRectangle->x = 0;
	destRectangle->y = 0;
	
	SDL_Rect *srcRectangle= new SDL_Rect();
	

	srcRectangle->x = X-W/2;
	srcRectangle->y = Y-H/2;
	srcRectangle->w = W;
	srcRectangle->h = H;
	SDL_BlitSurface(
					src,
					srcRectangle,
					dest,
					destRectangle
					);
	SDL_FillRect(src, NULL, 0x000000);
	return true;
}





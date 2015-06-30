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

bool Camera::render(SDL_Renderer *renderer, SDL_Surface* destSurface,int X, int Y, int W, int H)
{
	if (renderer == NULL or destSurface == NULL)
	{
		fprintf(stderr,"Camera::render Surface is NULL pointer\n");
		return false;
	}

	SDL_Rect *destRectangle= new SDL_Rect();
	
	destRectangle->x = 0;
	destRectangle->y = 0;
	
	SDL_Rect *srcRectangle= new SDL_Rect();
	

	srcRectangle->x = X;
	srcRectangle->y = Y;
	srcRectangle->w = W;
	srcRectangle->h = H;
//	SDL_BlitSurface(
//					srcSurface,
//					srcRectangle,
//					destSurface,
//					destRectangle
//					);

	return true;
}





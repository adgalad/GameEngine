//
//  Object.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Object__
#define __GameEngine__Object__

#include <stdio.h>
#include <vector>
#include "SDLHeader.h"
#include "ObjectAction.h"

using namespace std;

class Instance;

class Object
{
	
/** Object Attributes **/
protected:
	SDL_Surface *objectSurface;
	Instance *instance; // Every object have its own instance
	int X, Y;
	int columns, rows;
	int width, height;
	int animated;
	int currentFrameX, currentFrameY;
	
public:
	vector<unique_ptr<ObjectAction>> action;

	
/** Object Functions **/

protected:
	
public:
	Object();
	
	Object(SDL_Surface *surface);
	
	Object(SDL_Surface *surface,
				   int  columns = 0,
		           int  rows    = 0,
		           int  width   = 0,
		           int  height  = 0
		   );
	
		/* SET FUNCTIONS */
	bool setCurrentFrame(int positionX, int positionY);
	
	void setAnimated(bool value);

		/* GET FUNSTIONS */

	int getCurrentFrameX();
	
	int getCurentFrameY();
	
	void addAction(ObjectAction *action);
	
	bool renderObject(SDL_Surface *surface,int X, int Y);
	
	bool renderObject(SDL_Surface *surface,
					  int X1,    int Y1,
					  int X2,    int Y2,
					  int width, int height
					);
	
	bool render(SDL_Surface *surface);
	
	bool loadImage(char* file);
	
	bool makeTransparent(int R, int G, int B);
	
	/* DESTRUCTOR */
	void release();
};

#endif /* defined(__GameEngine__Object__) */

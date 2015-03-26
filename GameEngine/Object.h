//
//  Object.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__Object__
#define __GameEngine__Object__

#include <memory.h>
#include <stdio.h>
#include <vector>
#include "SDLHeader.h"
#include "ObjectAction.h"


using namespace std;



class Object
{
		/* * * * * * * * */
		/*  ATTRIBUTES   */
		/* * * * * * * * */
	
public:
	vector<unique_ptr<ObjectAction>> action;
	SDL_TimerID timer;
	int         columns, rows;
	int         currentFrameX, currentFrameY;
	bool        animated;
	bool		isSprite;
	bool        verticalAnimation;

public:
	SDL_Surface *surface;
	int  X, Y;
	int  width, height;
	
	
		/* * * * * * * */
		/*  FUNCTIONS  */
		/* * * * * * * */
protected:
	
public:
		/* CONSTRUCTORS */
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
	
	void setAnimate(int columns, int rows);
	
	void setInstance(Instance *instance);

		/* GET FUNSTIONS */

	int  getCurrentFrameX();
	
	int  getCurentFrameY();
	
	void addAction(ObjectAction *action);
	
		/* CLASS FUNCTIONS */
	
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

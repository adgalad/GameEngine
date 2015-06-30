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
	bool		isStatic;
	bool        verticalAnimation;
	static int	_id;

public:
	SDL_Texture* texture;
	int  X, Y;
	int  width, height;
	int  *cameraX,  *cameraY;
	int  *winWidth, *winHeight;
	int  id;
	
	
		/* * * * * * * */
		/*  FUNCTIONS  */
		/* * * * * * * */
protected:
	
public:
		/* CONSTRUCTORS */
	Object();
	
	Object(SDL_Surface *surface, SDL_Renderer *renderer);
	
	Object(SDL_Surface *texture);
	
		/* SET FUNCTIONS */
	void setStatic(bool value);
	
	bool setCurrentFrame(int positionX, int positionY);
	
	void setAnimated(bool value);
	
	void setAnimateValues(int columns, int rows);
	
	void setInstance(Instance *instance);
	
	void setEnvironmentValues(int *winWidth, int*winHeight,
							  int*cameraX, int*cameraY
							  );

		/* GET FUNSTIONS */

	int  getCurrentFrameX();
	
	int  getCurentFrameY();
	
	void addAction(ObjectAction *action);
	
		/* CLASS FUNCTIONS */
	
	bool renderObject(SDL_Renderer *renderer,int X, int Y);
	
	bool renderObject(SDL_Renderer *renderer,
					  int X1,    int Y1,
					  int X2,    int Y2,
					  int width, int height
					);
	
	virtual bool render(SDL_Renderer *renderer);
	
	bool loadImage(string file, SDL_Renderer *renderer);
	
	bool makeTransparent(int R, int G, int B);

	
	
		/* DESTRUCTOR */
	void release();
	
};

#endif /* defined(__GameEngine__Object__) */

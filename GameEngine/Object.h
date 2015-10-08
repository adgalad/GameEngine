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

	SDL_TimerID timer;
	static int	_id;

public:
	int  X, Y;
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

	
		/* DESTRUCTOR */
	~Object();
	
		/* SET FUNCTIONS */
	
	void setEnvironmentValues(int *winWidth, int*winHeight,
							  int*cameraX, int*cameraY
							  );

		/* GET FUNSTIONS */

	void addAction(ObjectAction *action);
	
		/* CLASS FUNCTIONS */
	

	
	virtual bool render();
	

	

	
};

#endif /* defined(__GameEngine__Object__) */

//
//  ObjectAccion.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__ObjectAccion__
#define __GameEngine__ObjectAccion__

#include "SDLHeader.h"

class ObjectAction
{
	/** ATTRIBUTES */
protected:

public:
	
	
	/** FUNCTIONS **/
protected:

public:
	ObjectAction();
	virtual bool doAction();
};


class Move : public ObjectAction
{
public:
	Move()
	{
		
	}
	
	bool doAction();
	bool doAction(int h)
	{
		printf("%d -- hola\n",h);
		return true;
	};
 	void f()
	{
		printf("hola amigo\n");
	}
	
};

#endif /* defined(__GameEngine__ObjectAccion__) */

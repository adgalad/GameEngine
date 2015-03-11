//
//  main.cpp
//  Game_Ing_Software
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include <iostream>
#include "Object.h"

void hola(ObjectAction a)
{
	printf("hola");
	a.doAction();
}
int SDL_main(int argc, char **argv)
{
	Object obj;
	ObjectAction a1,a2;
	Move a3,a4;
	obj.addAction(&a1);
	obj.addAction(&a3);
	obj.addAction(&a2);
	obj.addAction(&a4);
	for (int i =0 ;i<obj.action.size() ; i++)
	{
		obj.action[i]->doAction();
	}

	obj.release();
    return 0;
}

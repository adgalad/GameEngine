//
//  ObjectAccion.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "ObjectAction.h"


ObjectAction::ObjectAction()
{
	
}
bool ObjectAction::doAction()
{
	printf("ObjectAction\n");
	return true;
};

bool Move::doAction()
{
	printf("Move\n");
	return true;
};

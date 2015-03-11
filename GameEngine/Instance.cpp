//
//  Instance.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/6/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "Instance.h"

Instance::Instance()
{
	
}
Instance::Instance(FILE *file)
{
	
}
Instance::Instance(std::string fileName)
{
	FILE *file = fopen(&fileName[0], "r");
}

bool loadFile(FILE *file);
bool render();
//
//  GameLoader.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "GameLoader.h"

bool GameLoader::loadParameters(string str)
{
	FILE *file = fopen(str.c_str(), "r");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR GameLoader::loadParameters(std::string)) Couldn't open the file %s\n",str.c_str());
	}
	char *parameter   = (char*)malloc(100);
	char *valueString = (char*)malloc(100);
	
	int nline = 0;
	while(fscanf(file, "%s =",parameter)!=EOF)
	{

		if (strcmp(parameter, "maxWalkVelocityX"))
		{
			fscanf(file, " %f\n",&maxWalkVelocityX);
			printf("%f\n",maxWalkVelocityX);
		}
		else if (strcmp(parameter, "maxWalkVelocityY"))
		{
			fscanf(file, "%f\n",&maxWalkVelocityY);
			printf("%f\n",maxWalkVelocityY);
		}
		else if(strcmp(parameter, "jumpAceleration"))
		{
			fscanf(file, "%f\n",&jumpAcceleration);
			printf("%f\n",jumpAcceleration);
		}
		else if(strcmp(parameter, "gravityAceleration"))
		{
			fscanf(file, "%f\n",&gravtiyAcceleration);
			printf("%f\n",gravtiyAcceleration);
		}
		else
		{
			fprintf(stderr, "ERROR GameLoader::loadParameters(std::string) at file %s line %d. Can't find parameter %s",&str[0],nline,parameter);
		}
		nline++;
	}
	
	free(parameter);
	free(valueString);
	
	return true;
}

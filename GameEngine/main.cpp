//
//  main.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//



#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "GameLoader.h"
#include "Camera.h"
#include "TextEntity.h"
std::string BASE_PATH_RESOURCE = "../../../../Resource/";
std::string BASE_PATH_SOURCE   = "../../../../GameEngine/";
std::string BASE_PATH_PROJECT  = "../../../../";

int main(int argc, char *argv[])
{

	Game *game = GameLoader::loadXML((char*)"/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngine/setup.xml");

	if(game != NULL)
	{
		game->run();
		game->release();
	}
	return 0;
}





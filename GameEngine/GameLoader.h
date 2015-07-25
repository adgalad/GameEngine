//
//  GameLoader.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__GameLoader__
#define __GameEngine__GameLoader__

#include <cstdio>
#include <cstdlib>
#include "SDLHeader.h"
#include "Game.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
using namespace std;

class GameLoader
{
public:
	GameLoader();

	static Game *loadXML(char *file);

private:
	
	static bool loadXMLTexture(pugi::xml_node *node, SDL_Renderer *renderer);
	
	static bool loadXMLEntity(pugi::xml_node *node, Game *game, Entity *entity);
	
	static bool loadXMLPlayer(pugi::xml_node *node, Game *game, Player *player);
	
	static bool loadXMLBackground(pugi::xml_node *node, Game *game);
	
};




#endif /* defined(__GameEngine__GameLoader__) */

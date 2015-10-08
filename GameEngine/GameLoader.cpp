//
//  GameLoader.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "GameLoader.h"




Game *GameLoader::loadXML(char *file)
{
	pugi::xml_document xmlDocument;
	Game *game = new Game();
	game->init();
	if (!xmlDocument.load_file(file)) {
		fprintf(stderr,"ERROR GameLoader::loadXML(char *) Couldn't load the file \n\t%s\n",file);
		return NULL;
	}
	
	pugi::xml_node gameNode;
	if (!(gameNode = xmlDocument.child("game")))
	{
		fprintf(stderr,"WARNING GameLoader::loadXML(char *) invalid XML document,first node should be \"game\" \n\t%s\n",file);
		return NULL;
	}
	if (!gameNode.attribute("cameraX").empty())
	{
		GameParameter::_cameraX = gameNode.attribute("cameraX").as_int();
	}
	if (!gameNode.attribute("cameraY").empty())
	{
		GameParameter::_cameraY = gameNode.attribute("cameraY").as_int();
	}
	if (!gameNode.attribute("fps").empty())
	{
		game->setMaxFPS(gameNode.attribute("fps").as_int());
	}
	if (!gameNode.attribute("jumpAcceleration").empty())
	{
		GameParameter::_jumpAcceleration = gameNode.attribute("jumpAcceleration").as_float();
	}
	if (!gameNode.attribute("maxSprintVelocityX" ).empty()) {
		GameParameter::_maxSprintVelocityX  = gameNode.attribute("maxSprintVelocityX").as_float();
	}
	if (!gameNode.attribute("maxSprintVelocityY" ).empty()) {
		GameParameter::_maxSprintVelocityY = gameNode.attribute("maxSprintVelocityY").as_float();
	}
	if (!gameNode.attribute("maxWalkVelocityX"   ).empty()) {
		GameParameter::_maxWalkVelocityX = gameNode.attribute("maxWalkVelocityX").as_float();
	}
	if (!gameNode.attribute("maxWalkVelocityY").empty()) {
		GameParameter::_maxWalkVelocityY = gameNode.attribute("maxWalkVelocityY").as_float();
	}
	if (!gameNode.attribute("gravtiyAcceleration").empty()) {
		GameParameter::_gravtiyAcceleration = gameNode.attribute("gravtiyAcceleration").as_float();
	}
	for (pugi::xml_node node = gameNode.first_child(); node; node = node.next_sibling()) {
		if (!strcmp(node.name(),"texture"))
		{
			GameLoader::loadXMLTexture(&node, game->renderer);
		}
		else if (!strcmp(node.name(),"background"))
		{
			GameLoader::loadXMLBackground(&node, game);
		}
	}
	
	return game;
}

bool GameLoader::loadXMLTexture(pugi::xml_node *node, SDL_Renderer *renderer)
{
	for (pugi::xml_node i = node->first_child(); i; i = i.next_sibling())
	{
		if (!strcmp(i.name(),"item"))
		{
			
			if(!i.attribute("path").empty())
			{
				TextureInfo *aux = new TextureInfo;
				aux->path = i.attribute("path").as_string();
				SDL_Surface *surface = IMG_Load(i.attribute("path").as_string());
				if (surface) {
					aux->SDLtexture = SDL_CreateTextureFromSurface(renderer,
																   surface
																);
				}
				if(!i.attribute("id").empty())
				{
					aux->_id = i.attribute("id").as_int();
				}
				else
				{
					fprintf(stderr,"WARNING GameLoader::loadXMLTexture(pugi::xml_node*, SDL_renderer*):\n  Trying to load item without id attribute.\n");
					delete aux;
					continue;
				}
				if(!i.attribute("name").empty())
				{
					aux->name = i.attribute("name").as_string();
				}
				GameParameter::_textures.addTexture(aux);
			}
			else
			{
				fprintf(stderr,"WARNING GameLoader::loadXMLTexture(pugi::xml_node*, SDL_renderer*):\n  Item without path to image. Item was not loaded.\n");
			}

		}
	}
	return true;
}

bool GameLoader::loadXMLBackground(pugi::xml_node *node, Game *game)
{
	Background *bg = new Background();
	game->addBackground(bg);
	
	if(!node->attribute("id").empty())
	{
		bg->loadTexture(GameParameter::_textures.getTextureById(node->attribute("id").as_int())->SDLtexture);
	}
	if(!node->attribute("static").empty())
	{
		bg->setStatic(node->attribute("static").as_bool());
	}
	if(!node->attribute("X").empty())
	{
		bg->X = node->attribute("X").as_int();
	}
	if(!node->attribute("Y").empty())
	{
		bg->Y = node->attribute("Y").as_int();
	}
	for (pugi::xml_node i = node->first_child(); i; i = i.next_sibling())
	{
		if (!strcmp(i.name(),"player"))
		{
			Player *player = new Player;
			GameLoader::loadXMLPlayer(&i, game, player);
			game->addPlayer(player);
		}
		else if (!strcmp(i.name(),"entity"))
		{
			Entity *entity = new Entity;
			GameLoader::loadXMLEntity(&i,game, entity);
			bg->addEntity(entity);
		}
	}
	return true;
}

bool GameLoader::loadXMLPlayer(pugi::xml_node *node, Game *game, Player *player)
{
	int c = 1, r = 1;
		// Load Surface
	if(!node->attribute("id").empty())
	{
		player->loadTexture(GameParameter::_textures.getTextureById(node->attribute("id").as_int())->SDLtexture);
	}
	
	if(!node->attribute("X").empty())
	{
		player->X = node->attribute("X").as_int();
	}
	
	if(!node->attribute("Y").empty())
	{
		player->Y = node->attribute("Y").as_int();
	}
	
	if(!node->attribute("velocityX").empty())
	{
		player->velocityX = node->attribute("velocityX").as_int();
	}
	
	if(!node->attribute("velocityY").empty())
	{
		player->velocityY = node->attribute("velocityY").as_int();
	}
	
	if(!node->attribute("animated").empty())
	{
		player->animated = node->attribute("animated").as_bool();
	}
	
	if(!node->attribute("animatedRow").empty())
	{
		r = node->attribute("animatedRow").as_int();
	}
	
	if(!node->attribute("animatedColumn").empty())
	{
		c = node->attribute("animatedColumn").as_int();
	}
	
	if(!node->attribute("standingAnimated").empty())
	{
		player->standingAnimated = node->attribute("standingAnimated").as_bool();
	}
	
	if(!node->attribute("verticalAnimation").empty())
	{
		player->verticalAnimation = node->attribute("verticalAnimation").as_bool();
	}
	
	if(!node->attribute("iscollision").empty())
	{
		player->iscollision = node->attribute("iscollision").as_bool();
	}
	
	player->setAnimateValues(c, r);
	pugi::xml_node nodeMap;
	if ((nodeMap = node->child("spriteMap"))!=NULL)
	{
		int j = 0;
		if(!player->verticalAnimation)
		{
			player->spriteMap = (int*) malloc(sizeof(int)*player->rows);
			
			for(pugi::xml_node i = nodeMap.first_child();
				i && j<player->rows;
				i = i.next_sibling()
				)
			{
				if (!strcmp(i.name(),"c"))
				{
					player->spriteMap[j++] = i.attribute("value").as_int();
				}
			}
		}
		else
		{
			player->spriteMap = (int*) malloc(sizeof(int)*player->columns);
			for(pugi::xml_node i = nodeMap.first_child();
				i && j < player->columns;
				i = i.next_sibling()
				)
			{
				if (!strcmp(i.name(),"c"))
				{
					player->spriteMap[j++] = i.attribute("value").as_int();
				}
			}
		}
		pugi::xml_node nodeControl;
		if ((nodeControl = nodeMap.child("control"))!=NULL)
		{
			const int n = 5;
			char words[n][10] = { "moveDown",
								  "moveUp",
								  "moveLeft",
								  "moveRight",
								  "standing"
								};
			int *pointerKey[n] = { &player->keyDown,
								   &player->keyUp,
				                   &player->keyLeft,
								   &player->keyRight,
								   &player->keyStanding
								};
			int *pointerPos[n] = {  &player->posDown,
									&player->posUp,
									&player->posLeft,
									&player->posRight,
									&player->posStanding
								};
			bool cond = true;
			for(pugi::xml_node i = nodeControl.first_child();
				i;
				i = i.next_sibling()
				)
			{
				for (int j = 0 ; j < n ; j++)
				{
					if (!strcmp(i.name(),words[j]) and
						!i.attribute("position").empty())
					{
						int pos = i.attribute("position").as_int();
						if(!i.attribute("key").empty())
						{
							const char *key = i.attribute("key").as_string();

							if (!strcmp(key,"left"))
							{
								printf("LEFT %d\n",pos);
								*pointerKey[j] = SDLK_LEFT;
							}
							else if(!strcmp(key,"down"))
							{
								printf("DOWN %d\n",pos);
								*pointerKey[j] = SDLK_DOWN;
							}
							else if(!strcmp(key,"right"))
							{
								printf("RIGHT %d\n",pos);
								*pointerKey[j] = SDLK_RIGHT;
							}
							else if(!strcmp(key,"up"))
							{
								printf("UP %d\n",pos);
								*pointerKey[j] = SDLK_UP;
							}
							else if(!strcmp(key,"space"))
							{
								printf("UP %d\n",pos);
								*pointerKey[j] = SDLK_SPACE;
							}
							else if (strlen(key) == 1)
							{
								*pointerKey[j] = key[0];
							}
							else
							{
								fprintf(stderr,"WARNING GameLoader::loadXMLPlayer(pugi::xml_node*, Game*, Player*): Unable to load key '%s' on %s",key,words[j]);
								cond = false;
								break;
							}
						}
						*pointerPos[j] = pos;
						cond = false;
						break;
					}
				}
				if (!cond)
				{
					cond = true;
					continue;
				}
				if (!strcmp(i.name(),"special"))
				{
					if(i.attribute("key"     ).empty() or
					   i.attribute("position").empty())
					{
						fprintf(stderr,"WARNING GameLoader::loadXMLPlayer(pugi::xml_node*, Game*, Player*):\nUnable to find key or position value when trying to add special action\n");
						continue;
					}
					
					const char *key = i.attribute("key").as_string();
					int         pos = i.attribute("position").as_int();
					if (!strcmp(key,"left"))
					{
						player->addAction(pos, SDLK_LEFT);
					}
					else if(!strcmp(key,"down"))
					{
						player->addAction(pos, SDLK_DOWN);
					}
					else if(!strcmp(key,"right"))
					{
						player->addAction(pos, SDLK_RIGHT);
					}
					else if(!strcmp(key,"up"))
					{
						player->addAction(pos, SDLK_UP);
					}
					else if(!strcmp(key,"space"))
					{
						player->addAction(pos, SDLK_SPACE);
					}
					else if (strlen(key) == 1)
					{
						player->addAction(pos, key[0]);
					}
					else
					{
						fprintf(stderr,"WARNING GameLoader::loadXMLPlayer(pugi::xml_node*, Game*, Player*): Unable to load key '%s' on special action",key);
						cond = false;
						break;
					}
				}
			}
		}
	}
	return true;
}

bool GameLoader::loadXMLEntity(pugi::xml_node *node, Game *game, Entity *entity)
{
	int c = 1, r = 1;
	// Load Surface
	if(!node->attribute("id").empty())
	{
		entity->loadTexture(GameParameter::_textures.getTextureById(node->attribute("id").as_int())->SDLtexture);
	}

	if(!node->attribute("X").empty())
	{
		entity->X = node->attribute("X").as_int();
	}

	if(!node->attribute("Y").empty())
	{
		entity->Y = node->attribute("Y").as_int();
	}

	if(!node->attribute("velocityX").empty())
	{
		entity->velocityX = node->attribute("velocityX").as_int();
	}

	if(!node->attribute("velocityY").empty())
	{
		entity->velocityY = node->attribute("velocityY").as_int();
	}
	
	if(!node->attribute("animated").empty())
	{
		entity->animated = node->attribute("animated").as_bool();
	}
	
	if(!node->attribute("animatedRow").empty())
	{
		r = node->attribute("animatedRow").as_int();
	}
	
	if(!node->attribute("animatedColumn").empty())
	{
		c = node->attribute("animatedColumn").as_int();
	}
	
	if(!node->attribute("standingAnimated").empty())
	{
		entity->standingAnimated = node->attribute("standingAnimated").as_bool();
	}
	
	if(!node->attribute("verticalAnimation").empty())
	{
		entity->verticalAnimation = node->attribute("verticalAnimation").as_bool();
	}
	
	if(!node->attribute("iscollision").empty())
	{
		entity->iscollision = node->attribute("iscollision").as_bool();
	}
	if(!node->attribute("static").empty())
	{
		entity->setStatic(node->attribute("static").as_bool());
	}
	entity->setAnimateValues(c, r);
	pugi::xml_node nodeMap;
	if ((nodeMap = node->child("spriteMap"))!=NULL) {
		int j = 0;
		if(!entity->verticalAnimation)
		{
			entity->spriteMap = (int*) malloc(sizeof(int)*entity->rows);
			for(pugi::xml_node i = nodeMap.first_child();
				i && j<entity->rows;
				i = i.next_sibling()
				)
			{
				if (!strcmp(i.name(),"c"))
				{
					entity->spriteMap[j++] = i.attribute("value").as_int();
				}
			}
		}
		else
		{
			entity->spriteMap = (int*) malloc(sizeof(int)*entity->columns);
			for(pugi::xml_node i = nodeMap.first_child();
				i && j < entity->columns;
				i = i.next_sibling()
				)
			{
				if (!strcmp(i.name(),"c"))
				{
					entity->spriteMap[j++] = i.attribute("value").as_int();
				}
			}
		}

	}
	return entity;
}

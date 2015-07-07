//
//  GameLoader.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/30/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "GameLoader.h"


TextureList _textures;
int	  _cameraX			   = 0;
int   _cameraY			   = 0;
float _jumpAcceleration	   = -50.0;
float _maxWalkVelocityX	   = 10.0;
float _maxWalkVelocityY    = 40.0;
float _maxSprintVelocityX  = 32.0;
float _maxSprintVelocityY  = 32.0;
float _gravtiyAcceleration = 9.8;


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
		_cameraX = gameNode.attribute("cameraX").as_int();
	}
	if (!gameNode.attribute("cameraY").empty())
	{
		_cameraY = gameNode.attribute("cameraY").as_int();
	}
	if (!gameNode.attribute("fps").empty())
	{
		game->setMaxFPS(gameNode.attribute("fps").as_int());
	}
	if (!gameNode.attribute("jumpAcceleration").empty())
	{
		_jumpAcceleration = gameNode.attribute("jumpAcceleration").as_float();
	}
	if (!gameNode.attribute("maxSprintVelocityX" ).empty()) {
		_maxSprintVelocityX  = gameNode.attribute("maxSprintVelocityX").as_float();
	}
	if (!gameNode.attribute("maxSprintVelocityY" ).empty()) {
		_maxSprintVelocityY = gameNode.attribute("maxSprintVelocityY").as_float();
	}
	if (!gameNode.attribute("maxWalkVelocityX"   ).empty()) {
		_maxWalkVelocityX = gameNode.attribute("maxWalkVelocityX").as_float();
	}
	if (!gameNode.attribute("maxWalkVelocityY").empty()) {
		_maxWalkVelocityY = gameNode.attribute("maxWalkVelocityY").as_float();
	}
	if (!gameNode.attribute("gravtiyAcceleration").empty()) {
		_gravtiyAcceleration = gameNode.attribute("gravtiyAcceleration").as_float();
	}
	for (pugi::xml_node node = gameNode.first_child(); node; node = node.next_sibling()) {
		if (!strcmp(node.name(),"surface"))
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
				_textures.addTexture(aux);
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
		bg->loadTexture(_textures.getTextureById(node->attribute("id").as_int())->SDLtexture);
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
			GameLoader::loadXMLEntity(&i, game, player);
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


bool GameLoader::loadXMLEntity(pugi::xml_node *node, Game *game, Entity *entity)
{
	int c = 1, r = 1;
	// Load Surface
	if(!node->attribute("id").empty())
	{
		entity->loadTexture(_textures.getTextureById(node->attribute("id").as_int())->SDLtexture);
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

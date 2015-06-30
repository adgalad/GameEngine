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

#include "Game.h"
#include "Camera.h"
#include "TextEntity.h"
std::string BASE_PATH_RESOURCE = "../../../../Resource/";
std::string BASE_PATH_SOURCE   = "../../../../GameEngine/";
std::string BASE_PATH_PROJECT  = "../../../../";

int main(int argc, char *argv[])
{
	SDL_Surface *wall   = IMG_Load(&(BASE_PATH_RESOURCE+"wall.jpg")[0]),
				*ground = IMG_Load(&(BASE_PATH_RESOURCE+"ground.jpg")[0]),
				*tree   = IMG_Load(&(BASE_PATH_RESOURCE+"Tree.png")[0]);
	Game game = Game();
	
	if(game.init())
	{
		game.loadParameterValues(BASE_PATH_PROJECT+"setup.ge");
		game.setMaxFPS(18);
		
		Background *bg = new Background();
		bg->loadImage("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEngine/Resource/bg.png",game.renderer);
		bg->setStatic(true);
		game.addBackground(bg);
		
		
		Player *player = new Player();
		player->loadImage("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEngine/Resource/yoshi.png",game.renderer);
		
		player->X = 400;
		player->Y = 800;
		player->velocityY = 0;
		player->velocityX = 0;
		player->setAnimated(true);
		player->setAnimateValues(2, 8);
		player->iscollision = true;
		player->movable = true;
		game.addPlayer(player);
		
		TextEntity *text = new TextEntity;
		text->setColor();
		text->setFont("/Library/Fonts/Arial Bold.ttf", 28);
		text->setMessage(game.renderer, "Player %d",2);
		text->X = game.width/2;
		text->Y = game.height/2-50;
		text->setStatic(true);
		text->iscollision = false;

		bg->addEntity(text);
		
		
		Entity *entity = new Entity(wall,game.renderer);
		entity->X = 150;
		entity->Y = 500;
		bg->addEntity(entity);
		
		Entity *entity2 = new Entity(wall,game.renderer);
		entity2->X = 1900;
		entity2->Y = 500;
		bg->addEntity(entity2);
		
		
		Entity *entity3 = new Entity(ground,game.renderer);
		entity3->X = 1150;
		entity3->Y = 900;
		bg->addEntity(entity3);
		
		Entity *entity7 = new Entity(ground,game.renderer);
		entity7->X = 400;
		entity7->Y = 900;
		bg->addEntity(entity7);
		
		Entity *entity4 = new Entity(tree,game.renderer);
		entity4->iscollision = false;
		entity4->X = 900;
		entity4->Y = 650;
		bg->addEntity(entity4);
		
		Entity *entity5 = new Entity(tree,game.renderer);
		entity5->iscollision = false;
		entity5->X = 500;
		entity5->Y = 650;
		bg->addEntity(entity5);
		
		Entity *entity6 = new Entity(tree,game.renderer);

		entity6->iscollision = false;
		entity6->X = 1200;
		entity6->Y = 650;
		bg->addEntity(entity6);
		
		
		game.run();
		game.release();
	}
	return 0;
}

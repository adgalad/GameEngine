//
//  main.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "Camera.h"
#include "Entity.h"

int SDL_main(int argc, char **argv)
{
	SDL_Surface *s = IMG_Load("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEngine/Resource/ground.png");


	Game game = Game();
	game.init();
	game.setMaxFPS(24);
	Background bg = Background();
	bg.loadImage((char *)"/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEngine/Resource/bg.jpg");
	game.addBackground(&bg);
	
	Player *entity1 = new Player();
	entity1->loadImage((char*)"/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Juego_SDL/GameEngine/Resource/yoshi.png");
	entity1->setAnimate(2,8);
	
	entity1->X = 100;
	entity1->Y = 110;
	entity1->movable = true;
	game.addPlayer(entity1);
	
	Entity *entity = new Entity(s);
	entity->X = 100;
	entity->Y = 184;
	bg.addEntity(entity);
	
	Entity *entity3 = new Entity(s);
	entity3->X = 520;
	entity3->Y = 100;
	bg.addEntity(entity3);


	game.run();
	game.release();

	
    return 0;
}

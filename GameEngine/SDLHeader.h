//
//  SDLHeader.h
//  GameEngine
//
//  Created by Carlos Spaggiari on 3/5/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef GameEngine_SDLHeader_h
#define GameEngine_SDLHeader_h

#include <SDL2/SDL.h>
#include <string>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

class Game;
class GameLoader;
class Instance;
class Object;
class Background;
class Entity;
class Player;
class Camera;

static float jumpAcceleration	 = -50.0;
static float maxWalkVelocityX	 = 10.0;
static float maxWalkVelocityY    = 40.0;
static float maxSprintVelocityX  = 32.0;
static float maxSprintVelocityY  = 32.0;
static float gravtiyAcceleration = 9.8;





#endif

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
#include <vector>
#include <list>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

class Game;
class GameLoader;
class Instance;
class Object;
class Background;
class Entity;
class TemporalEntity;
class TextEntity;
class Player;
class Camera;

#define RIGHT_DIR	0
#define LEFT_DIR	1
#define UP_DIR		2
#define DOWN_DIR	3

class TextureInfo
{
public:
	string name;
	string path;
	int    _id;
	SDL_Texture *SDLtexture;
	
	TextureInfo(){
		SDLtexture = NULL;
	}
	
	~TextureInfo()
	{
		SDL_free(SDLtexture);
	}
};

class TextureList
{
private:
	vector<TextureInfo*> textures;
	
public:
	TextureList();
	
	void release();
	
	bool addTexture(TextureInfo *ti);
	
	TextureInfo* getTextureById(int _id);
	
	TextureInfo* getTextureByName(const char *name);
};


class GameParameter
{
public:
	static TextureList	_textures;
	static int			_cameraX;
	static int			_cameraY;
	static float		_jumpAcceleration;
	static float		_maxWalkVelocityX;
	static float		_maxWalkVelocityY;
	static float		_maxSprintVelocityX;
	static float		_maxSprintVelocityY;
	static float		_gravtiyAcceleration;
};
#endif

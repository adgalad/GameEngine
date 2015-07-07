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
class Player;
class Camera;

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
};


extern TextureList	_textures;
extern int			_cameraX;
extern int			_cameraY;
extern float		_jumpAcceleration;
extern float		_maxWalkVelocityX;
extern float		_maxWalkVelocityY;
extern float		_maxSprintVelocityX;
extern float		_maxSprintVelocityY;
extern float		_gravtiyAcceleration;

#endif

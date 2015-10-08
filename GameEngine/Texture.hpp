//
//  Texture.hpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 10/7/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SDLHeader.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Point
{
public:
	int x;
	int y;

	Point(){
		x = 0;
		y = 0;
	}
};

class Sprite
{
private:
	static int	_id;
	static SDL_Renderer* renderer;
	
	int			id;
	string		name;
	string		path;

	int		columns;
	int		rows;
	int		width;
	int		height;
	bool	animated;
	bool	isStatic;
	bool	verticalAnimation;
	int		direcction;
	Point	currentFrame;
	
	int*					spriteMap;
	SDL_Texture*			spriteTexture;
	map<string, Point>		spritePosition;


	
	/* FUNCTIONS */
	
public:
	
	/* CONSTRUCTOR AND DESTRUCTOR */
	Sprite();
	
	~Sprite();
	
	
	/* STATIC METHODS */
	inline static void createRenderer(SDL_Window *window);
	
	inline static void renderPresent();
	
	
	/* PUBLIC METHODS */
	void setColumnsAndRows(int columns, int rows);
	
	void setName(string name);
	
	bool loadImage(string file, SDL_Renderer *renderer);
	
	bool render(int X, int Y, int* cameraX = NULL, int* cameraY = NULL);
	
	
	/* PRIVATE METHODS */
private:
	bool renderTexture(int X, int Y);
	
	bool renderTexture(int X1, int Y1, int X2, int Y2, int W, int H);
};

#endif /* Texture_hpp */


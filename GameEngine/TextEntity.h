//
//  TextEntity.h
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 6/29/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__TextEntity__
#define __GameEngine__TextEntity__

#include <stdio.h>
#include "Entity.h"

class TextEntity : public Entity
{
public:
	TTF_Font *font;
	SDL_Color color;
	
	TextEntity();
	
	bool setColor(Uint8 R = 0, Uint8 B = 0, Uint8 G = 0, Uint8 A = 0);
	
	bool setFont(char *font, int size);
	
	bool setMessage(SDL_Renderer *renderer, const char *message, ...);
	
};

#endif /* defined(__GameEngine__TextEntity__) */

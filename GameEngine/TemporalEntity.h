//
//  TemporalEntity.h
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 7/20/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#ifndef __GameEngine__TemporalEntity__
#define __GameEngine__TemporalEntity__

#include <stdio.h>
#include "SDLHeader.h"
#include "Entity.h"


class TemporalEntity : public Entity
{
	friend class Background;
protected:
	unsigned int timeUntilDisappear;
	unsigned int beginTime;
	bool disappearOnColiision;
	
	
	
	
	// FUNCTIONS
	
protected:
	bool collision();
	
public:
	TemporalEntity();
	
	void setTime(unsigned int miliseconds);
	
	bool render(SDL_Renderer *renderer);
	
	void setDisappearOnColission(bool value);

	
	
};


#endif /* defined(__GameEngine__TemporalEntity__) */

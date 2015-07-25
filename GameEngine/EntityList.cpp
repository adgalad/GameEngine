//
//  EntityList.cpp
//  GameEngine
//
//  Created by Carlos Spaggiari Roa on 7/22/15.
//  Copyright (c) 2015 ARSC. All rights reserved.
//

#include "EntityList.h"

EntityList::EntityList()
{
	this->entity	= NULL;
	this->next		= NULL;
	this->previous	= NULL;
}

void EntityList::pushFront(Entity *entity)
{
	
	if (this->entity == NULL)
	{
		this->entity = entity;
	}
	else
	{
		EntityList *newNode  = new EntityList;
		newNode->entity		 = this->entity;
		newNode->next		 = this->next;
		newNode->previous	 = this;
		if (this->next)
			this->next->previous = newNode;
		this->entity		 = entity;
		this->next			 = newNode;
	}
}

void EntityList::remove(Entity *entity)
{
	EntityList *node = this;
	while (node != NULL)
	{
		if(node->entity->id == entity->id)
		{
			if (node->previous)
			{
				node->previous->next = node->next;
				if (node->next)
					node->next->previous = node->previous;
				node->entity->release();
				free(node);
			}
			else
			{
				node->entity->release();
				
				if (node->next)
				{
					node->entity = node->next->entity;
					node->next = node->next->next;
				}
				else
				{
					node->entity = NULL;
				}
			}
			return;
		}
		node = node->next;
	}
}

bool EntityList::render(SDL_Renderer *renderer)
{
	EntityList *node = this;
	bool returnValue = true;
	
	if (node->entity != NULL)
		while(node != NULL)
		{
			
			node->entity->render(renderer);
			node = node->next;
		}
	
	return returnValue;
}

void EntityList::loop()
{
	EntityList *node = this;
	EntityList *aux  = NULL;
	if (node->entity != NULL)
	while(node != NULL)
	{
		node->entity->movement();
		if (node->entity->collision())
		{
			aux = node->next;
			if (node->previous)
			{
				node->previous->next = node->next;
				if (node->next)
					node->next->previous = node->previous;
				node->entity->release();
				free(node);
			}
			else
			{
				node->entity->release();
				
				if (node->next)
				{
					node->entity = node->next->entity;
					node->next = node->next->next;
				}
				else
				{
					node->entity = NULL;
				}
				
			}
			node = aux;
		}
		else
		{
			node = node->next;
		}
	}
}
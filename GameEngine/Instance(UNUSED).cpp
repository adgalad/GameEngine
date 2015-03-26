////
////  Instance.cpp
////  GameEngine
////
////  Created by Carlos Spaggiari on 3/6/15.
////  Copyright (c) 2015 ARSC. All rights reserved.
////
//
//#include "Instance(UNUSED).h"
//
//Instance::Instance()
//{
//	
//}
//Instance::Instance(FILE *file)
//{
//	
//}
//Instance::Instance(std::string fileName)
//{
//	FILE *file = fopen(&fileName[0], "r");
//}
//
//bool Instance::loadFile(FILE *file)
//{
//	
//	return true;
//}
//
//int Instance::setWidth(int width)
//{
//	this->width = width;
//	return this->width;
//}
//
//int Instance::setHeight(int height)
//{
//	this->height = height;
//	return this->height;
//}
//
//void Instance::addBackground(Background *bg)
//{
//	bg->setInstance(this);
//	this->background.push_back(unique_ptr<Background>(bg));
//}
//
//bool Instance::render(SDL_Surface *surface)
//{
//	for (int i=0; i < this->background.size(); i++) {
//		this->background[i]->render(surface);
//	}
//	return true;
//}
//
//void Instance::release()
//{
//	for (int i=0; i < this->background.size(); i++) {
//		this->background[i]->release();
//		this->background[i].release();
//	}
//}
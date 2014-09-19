/*
*	System.cpp
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "System.h"

static System* sharedSystem = nullptr;

System::System(){}

System::~System(){}

System* System::getInstance()
{
	if (sharedSystem == nullptr) {
		sharedSystem = new System;
		if (!sharedSystem->init()) {
			cerr << "Failed to initialize management system!" << endl;
			delete sharedSystem;
			return NULL;
		}
	}

	return sharedSystem;
}

bool System::init()
{
	return true;
}

void System::destroyInstance()
{
	if (sharedSystem != nullptr) {
		delete sharedSystem;
		sharedSystem = nullptr;
	}
	return;
}


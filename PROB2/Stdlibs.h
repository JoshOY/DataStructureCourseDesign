/*
*	stdlibs.h
*
*	Created by 1352847 JoshOY on 14-10-17
*	Copyright (c) 2014 JoshOY. All rights reserved.
*
*	Note: please DO NOT USE Viusal C++ 6.0 TO COMPILE. (It's a trash IDE)
*/

#ifndef __1352847_STDLIBS_H__
#define __1352847_STDLIBS_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <set>

using namespace std;

typedef struct _Node{
	int id;
	_Node* next;
} Node;

const regex UINT_PATTERN("[1-9](([0-9])*)");


#endif

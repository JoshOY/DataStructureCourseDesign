/*
*	stdlibs.h
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*
*	Note: please DO NOT USE Viusal C++ 6.0 TO COMPILE. (It's a trash IDE)
*/

#ifndef __1352847_STDLIBS_H__
#define __1352847_STDLIBS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>	// C++11
#include <map>

using namespace std;

const regex ID_PATTERN("[0-9]+");
const regex INPUT_PATTERN("[12345]");
const regex GENDER_PATTERN("[MFmf]");
const regex AGE_PATTERN("[1-9](([0-9])*)");

#endif
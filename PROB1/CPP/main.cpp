/*
*	main.cpp
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "System.h"

int main(int argc, char* argv[]) 
{
	System::getInstance()->run();
	System::destroyInstance();
	return 0;
}
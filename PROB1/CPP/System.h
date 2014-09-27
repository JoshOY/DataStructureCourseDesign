/*
*	System.h
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#ifndef __1352847_SYSTEM_H__
#define __1352847_SYSTEM_H__

#include "Student.h"

class System 
{
public:

	System();

	~System();

	static System* getInstance();

	virtual bool init();

	static void destroyInstance();

	void run();                        

	

private:

	static System* sharedSystem;

	list<Student> studentsList;

	int inputCommand();

	bool insert();

	bool remove();

	bool find();

	bool change();

	bool statistics();
};

#endif

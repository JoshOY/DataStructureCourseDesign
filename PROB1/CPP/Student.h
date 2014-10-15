/*
*	Student.h
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#ifndef __1352847_STUDENTS_H__
#define __1352847_STUDENTS_H__

#include "stdlibs.h"

const bool MALE = true;
const bool FEMALE = false;

class Student 
{
public:

	/* Constructor & destructor */

	Student();

	Student(long long _id, string _name, bool _gender, unsigned int _age, string _applyFor);

	~Student();

	/* get&set functions */

	long long getId() const;

	string getName() const;

	bool getGender() const;

	unsigned int getAge() const;

	string getApplyFor() const;

	bool setId(const long long _id);

	bool setName(const string& _name);

	bool setGender(const bool _gender);

	bool setAge(const unsigned int _age);

	bool setApplyFor(const string& _applyFor);

	/* Override < operation */
	int operator<(const Student& _comparing) {
		if (this->id < _comparing.id) {
			return 1;
		}
		else {
			return 0;
		}
	}

private:

	long long id;

	string name;

	bool gender;

	unsigned int age;

	string applyFor;
};

#endif

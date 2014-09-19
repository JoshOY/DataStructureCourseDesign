/*
*	Student.cpp
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "Student.h"

/* Default constructor and destructor */
Student::Student() {}

Student::Student(long long _id, string _name, bool _gender, unsigned int _age, string _applyFor): 
                 id(_id),
				 name(_name),
				 gender(_gender),
				 age(_age),
				 applyFor(_applyFor) {}


Student::~Student(){}

long long Student::getId() const
{
	return this->id;
}

string Student::getName() const
{
	return this->name;
}

bool Student::getGender() const
{
	return this->gender;
}

unsigned int Student::getAge() const
{
	return this->age;
}

string Student::getApplyFor() const
{
	return this->applyFor;
}

bool Student::setId(const long long _id)
{
	this->id = _id;
	return true;
}

bool Student::setName(const string& _name)
{
	this->name = _name;
	return true;
}

bool Student::setGender(const bool _gender)
{
	this->gender = _gender;
	return true;
}

bool Student::setAge(const unsigned int _age) 
{
	this->age = _age;
	return true;
}

bool Student::setApplyFor(const string& _applyFor) 
{
	this->applyFor = _applyFor;
	return true;
}
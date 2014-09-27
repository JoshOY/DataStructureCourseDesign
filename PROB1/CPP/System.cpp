/*
*	System.cpp
*
*	Created by 1352847 JoshOY on 14-9-19
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "System.h"

System* System::sharedSystem = nullptr;

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
	cout << "请先建立考生信息系统！" << endl;
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

void System::run()
{
	while (true) {
		inputCommand();
	}
}

int System::inputCommand()
{
	string input;
	stringstream ss;
	
	while (true) {
		std::cout << "请输入您的操作：1-插入 2-删除 3-查找 4-修改 5-统计：";
		std::cin >> input;
		if (regex_match(input, INPUT_PATTERN)) {
			break;
		} else {
			std::cout << "非法输入格式。请确定输入是否正确。" << endl;
		}
	}

	int operationSelect;
	ss << input;
	ss >> operationSelect;


	switch (operationSelect) {
	case 1:
		return insert();
		break;
	case 2:
		return remove();
		break;
	case 3:
		return find();
		break;
	case 4:
		return change();
		break;
	case 5:
		return statistics();
		break;
	}
}

bool System::insert()
{
	string input;
	int insertNum;
	while (true) {
		std::cout << "请输入考生人数（0为取消操作）：";
		std::cin >> input;

		if (!regex_match(input, ID_PATTERN)) {
			std::cout << "输入不合法，请重新输入。" << endl;
		}
		else {
			break;
		}
	}
	stringstream ss;
	ss << input;
	ss >> insertNum;
	if (insertNum == 0) {
		cout << "操作取消。" << endl;
	}
	else {
		for (int n = 1; n <= insertNum; ++n) {
			std::cout << "请输入考生的考号、姓名、性别(M/F)、年龄以及报考类别（之间用空格隔开）：" << endl;
			string inputId, inputName, inputGender, inputAge, inputApplyFor;
			std::cin >> inputId >> inputName >> inputGender >> inputAge >> inputApplyFor;

			if (!regex_match(inputId, ID_PATTERN)) {
				std::cout << "考号格式不正确。" << endl;
				--n;
				continue;
			}
			if (!regex_match(inputGender, GENDER_PATTERN)) {
				std::cout << "性别格式不正确（输入F代表性别女， M代表性别男）。" << endl;
				--n;
				continue;
			}
			if (!regex_match(inputAge, AGE_PATTERN)) {
				std::cout << "年龄格式不正确。" << endl;
				--n;
				continue;
			}

			int idInit;
			bool genderInit;
			int ageInit;

			ss.clear();
			ss << inputId;
			ss >> idInit;
			ss.clear();
			ss << inputAge;
			ss >> ageInit;
			if ((inputGender == "M") || (inputGender == "m")) {
				genderInit = MALE;
			} else {
				genderInit = FEMALE;
			}

			this->studentsList.push_back(Student(idInit, inputName, genderInit, ageInit, inputApplyFor));
		}
	}
	return true;
}

bool System::remove()
{
	return true;
}

bool System::change()
{
	return true;
}

bool System::find()
{
	return true;
}

bool System::statistics()
{
	return true;
}
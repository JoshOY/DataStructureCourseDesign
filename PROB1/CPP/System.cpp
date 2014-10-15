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
	while (inputCommand()) {
		;
	}
}

int System::inputCommand()
{
	string input;
	stringstream ss;
	bool shouldExit = false;
	
	while (true) {
		std::cout << "请输入您的操作：1-插入 2-删除 3-查找 4-修改 5-统计：";
		std::cin >> input;
		if (regex_match(input, INPUT_PATTERN)) {
			break;
		}
		else if (input == "exit"){
			shouldExit = true;
			break;
		} else {
			std::cout << "非法输入格式。请确定输入是否正确。" << endl;
		}
	}

	if (shouldExit) {
		return 0;
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
	return 1;
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
		std::sort(studentsList.begin(), studentsList.end());
	}
	return true;
}

bool System::change()
{
	std::string input;
	std::cout << "请输入被修改考生的id（取消请输入cancel）：";
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "操作取消。" << endl;
			break;
		}
		if (regex_match(input, ID_PATTERN)) {
			int id;
			stringstream ss;
			ss << input;
			ss >> id;
			bool deleteSuccessful = false;
			for (auto it = studentsList.begin(); it != studentsList.end();) {
				if (it->getId() == id) {
					std::cout << "请输入考生的考号、姓名、性别(M/F)、年龄以及报考类别（之间用空格隔开）：" << endl;
					string inputId, inputName, inputGender, inputAge, inputApplyFor;
					std::cin >> inputId >> inputName >> inputGender >> inputAge >> inputApplyFor;

					if (!regex_match(inputId, ID_PATTERN)) {
						std::cout << "考号格式不正确。" << endl;
						continue;
					}
					if (!regex_match(inputGender, GENDER_PATTERN)) {
						std::cout << "性别格式不正确（输入F代表性别女， M代表性别男）。" << endl;
						continue;
					}
					if (!regex_match(inputAge, AGE_PATTERN)) {
						std::cout << "年龄格式不正确。" << endl;
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
					}
					else {
						genderInit = FEMALE;
					}
					(*it) = Student(idInit, inputName, genderInit, ageInit, inputApplyFor);
				}
				else {
					++it;
				}
			}
			if (deleteSuccessful)
				cout << "删除成功。" << endl;
			else
				cout << "未找到删除项目。" << endl;
			break;
		}
		else {
			cout << "输入无效。" << endl;
			std::cin >> input;
		}
	}
	return true;
}

bool System::remove()
{
	std::string input;
	std::cout << "请输入被删除考生的id（取消请输入cancel）：";
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "操作取消。" << endl;
			break;
		}
		if (regex_match(input, ID_PATTERN)) {
			int id;
			stringstream ss;
			ss << input;
			ss >> id;
			bool deleteSuccessful = false;
			for (auto it = studentsList.begin(); it != studentsList.end();) {  //for循环中不要it++
				if (it->getId() == id) {
					it = studentsList.erase(it);
				} else {
					++it;
				}
			}
			if (deleteSuccessful)
				cout << "删除成功。" << endl;
			else
				cout << "未找到删除项目。" << endl;
			break;
		} else {
			cout << "输入无效。" << endl;
			std::cin >> input;
		}
	}

	return true;
}

bool System::find()
{
	string input;
	std::cout << "请输入查找学生的学号（取消请输入cancel）：" << endl;
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "操作取消。" << endl;
			break;
		}
		if (regex_match(input, ID_PATTERN)) {
			int id;
			stringstream ss;
			ss << input;
			ss >> id;
			bool deleteSuccessful = false;
			for (auto it = studentsList.begin(); it != studentsList.end();) {
				if (it->getId() == id) {
					string g;
					if (it->getGender() == MALE) {
						g = "男";
					} else {
						g = "女";
					}
					cout << "学号: " << it->getId() << "; "
						<< "姓名：" << it->getName() << "; "
						<< "性别：" << g << "; "
						<< "年龄：" << it->getAge() << "; " 
						<< "报考类别：" << it->getApplyFor() << std::endl;
				} else {
					++it;
				}
			}
			if (deleteSuccessful)
				cout << "删除成功。" << endl;
			else
				cout << "未找到删除项目。" << endl;
			break;
		} else {
			cout << "输入无效。" << endl;
			std::cin >> input;
		}
	}
	return true;
}

bool System::statistics()
{
	string g;
	fstream fout("output.txt", ios::out);
	for (int i = 0; i < studentsList.size(); ++i) {
		if (studentsList[i].getGender() == MALE) {
			g = "男";
		}
		else {
			g = "女";
		}

		fout << "学号: " << studentsList[i].getId() << "; "
			<< "姓名：" << studentsList[i].getName() << "; "
			<< "性别：" << g << "; "
			<< "年龄：" << studentsList[i].getAge() << "; "
			<< "报考类别：" << studentsList[i].getApplyFor() << std::endl;
	}
	std::cout << "内容已保存到当前目录下output.txt中。" << endl;
	std::cout << "共计人数：" << studentsList.size() << endl;
	fout.close();
	return true;
}
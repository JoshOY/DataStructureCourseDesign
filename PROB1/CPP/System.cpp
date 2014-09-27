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
	cout << "���Ƚ���������Ϣϵͳ��" << endl;
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
		std::cout << "���������Ĳ�����1-���� 2-ɾ�� 3-���� 4-�޸� 5-ͳ�ƣ�";
		std::cin >> input;
		if (regex_match(input, INPUT_PATTERN)) {
			break;
		} else {
			std::cout << "�Ƿ������ʽ����ȷ�������Ƿ���ȷ��" << endl;
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
		std::cout << "�����뿼��������0Ϊȡ����������";
		std::cin >> input;

		if (!regex_match(input, ID_PATTERN)) {
			std::cout << "���벻�Ϸ������������롣" << endl;
		}
		else {
			break;
		}
	}
	stringstream ss;
	ss << input;
	ss >> insertNum;
	if (insertNum == 0) {
		cout << "����ȡ����" << endl;
	}
	else {
		for (int n = 1; n <= insertNum; ++n) {
			std::cout << "�����뿼���Ŀ��š��������Ա�(M/F)�������Լ��������֮���ÿո��������" << endl;
			string inputId, inputName, inputGender, inputAge, inputApplyFor;
			std::cin >> inputId >> inputName >> inputGender >> inputAge >> inputApplyFor;

			if (!regex_match(inputId, ID_PATTERN)) {
				std::cout << "���Ÿ�ʽ����ȷ��" << endl;
				--n;
				continue;
			}
			if (!regex_match(inputGender, GENDER_PATTERN)) {
				std::cout << "�Ա��ʽ����ȷ������F�����Ա�Ů�� M�����Ա��У���" << endl;
				--n;
				continue;
			}
			if (!regex_match(inputAge, AGE_PATTERN)) {
				std::cout << "�����ʽ����ȷ��" << endl;
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
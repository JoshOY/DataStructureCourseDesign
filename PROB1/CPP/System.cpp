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
		std::cout << "���������Ĳ�����1-���� 2-ɾ�� 3-���� 4-�޸� 5-ͳ�ƣ�";
		std::cin >> input;
		if (regex_match(input, INPUT_PATTERN)) {
			break;
		}
		else if (input == "exit"){
			shouldExit = true;
			break;
		} else {
			std::cout << "�Ƿ������ʽ����ȷ�������Ƿ���ȷ��" << endl;
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
		std::sort(studentsList.begin(), studentsList.end());
	}
	return true;
}

bool System::change()
{
	std::string input;
	std::cout << "�����뱻�޸Ŀ�����id��ȡ��������cancel����";
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "����ȡ����" << endl;
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
					std::cout << "�����뿼���Ŀ��š��������Ա�(M/F)�������Լ��������֮���ÿո��������" << endl;
					string inputId, inputName, inputGender, inputAge, inputApplyFor;
					std::cin >> inputId >> inputName >> inputGender >> inputAge >> inputApplyFor;

					if (!regex_match(inputId, ID_PATTERN)) {
						std::cout << "���Ÿ�ʽ����ȷ��" << endl;
						continue;
					}
					if (!regex_match(inputGender, GENDER_PATTERN)) {
						std::cout << "�Ա��ʽ����ȷ������F�����Ա�Ů�� M�����Ա��У���" << endl;
						continue;
					}
					if (!regex_match(inputAge, AGE_PATTERN)) {
						std::cout << "�����ʽ����ȷ��" << endl;
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
				cout << "ɾ���ɹ���" << endl;
			else
				cout << "δ�ҵ�ɾ����Ŀ��" << endl;
			break;
		}
		else {
			cout << "������Ч��" << endl;
			std::cin >> input;
		}
	}
	return true;
}

bool System::remove()
{
	std::string input;
	std::cout << "�����뱻ɾ��������id��ȡ��������cancel����";
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "����ȡ����" << endl;
			break;
		}
		if (regex_match(input, ID_PATTERN)) {
			int id;
			stringstream ss;
			ss << input;
			ss >> id;
			bool deleteSuccessful = false;
			for (auto it = studentsList.begin(); it != studentsList.end();) {  //forѭ���в�Ҫit++
				if (it->getId() == id) {
					it = studentsList.erase(it);
				} else {
					++it;
				}
			}
			if (deleteSuccessful)
				cout << "ɾ���ɹ���" << endl;
			else
				cout << "δ�ҵ�ɾ����Ŀ��" << endl;
			break;
		} else {
			cout << "������Ч��" << endl;
			std::cin >> input;
		}
	}

	return true;
}

bool System::find()
{
	string input;
	std::cout << "���������ѧ����ѧ�ţ�ȡ��������cancel����" << endl;
	std::cin >> input;
	while (true) {
		if (input == "cancel") {
			cout << "����ȡ����" << endl;
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
						g = "��";
					} else {
						g = "Ů";
					}
					cout << "ѧ��: " << it->getId() << "; "
						<< "������" << it->getName() << "; "
						<< "�Ա�" << g << "; "
						<< "���䣺" << it->getAge() << "; " 
						<< "�������" << it->getApplyFor() << std::endl;
				} else {
					++it;
				}
			}
			if (deleteSuccessful)
				cout << "ɾ���ɹ���" << endl;
			else
				cout << "δ�ҵ�ɾ����Ŀ��" << endl;
			break;
		} else {
			cout << "������Ч��" << endl;
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
			g = "��";
		}
		else {
			g = "Ů";
		}

		fout << "ѧ��: " << studentsList[i].getId() << "; "
			<< "������" << studentsList[i].getName() << "; "
			<< "�Ա�" << g << "; "
			<< "���䣺" << studentsList[i].getAge() << "; "
			<< "�������" << studentsList[i].getApplyFor() << std::endl;
	}
	std::cout << "�����ѱ��浽��ǰĿ¼��output.txt�С�" << endl;
	std::cout << "����������" << studentsList.size() << endl;
	fout.close();
	return true;
}
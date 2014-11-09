/*
*	Main.cpp
*
*	Created by 1352847 JoshOY on 14-11-9
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	string inputStr;
	Node* root;

	cout << "**             ���׹���ϵͳ                 **" << endl;
	cout << "**********************************************" << endl;
	cout << "**             ������ִ�в���               **" << endl;
	cout << "**             A -- ���Ƽ���                **" << endl;
	cout << "**             B -- ��Ӽ�ͥ��Ա            **" << endl;
	cout << "**             C -- ��ɢ�ֲ���ͥ            **" << endl;
	cout << "**             D -- ���ļ�ͥ��Ա����        **" << endl;
	cout << "**             E -- �˳�����                **" << endl;
	cout << "**********************************************" << endl;

	cout << "�����뽨��һ�����ף�" << endl;
	cout << "���������ȵ�������"; cin >> inputStr;
	root = new Node(inputStr);
	cout << "�ü��׵������ǣ�" << inputStr << endl;

	while (true) {
		cout << endl;
		cout << "������Ҫִ�еĲ�����";
		cin >> inputStr;
		if (!std::regex_match(inputStr, OP_PATTERN)) {
			cout << "������Ч��" << endl;
			continue;
		}

		stringstream ss;
		int counter;
		Node* ptr;
		string changeName;

		switch (inputStr[0])
		{
		case 'A':
			cout << "������Ҫ������ͥ���˵�������"; cin >> inputStr;
			if (!checkRepeat(inputStr)) {
				cout << "�������Ҳ������ˣ�" << endl;
				break;
			}
			ptr = root->find(inputStr);

			cout << "�������Ů������"; cin >> inputStr;
			if (!regex_match(inputStr, UINT_PATTREN)) {
				cout << "���벻�Ϸ���" << endl;
				break;
			}
			ss << inputStr;
			ss >> counter;
			ss.clear();
			cout << "������������Ů������" << endl;
			for (int i = 0; i < counter; i++) {
				cin >> inputStr;
				if (!ptr->addChild(inputStr))
					cout << "����" << inputStr << "���������һ���ظ������������Ч��" << endl;
			}
			cout << ptr->name << "����һ����ŮΪ��";
			for (int i = 0; i < ptr->children.size(); i++) {
				cout << ptr->children[i]->name << '\t';
			}
			cout << endl;
			break;

		case 'B':
			cout << "������Ҫ������ͥ���˵�������"; cin >> inputStr;
			if (!checkRepeat(inputStr)) {
				cout << "�������Ҳ������ˣ�" << endl;
				break;
			}
			ptr = root->find(inputStr);
			cout << "������������Ů������" << endl;
			cin >> inputStr;
			if (!ptr->addChild(inputStr))
				cout << "����" << inputStr << "���������һ���ظ������������Ч��" << endl;
			cout << ptr->name << "����һ����ŮΪ��";
			for (int i = 0; i < ptr->children.size(); i++) {
				cout << ptr->children[i]->name << '\t';
			}
			cout << endl;
			break;

		case 'C':
			cout << "������Ҫ��ɢ��ͥ���˵�������"; cin >> inputStr;
			if (!root->deleteChild(inputStr)) {
				cout << "�������Ҳ������ˣ�" << endl;
			}
			else {
				cout << "ɾ����ϡ�" << endl;
			}
			break;

		case 'D':
			cout << "������Ҫ��ɢ��ͥ���˵�������"; cin >> inputStr;
			cout << "��������ĵ����֣�"; cin >> changeName;
			if (!root->editChild(inputStr, changeName)) {
				cout << "�������Ҳ������˻���ĺ��������" << endl;
			}
			else {
				cout << "������ϡ�" << endl;
			}
			break;
			break;

		case 'E':
			delete root;
			return 0;
			break;

		default:
			break;
		}
	}

	return 0;
}
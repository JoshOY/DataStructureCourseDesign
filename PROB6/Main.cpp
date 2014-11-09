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

	cout << "**             家谱管理系统                 **" << endl;
	cout << "**********************************************" << endl;
	cout << "**             请输入执行操作               **" << endl;
	cout << "**             A -- 完善家谱                **" << endl;
	cout << "**             B -- 添加家庭成员            **" << endl;
	cout << "**             C -- 解散局部家庭            **" << endl;
	cout << "**             D -- 更改家庭成员姓名        **" << endl;
	cout << "**             E -- 退出程序                **" << endl;
	cout << "**********************************************" << endl;

	cout << "首先请建立一个家谱！" << endl;
	cout << "请输入祖先的姓名："; cin >> inputStr;
	root = new Node(inputStr);
	cout << "该家谱的祖先是：" << inputStr << endl;

	while (true) {
		cout << endl;
		cout << "请输入要执行的操作：";
		cin >> inputStr;
		if (!std::regex_match(inputStr, OP_PATTERN)) {
			cout << "输入无效。" << endl;
			continue;
		}

		stringstream ss;
		int counter;
		Node* ptr;
		string changeName;

		switch (inputStr[0])
		{
		case 'A':
			cout << "请输入要建立家庭的人的姓名："; cin >> inputStr;
			if (!checkRepeat(inputStr)) {
				cout << "家谱中找不到此人！" << endl;
				break;
			}
			ptr = root->find(inputStr);

			cout << "请输入儿女人数："; cin >> inputStr;
			if (!regex_match(inputStr, UINT_PATTREN)) {
				cout << "输入不合法！" << endl;
				break;
			}
			ss << inputStr;
			ss >> counter;
			ss.clear();
			cout << "请依次输入子女姓名：" << endl;
			for (int i = 0; i < counter; i++) {
				cin >> inputStr;
				if (!ptr->addChild(inputStr))
					cout << "名字" << inputStr << "与家谱中另一人重复！本次添加无效。" << endl;
			}
			cout << ptr->name << "的下一代子女为：";
			for (int i = 0; i < ptr->children.size(); i++) {
				cout << ptr->children[i]->name << '\t';
			}
			cout << endl;
			break;

		case 'B':
			cout << "请输入要建立家庭的人的姓名："; cin >> inputStr;
			if (!checkRepeat(inputStr)) {
				cout << "家谱中找不到此人！" << endl;
				break;
			}
			ptr = root->find(inputStr);
			cout << "请依次输入子女姓名：" << endl;
			cin >> inputStr;
			if (!ptr->addChild(inputStr))
				cout << "名字" << inputStr << "与家谱中另一人重复！本次添加无效。" << endl;
			cout << ptr->name << "的下一代子女为：";
			for (int i = 0; i < ptr->children.size(); i++) {
				cout << ptr->children[i]->name << '\t';
			}
			cout << endl;
			break;

		case 'C':
			cout << "请输入要解散家庭的人的姓名："; cin >> inputStr;
			if (!root->deleteChild(inputStr)) {
				cout << "家谱中找不到此人！" << endl;
			}
			else {
				cout << "删除完毕。" << endl;
			}
			break;

		case 'D':
			cout << "请输入要解散家庭的人的姓名："; cin >> inputStr;
			cout << "请输入更改的名字："; cin >> changeName;
			if (!root->editChild(inputStr, changeName)) {
				cout << "家谱中找不到此人或更改后会重名！" << endl;
			}
			else {
				cout << "更改完毕。" << endl;
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
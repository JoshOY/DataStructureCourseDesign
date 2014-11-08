/*
*	Main.cpp
*
*	Created by 1352847 JoshOY on 14-11-8
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include "kmp.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "请输入文本内容（按回车结束）：" << endl;
	string content;
	std::getline(std::cin, content, '\n');

	

	cout << "请输入检索关键词：";
	string keyword;
	cin >> keyword;

	vector<unsigned int> kmpVec = prefixFunction(keyword);
	unsigned int matchCounter = 0;

	for (int i = 0; i < content.length(); i++) {
		if (keyword[0] == content[i]) {
			for (int j = 0; j < keyword.length(); j++) {
				if (keyword[j] != content[i + j]) {
					i += (j - 1 - kmpVec[j - 1]);
					break;
				}
				if (j == keyword.length() - 1) {
					matchCounter += 1;
					i += keyword.length() - 1;
					break;
				}
			}
		}
	}

	cout << "找到关键词\"" << keyword << "\"的次数：" << matchCounter << endl;
	cout << "请输入保存结果的文件名：";
	string filename;
	cin >> filename;

	fstream fout(filename);
	fout << "文本内容如下：" << endl;
	fout << content << endl;
	fout << "----------------------------------" << endl;
	fout << "找到关键词\"" << keyword << "\"的次数：" << matchCounter << endl;
	fout.close();

	return 0;
}
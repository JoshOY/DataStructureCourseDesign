/*
*	Main.cpp
*
*	Created by 1352847 JoshOY on 14-10-17
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include "Stdlibs.h";

static int N, S, M, K;
static Node* headNode = new Node{ 1, nullptr };
static Node* tailNode = headNode;
static stringstream ss;
static bool* surviveSet;

int main(int argc, char *argv[])
{
	//input
	cout << "约瑟夫问题(by JoshOY, 2014/10/27)： " << endl;
	cout << "假设N个人围成一圈，从第S个人开始报数，报到M的人出局，再由下一个人开始报数，如此循环直到剩下K个人为止。" << endl;

	string input;

	cout << "输入人数N: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "请输入正整数……" << endl;
		cout << "输入人数N: ";
		cin >> input;
	}

	ss.clear();
	ss << input;
	ss >> N;

	cout << "开始位置S: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "请输入正整数……" << endl;
		cout << "开始位置S: ";
		cin >> input;
	}
	ss.clear();
	ss << input;
	ss >> S;

	cout << "输入死亡数字M: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "请输入正整数……" << endl;
		cout << "输入死亡数字M: ";
		cin >> input;
	}
	ss.clear();
	ss << input;
	ss >> M;

	cout << "输入剩余人数K: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "请输入正整数……" << endl;
		cout << "输入剩余人数K: ";
		cin >> input;
	}
	ss.clear();
	ss << input;
	ss >> K;
	cout << endl;

	//init
	for (int i = 2; i <= N; ++i) {
		tailNode->next = new Node({i, nullptr});
		tailNode = tailNode->next;
	}
	tailNode->next = headNode;
	if (headNode->next == nullptr) {
		headNode->next = headNode;
	}

	Node* currentNode = headNode;
	Node* lastNode = tailNode;

	for (int i = 1; i < S; i++) {
		lastNode = lastNode->next;
		currentNode = currentNode->next;
	}

	surviveSet = new bool[N + 1];
	for (int i = 1; i < N; ++i) {
		surviveSet[i] = true;
	}


	//solve it
	int counter = 0;
	int deathId;
	for (int i = N; i > K; i--) {
		if (M > i) {
			M = M % i;
		}
		
		counter = 1;
		while (counter != M) {
			lastNode = lastNode->next;
			currentNode = currentNode->next;
			++counter;
		}

		//handle dead
		deathId = currentNode->id;
		lastNode->next = lastNode->next->next;
		delete currentNode;
		currentNode = lastNode->next;
		surviveSet[deathId] = false;

		cout << "第" << (N - i + 1) << "个死亡者的位置：\t" << deathId << endl;
	}

	cout << endl << "生还者位置为：\t";
	for (int i = 1; i <= N; i++) {
		if (surviveSet[i] == true) {
			cout << i << "\t";
		}
	}
	delete surviveSet;

	system("pause");
	return 0;
}
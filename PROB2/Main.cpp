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
	cout << "Լɪ������(by JoshOY, 2014/10/27)�� " << endl;
	cout << "����N����Χ��һȦ���ӵ�S���˿�ʼ����������M���˳��֣�������һ���˿�ʼ���������ѭ��ֱ��ʣ��K����Ϊֹ��" << endl;

	string input;

	cout << "��������N: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "����������������" << endl;
		cout << "��������N: ";
		cin >> input;
	}

	ss.clear();
	ss << input;
	ss >> N;

	cout << "��ʼλ��S: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "����������������" << endl;
		cout << "��ʼλ��S: ";
		cin >> input;
	}
	ss.clear();
	ss << input;
	ss >> S;

	cout << "������������M: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "����������������" << endl;
		cout << "������������M: ";
		cin >> input;
	}
	ss.clear();
	ss << input;
	ss >> M;

	cout << "����ʣ������K: ";
	cin >> input;
	while (!regex_match(input, UINT_PATTERN)) {
		cout << "����������������" << endl;
		cout << "����ʣ������K: ";
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

		cout << "��" << (N - i + 1) << "�������ߵ�λ�ã�\t" << deathId << endl;
	}

	cout << endl << "������λ��Ϊ��\t";
	for (int i = 1; i <= N; i++) {
		if (surviveSet[i] == true) {
			cout << i << "\t";
		}
	}
	delete surviveSet;

	system("pause");
	return 0;
}
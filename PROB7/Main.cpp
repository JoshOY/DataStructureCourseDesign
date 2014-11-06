/*
*	Main.cpp
*
*	Created by 1352847 JoshOY on 14-11-6
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char opPriority[] = { '+', '-', '*', '/', '^'};	//ȷ����������ȼ������ȵ��ź���
const int opPriorityLength = sizeof(opPriority);

typedef struct _ExpNode {		//�����ڵ�ṹ��
	_ExpNode()
	{
		parent = nullptr;
		lchild = nullptr;
		rchild = nullptr;
	}

	~_ExpNode()
	{
		if (lchild != nullptr) {
			lchild->~_ExpNode();
		}
		if (rchild != nullptr) {
			rchild->~_ExpNode();
		}
	}

	string val;
	_ExpNode* parent;
	_ExpNode* lchild;
	_ExpNode* rchild;
} ExpNode;

void analyseExp(string expression, ExpNode* node)	//�ú���ͨ���ݹ�������ʽ����������״�ṹ
{
	string lc, rc, op;	//Left exp, right exp, operator
	vector<bool> isOnLayerOutside;
	int currentLayer = 0, index = 0, opindex = 0, opwhere = 0;
	bool hasNoOp = true;

	while (expression[0] == '(' && expression[expression.length() - 1] == ')') {
		expression = expression.substr(1, expression.length() - 2);
	}

	for (auto ch : expression) {
		if (ch == '(') {
			currentLayer++;
		}
		if (ch == ')') {
			currentLayer--;
		}
		isOnLayerOutside.push_back(currentLayer == 0);
		index++;
	}

	for (opindex = 0; opindex < opPriorityLength; opindex++) {
		for (index = 0; index < expression.length(); index++) {
			if (isOnLayerOutside[index] && (expression[index] == opPriority[opindex])) {
				hasNoOp = false;
				opwhere = index;
				break;
			}
		}
		if (hasNoOp == false) {
			break;
		}
	}

	if (hasNoOp) {
		node->val = expression;
		node->lchild = nullptr;
		node->rchild = nullptr;
		return;
	} else {
		node->val = opPriority[opindex];
		lc = expression.substr(0, opwhere);
		rc = expression.substr(opwhere + 1);
		node->lchild = new ExpNode;
		node->lchild->parent = node;
		node->rchild = new ExpNode;
		node->rchild->parent = node;
		analyseExp(lc, node->lchild);
		analyseExp(rc, node->rchild);
		return;
	}
}

string getPolishExp(ExpNode* node)
{
	string rtn = node->val;
	if (node->lchild != nullptr) {
		rtn += " " + getPolishExp(node->lchild);
	}
	if (node->rchild != nullptr) {
		rtn += " " + getPolishExp(node->rchild);
	}
	return rtn;
}

string getPolishExpRev(ExpNode* node)
{
	string rtn = "";
	if (node->lchild != nullptr) {
		rtn += getPolishExpRev(node->lchild) + " ";
	}
	if (node->rchild != nullptr) {
		rtn += getPolishExpRev(node->rchild) + " ";
	}
	rtn += node->val;
	return rtn;
}

int main(int argc, char* argv[])
{
	ExpNode* root = new ExpNode;

	string exp;
	cout << "��������ʽ�� ";
	getline(cin, exp);
	analyseExp(exp, root);

	cout << "�������ʽ��ǰ׺���ʽ��Ϊ��" << getPolishExp(root) << endl;
	cout << "��׺���ʽΪ��" << exp << endl;
	cout << "�沨�����ʽ��ǰ׺���ʽ��Ϊ��" << getPolishExpRev(root) << endl;

	delete root;		//������~ExpNode()���ӽڵ��ڸ��ڵ�ɾ��ʱҲ���ͷ��ڴ档
	system("pause");
	return 0;
}
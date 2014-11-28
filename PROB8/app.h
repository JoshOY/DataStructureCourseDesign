#ifndef __1352847_APP_H__
#define __1352847_APP_H__

#include "KruskalAlgo.h"
#include <regex>

using namespace std;
const regex INPUT_PATTERN("[ABCDEabcde]");

class Application 
{
public:
	Application()
	{
		cout << "电网造价模拟系统" << endl;
		cout << endl;
		cout << "A - 创造电网节点" << endl;
		cout << "B - 添加电网的边" << endl;
		cout << "C - 构造并显示最小生成树" << endl;
		cout << "D - 退出程序" << endl;
	}

	bool getOperation() 
	{
		cout << "Select operation: ";
		string input;
		cin >> input;
		if (!regex_match(input, INPUT_PATTERN)) {
			cout << "Invalid input." << endl << endl;
			return true;
		}
		switch (input[0]) {
		case 'A':
		case 'a':
			createNewNodes();
			break;
		case 'B':
		case 'b':
			addEdges();
			break;
		case 'C':
		case 'c':
			spanTree();
			break;
		case 'D':
		case 'd':
			return false;
			break;
		}
	}

	void createNewNodes()
	{
		cout << "Please input the number of nodes you want to insert: ";
		int num;
		cin >> num;
		
		cout << "Please input names of nodes you want to insert." << endl;
		string str;
		int start = g.nodes.size();
		for (int i = start; i < start + num; i++) {
			cin >> str;
			g.nodes[str] = i;
		}
	}

	void addEdges()
	{
		cout << "Please input the names of the two nodes and distance: ";
		string nodeA, nodeB;
		int w;
		cin >> nodeA >> nodeB >> w;
		if ((g.nodes.count(nodeA) > 0) && (g.nodes.count(nodeB) > 0)) {
			g.edges.push_back({g.nodes[nodeA], g.nodes[nodeB], w});
			cout << "insert complete." << endl << endl;
		}
		else {
			cout << "Node not found." << endl << endl;
		}
		return;
	}

	void spanTree()
	{
		std::sort(g.edges.begin(), g.edges.end());
		vector<string> t = kruskalAlgorithm(g);
		for (auto s : t) {
			cout << s << "\t";
		}
		cout << endl << endl;
		return;
	}

private:
	Graph g;
};

#endif

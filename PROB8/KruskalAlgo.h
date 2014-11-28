#ifndef __1352847_KRUSKAL_ALGO_H__
#define __1352847_KRUSKAL_ALGO_H__

#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

const int NOT_FOUND = -1;

// Struct of edge
typedef struct _Edge {
	int node1;
	int node2;
	int weight;

	bool operator<(const _Edge& rhs) {
		if (this->weight <= rhs.weight) {
			return true;
		} else {
			return false;
		}
	}
} Edge;

// Struct of graph
typedef struct _Graph {
	vector<Edge> edges;
	map<string, int> nodes;
} Graph;

//Before using this algorithm, please ensure g.edges is sorted.
vector<string> kruskalAlgorithm(const Graph& g)
{
	// Vars we need
	int n, m;
	vector<int> parent;
	vector<string> rtn;
	auto f = [](const vector<int>& parentVec, int currentNode)
	{
		while (parentVec[currentNode] != NOT_FOUND) {
			currentNode = parentVec[currentNode];
		}
		return currentNode;
	};
	
	// Initialize the parent array as {-1, -1, -1, ...} (size == node nums in graph)
	for (int i = 0; i < g.nodes.size(); i++) {
		parent.push_back(NOT_FOUND);	//NOT_FOUND = -1
	}

	for (int i = 0; i < g.edges.size(); i++) {
		n = f(parent, g.edges[i].node1);
		m = f(parent, g.edges[i].node2);

		if (n != m) {	//if m == n, then it's not a tree but a ring
			parent[n] = m;
			string name1, name2;
			for (auto v : g.nodes) {
				if (v.second == g.edges[i].node1) {
					name1 = v.first;
					break;
				}
			}
			for (auto v : g.nodes) {
				if (v.second == g.edges[i].node2) {
					name2 = v.first;
					break;
				}
			}
			stringstream ss;
			string weight_str;
			ss << g.edges[i].weight;
			ss >> weight_str;

			rtn.push_back(name1 + "-(" + weight_str + ")->" + name2);
			//std::cout << "(" << g.nodes[g.edges[i].node1] << ", " << g.nodes[g.edges[i].node2] << ") [" << g.edges[i].weight << "]" << std::endl;
		}
	}
	return rtn;
}

#endif
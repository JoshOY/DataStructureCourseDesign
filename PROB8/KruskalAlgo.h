/*
*	KruskalAlgo.h
*
*	Created by 1352847 JoshOY on 14-11-20
*	Copyright (c) 2014 JoshOY. All rights reserved.
*/

#ifndef __1352847_KRUSKAL_ALGO_H__
#define __1352847_KRUSKAL_ALGO_H__

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using std::sort;
using std::set;
using std::vector;
using std::string;

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
	vector<string> nodes;
} Graph;

//Before using this algorithm, please ensure g.edges is sorted.
void kruskalAlgorithm(const Graph& g)
{
	// Vars we need
	int n, m;
	vector<int> parent;
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
			std::cout << "(" << g.nodes[g.edges[i].node1] << ", " << g.nodes[g.edges[i].node2] << ") [" << g.edges[i].weight << "]" << std::endl;
		}
	}
}

#endif
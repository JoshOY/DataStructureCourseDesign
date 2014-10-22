#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include "ProbStructs.h"

using namespace std;

static ifstream fin("prob3.txt");
static int maze_length, maze_width;
static int startPosX, startPosY, endPosX, endPosY;
static vector<vector<bool> > maze;
static vector<Pos> steps;
static set<Pos> stepsSet;

void inputAndInit()
{
	//Input the size of maze and initialize static vars.
	fin >> maze_length >> maze_width;
	fin >> startPosX >> startPosY >> endPosX >> endPosY;
	for (int i = 0; i < maze_length; ++i) {
		vector<bool> tmpVec;
		for (int j = 0; j < maze_width; ++j) {
			tmpVec.push_back(true);
		}
		maze.push_back(tmpVec);
	}

	//check out the blocks;
	int blockNum, tmpX, tmpY;
	fin >> blockNum;
	for (int i = 1; i <= blockNum; ++i) {
		fin >> tmpX >> tmpY;
		maze[tmpX][tmpY] = false;
	}
	fin.close();

	for (int i = 0; i <= maze_length; ++i) {
		stepsSet.insert({ i, -1 });
		stepsSet.insert({ -1, i });
		stepsSet.insert({ i, maze_length });
		stepsSet.insert({ maze_width, i });
	}
	return;
}

bool dfs(int x, int y)
{
	if ((x == endPosX) && (y == endPosY)) {
		steps.push_back({x, y});
		return true;
	}

	bool canGoLeft = true, canGoRight = true, canGoUp = true, canGodown = true;
	if (stepsSet.count({ x - 1, y }) || (maze[x - 1][y] == false) ) {
		canGoUp = false;
	}
	if (stepsSet.count({ x + 1, y }) || (maze[x + 1][y] == false)) {
		canGodown = false;
	}
	if (stepsSet.count({ x, y - 1 }) || (maze[x][y - 1] == false)) {
		canGoLeft = false;
	}
	if (stepsSet.count({ x, y + 1 }) || (maze[x][y + 1] == false)) {
		canGoRight = false;
	}

	steps.push_back({ x, y });
	stepsSet.insert({ x, y });
	if (canGoRight) {
		if (dfs(x, y + 1)) {
			return true;
		}
	}
	if (canGodown) {
		if (dfs(x + 1, y)) {
			return true;
		}
	}
	if (canGoLeft) {
		if (dfs(x, y - 1)) {
			return true;
		}
	}
	if (canGoUp) {
		if (dfs(x - 1, y)) {
			return true;
		}
	}
	steps.pop_back();
	stepsSet.erase({ x, y });
	return false;
}

int main()
{
	inputAndInit();
	dfs(startPosX, startPosY);
	for (int i = 0; i < steps.size(); ++i) {
		fout << "( " << steps[i].x << " , " << steps[i].y << " )";
		if (i != steps.size() - 1) {
			fout << " -> ";
		}
	}
	fout.close();
	return 0;
}

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum directions { N, E, S, W };

template <typename T>
struct items
{
	T x;
	T y;
	int dir;
};

template <typename T>
class Maze
{
	vector <vector<T>> maze_mark;
	stack<items<T>> stack; // 순서대로 i(행), j(열), direction 저장
public:
	Maze();
	void maze_file();
	void maze_output();
};


#endif

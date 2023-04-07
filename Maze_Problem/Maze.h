#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

enum directions { N, E, S, W };

template <typename T>
struct items
{
	T i;
	T j;
	int dir;
};

template <typename T>
class Maze
{
	int cur_i;
	int cur_j;
	int next_i;
	int next_j;
	vector <vector<T>> maze_map;
	vector <vector<T>> maze_mark;
	stack<items<T>> stack; // 순서대로 i(행), j(열), direction 저장
public:
	Maze();
	void maze_file();
	void maze_output();
	void maze_check(int i, int j);
	void start();
	void find_dir();
	void path();
	void move(T d);
};

#endif

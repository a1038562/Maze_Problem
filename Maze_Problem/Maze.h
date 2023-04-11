#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#define SIZE 100

using namespace std;

typedef struct
{
	int i;
	int j;
}heading;

template <typename T>
struct items
{
	T i;
	T j;
	T dir;
};

enum directions { N, E, S, W };

template <typename T>
class Maze
{
	heading motion[4] = { {-1,0},{0,1},{1,0},{0,-1} };
	vector <vector<int>> maze_map;
	vector <vector<int>> maze_mark;
	vector <vector<int>> maze_result;
	items<T> stack[SIZE];
	int size;

public:
	Maze();
	void maze_file();
	void maze_output(vector < vector<int >> maze_info);
	void maze_check(int i, int j);
	void start();
	void path();
	void result();
	void push(items<T> temp);
	items<T> pop();
	items<T> input(T i, T j, T d);
	void save();
};

#endif
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#define SIZE 100 // stack�� �ִ� ����

using namespace std;

typedef struct // Ž�� ������ �����ϴ� ����ü
{
	int i;
	int j;
}heading;

template <typename T> // ����ü ���ø�
struct items // stack�� ������ i, j, ���� ����
{
	T i; // ��
	T j; // ��
	T dir; // ����
};

enum directions { N, E, S, W }; // ����

template <typename T> // Ŭ���� ���ø�
class Maze
{
	items<T> stack[SIZE]; // �̵� ������ ������ stack
	int size; // stack ũ��
	heading motion[4] = { {-1,0},{0,1},{1,0},{0,-1} }; // �̵� ���⿡ ���� ��ǥ
	vector <vector<int>> maze_map; // �̷� map
	vector <vector<int>> maze_mark; // �̵� ��� Ȯ�ο� vector
	vector <vector<int>> maze_result; // �̵� ��� ��¿� vector

public:
	Maze(); // ������
	void maze_file(); // �̷� csv ���� �ҷ�����
	void maze_output(vector < vector<int >> maze_info); // �̷� ����ϱ�
	void maze_check(int i, int j); // �̷� �迭�� ���� Ȯ��
	void start(); // �̷� ã�� ����
	void path(); // �̷� ������ ��� Ž��
	void result(); // �̷� ã�� ��� ���
	void push(items<T> temp); // stack�� �� �߰�
	items<T> pop(); // stack�� ���������� ����� �� �ҷ�����
	items<T> input(T i, T j, T d); // item ����ü�� ���� ����
	void save(); // �̷� ã�� ����� csv ���Ϸ� ����
};

#endif
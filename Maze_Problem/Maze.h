#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#define SIZE 100 // stack의 최대 개수

using namespace std;

typedef struct // 탐색 방향을 저장하는 구조체
{
	int i;
	int j;
}heading;

template <typename T> // 구조체 템플릿
struct items // stack에 저장할 i, j, 방향 정보
{
	T i; // 행
	T j; // 열
	T dir; // 방향
};

enum directions { N, E, S, W }; // 방향

template <typename T> // 클래스 템플릿
class Maze
{
	items<T> stack[SIZE]; // 이동 정보를 저장할 stack
	int size; // stack 크기
	heading motion[4] = { {-1,0},{0,1},{1,0},{0,-1} }; // 이동 방향에 따른 좌표
	vector <vector<int>> maze_map; // 미로 map
	vector <vector<int>> maze_mark; // 이동 경로 확인용 vector
	vector <vector<int>> maze_result; // 이동 경로 출력용 vector

public:
	Maze(); // 생성자
	void maze_file(); // 미로 csv 파일 불러오기
	void maze_output(vector < vector<int >> maze_info); // 미로 출력하기
	void maze_check(int i, int j); // 미로 배열의 숫자 확인
	void start(); // 미로 찾기 시작
	void path(); // 미로 내에서 경로 탐색
	void result(); // 미로 찾기 결과 출력
	void push(items<T> temp); // stack에 값 추가
	items<T> pop(); // stack에 마지막으로 저장된 값 불러오기
	items<T> input(T i, T j, T d); // item 구조체에 정보 저장
	void save(); // 미로 찾기 결과를 csv 파일로 저장
};

#endif
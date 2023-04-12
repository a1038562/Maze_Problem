#include "Maze.h"

template <typename T>
Maze<T>::Maze() : size(-2) // stack 크기 초기화, 값이 존재하지 않음을 표현하기 위해 음수 사용
{
	stack[SIZE - 1] = {}; // stack 초기화
};

template <typename T>
void Maze<T>::maze_file() // 미로 csv를 읽는 함수
{
	vector <int> maze_list;
	vector <int> maze_wall;
	ifstream file;
	file.open("maze.csv", ios::in); // maze 파일 열기

	int j = 1; // 열 인덱스, 나머지 계산을 위해 1부터 시작

	while (!file.eof()) // 파일이 끝나기 전까지 반복
	{
		string buf;
		string mark;
		file >> buf; // 파일 첫 번째 행을 string에 저장
		int size_j = (buf.length() + 1) / 2; // 열의 크기 계산
		stringstream ss(buf);
		maze_list.push_back(1); // 좌측의 벽을 만들기 위해 1을 1차원 vector에 추가

		while (getline(ss, mark, ',')) // ','이 나오기 전까지 문자 읽기 반복
		{
			maze_list.push_back(stoi(mark)); // 1차원 vector에 읽은 문자 저장

			if (j % size_j == 0) // j(누적 열)가 size_j(열 크기)가 되는 경우 행 증가
			{
				maze_list.push_back(1); // 우측의 벽을 만들기 위해 1을 1차원 vector에 추가
				maze_map.push_back(maze_list); // 2차원 vector에 하나의 행 정보를 담은 1차원 vector 저장
				maze_list.clear(); // 1차원 vector 비우기
			}

			j++;
		}
	}

	for (int k = 0; k < maze_map[0].size(); k++) maze_wall.push_back(1); // 상단, 하단의 벽을 만들기 위해 1을 1차원 vector에 열 크기만큼 추가
	maze_map.insert(maze_map.begin(), maze_wall); // 2차원 vector에 상단 벽 정보를 담은 1차원 vector 저장
	maze_map.push_back(maze_wall); // 2차원 vector에 하단 벽 정보를 담은 1차원 vector 저장

	file.close(); // 파일 닫기
}
template <typename T>
void Maze<T>::maze_output(vector<vector<int>> maze_info) // 미로 출력 함수
{
	for (int i = 0; i < maze_info.size(); i++) // 행 증가
	{
		for (int j = 0; j < maze_info[0].size(); j++) // 열 증가
			cout << maze_info[i][j] << " "; // 미로 출력

		cout << "\n";
	}
	cout << "\n";
}

template <typename T>
void  Maze<T>::start() // 시작 함수
{
	maze_file(); // csv 파일을 불러오는 함수 실행
	maze_mark.assign(maze_map.begin(), maze_map.end()); // map vector를 이동 확인용 vector에 복사

	// map 구성 정보 출력
	cout << "\n< START >\n";
	cout << "\n0: FLOOR\n";
	cout << "\n1: WALL\n";
	cout << "\n2: PATH\n";
	cout << "\nINPUT MAZE\n";

	maze_output(maze_map); // 초기 map 출력
	path(); // 경로 찾기 함수 실행
}

template <typename T>
void Maze<T>::path() // 경로 탐색 함수
{
	size = -1; // 시작 전 push 함수를 실행하면 size가 1 증가하므로 -1로 초기화
	maze_mark[1][1] = 1; // 이동 확인용 vector에 초기 지점 표시
	items<int> temp = input(1, 1, E); // 초기 위치 정보를 item 형식으로 저장
	push(temp); // stack에 저장
	int cur_i; // 현재 i
	int cur_j; // 현재 j
	int d; // 현재 방향
	int next_i; // 이동 후 i
	int next_j; // 이동 후 j

	while (size >= 0) // stack에 값이 존재하는 동안 반복
	{
		temp = pop(); // stack에 마지막으로 저장된 값 불러오기
		cur_i = temp.i;  // 현재 i를 저장된 값으로 설정
		cur_j = temp.j; // 현재 j를 저장된 값으로 설정
		d = temp.dir; // 현재 방향을 저장된 값으로 설정

		while (d < 4) // 방향이 4방향 중 하나인 경우에 반복
		{
			next_i = cur_i + motion[d].i; // 방향에 따라 이동 후 i 설정
			next_j = cur_j + motion[d].j; // 방향에 따라 이동 후 j 설정

			if (next_i == maze_map.size() - 2 && next_j == maze_map[0].size() - 2) // 이동 후의 상태가 도착하는 경우
			{
				d++;
				temp = input(cur_i, cur_j, d); // 현재 정보를 item 형식으로 저장
				push(temp); // stack에 저장

				temp = input(next_i, next_j, d); // 이동 후의 정보를 item 형식으로 저장
				push(temp); // stack에 저장

				result(); // 결과 출력
				break;
			}

			else if (maze_mark[next_i][next_j] == 0 && maze_map[next_i][next_j] == 0) // 새로운 경로를 찾은 경우
			{
				maze_mark[next_i][next_j] = 1; // 이동 확인용 vector 표시 전환

				//현재까지의 이동 경로를 stack에 저장
				temp.i = cur_i; // 현재 i 저장
				temp.j = cur_j; // 현재 j 저장
				temp.dir = d++; // 이동할 방향 저장
				push(temp); // 위의 정보들을 stack에 저장

				cur_i = next_i; // 현재 i를 이동 후 i 값으로 설정
				cur_j = next_j; // 현재 j를 이동 후 j 값으로 설정
				d = N; // 현재 방향을 N(=0)으로 설정
			}

			else d++; // 시계방향으로 방향 순서 이동


		}
	}
}

template <typename T>
void Maze<T>::result() // 결과 출력 함수
{
	maze_result.assign(maze_map.begin(), maze_map.end()); // map vector를 결과 출력용 vector에 복사

	for (int k = 0; k <= size; k++)
		maze_result[stack[k].i][stack[k].j] = 2; // 생성된 경로를 2로 표시


	cout << "\nOUTPUT MAZE\n";
	maze_output(maze_result); // 생성된 경로가 표시된 map 출력

	cout << "\nMOVEMENT COORDINATES\n";
	for (int k = 0; k <= size; k++)
		cout << "( " << stack[k].i << ", " << stack[k].j << " )" << "\n"; // 이동 좌표 출력

	cout << "\nTRAVEL DISTANCE: " << size << "\n"; // 이동 거리 출력
	save(); // 이동 좌표를 csv 파일에 저장 
}

template <typename T>
items<T> Maze<T>::input(T i, T j, T d) // item 형식 저장 함수
{
	// 입력된 값을 item 형식으로 저장 후 반환
	items<T> temp;
	temp.i = i;
	temp.j = j;
	temp.dir = d;
	return temp;
}

template <typename T>
void Maze<T>::push(items<T> temp) // stack 저장 함수
{
	size++; // stack 크기 증가
	// stack의 마지막에 값 저장
	stack[size].i = temp.i;
	stack[size].j = temp.j;
	stack[size].dir = temp.dir;
}

template <typename T>
items<T> Maze<T>::pop() // stack에 마지막으로 저장된 값을 불러오는 함수
{
	items<T> temp;

	if (size >= 0) // stack에 값이 존재하는 경우
	{
		temp = stack[size]; // stack에 마지막으로 저장된 값 불러오기 
		size--; // 크기 감소
	}
	return temp;
}

template <typename T>
void Maze<T>::save() // 미로 찾기 결과를 csv 파일로 저장 
{
	ofstream file("path.csv"); // 저장할 파일 
	if (file.is_open()) // 파일이 열려있는 경우
	{
		for (int k = 0; k <= size; k++)
			file << stack[k].i << "," << stack[k].j << "\n"; // i, j를 저장
	}
	file.close(); // 파일 닫기
	cout << "\nFILE SAVED\n";
}
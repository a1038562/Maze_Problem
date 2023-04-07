#include "Maze.h"

template <typename T>
Maze<T>::Maze()
{}

template <typename T>
void Maze<T>::maze_file()
{
	vector <int> maze_list;
	ifstream file;

	file.open("maze.csv", ios::in);

	int j = 1; // 열 인덱스, 나머지 계산을 위해 1부터 시작

	while (!file.eof())
	{
		string buf;
		string mark;
		file >> buf;
		stringstream ss(buf);
		while (getline(ss, mark, ','))
		{
			maze_list.push_back(stoi(mark));

			if (j % 15 == 0)// 15x15 행렬이므로 i번째 행에서 j(열)가 15가 되는 경우 행 증가
			{
				maze_map.push_back(maze_list);
				maze_list.clear();
			}
			j++;
		}
	}
	file.close();
}

template <typename T>
void Maze<T>::maze_output()
{
	for (int i = 0; i < maze_map.size(); i++)
	{
		for (int j = 0; j < maze_map[0].size(); j++)
		{
			cout << maze_map[i][j] << " ";
		}
		cout << "\n";
	}
}

template <typename T>
void  Maze<T>::maze_check(int i, int j)
{
	if (i < maze_map.size() && j < maze_map[0].size())
	{
		cout << "(" << i << ", " << j << ") " << maze_map[i][j] << "\n";
	}

	else
	{
		cout << "path not exist\n";
	}
}

template <typename T>
void  Maze<T>::start()
{
	//copy(maze_map.begin(), maze_map.end(), maze_mark.begin());
	maze_mark.assign(maze_map.begin(), maze_map.end()); // 복사

	cur_i = 0;
	cur_j = 0;
	next_i = 0;
	next_j = 0;
	maze_mark[0][0] = 1;
	stack.push(0, 0, E);
	path();
}

//template <typename T>
//void Maze<T>::find_dir()
//{
//	int d; //방향
//	int cost = 0;
//
//	switch (d)
//	{
//	case E:
//		cost = 1;
//		break;
//	case N:
//		cost = 2;
//		break;
//	case S:
//		cost = 1;
//		break;
//	case W:
//		cost = 2; 
//		break;
//	}
//}

template <typename T>
void Maze<T>::path()
{
	int d;
	items temp;
	while (d < 4)
	{
		temp = stack.pop(); // stack에서 가장 마지막으로 저장된 i, j, dir 정보 
		move(d); // 새로 탐색한 방향에 따라 이동
		if (cur_i == maze_map.size() && cur_j = maze_map[0].size()) // 도착
		{
			break;
		}

		if (maze_mark[next_i][next_j] == 0 && maze_map[next_i][next_j] == 0) // 새로운 경로를 찾은 경우
		{
			maze_mark[next_i][next_j] = 1; // 새로운 경로 mark를 1로 변경
			//현재까지의 이동 경로를 stack에 저장
			temp.i = cur_i; // stack에 현재 i 저장
			temp.j = cur_j; // stack에 현재 j 저장
			//temp.dir++; // stack에 이동할 방향 저장
			stack.push(temp);
			cur_i = next_i;
			cur_j = next_j;
		}
		else d++; // 새로운 방향 탐색
	}
}

template <typename T>
void Maze<T>::move(T d)
{
	switch (d)
	{
	case E:
		next_j = cur_j + 1;
		break;
	case N:
		next_i = cur_i + 1;
		break;
	case S:
		next_i = cur_i - 1;
		break;
	case W:
		next_j = cur_j - 1;
		break;
	}
}
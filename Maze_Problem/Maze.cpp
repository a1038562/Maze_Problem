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

	int j = 1; // �� �ε���, ������ ����� ���� 1���� ����

	while (!file.eof())
	{
		string buf;
		string mark;
		file >> buf;
		stringstream ss(buf);
		while (getline(ss, mark, ','))
		{
			maze_list.push_back(stoi(mark));

			if (j % 15 == 0)// 15x15 ����̹Ƿ� i��° �࿡�� j(��)�� 15�� �Ǵ� ��� �� ����
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
	maze_mark.assign(maze_map.begin(), maze_map.end()); // ����

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
//	int d; //����
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
		temp = stack.pop(); // stack���� ���� ���������� ����� i, j, dir ���� 
		move(d); // ���� Ž���� ���⿡ ���� �̵�
		if (cur_i == maze_map.size() && cur_j = maze_map[0].size()) // ����
		{
			break;
		}

		if (maze_mark[next_i][next_j] == 0 && maze_map[next_i][next_j] == 0) // ���ο� ��θ� ã�� ���
		{
			maze_mark[next_i][next_j] = 1; // ���ο� ��� mark�� 1�� ����
			//��������� �̵� ��θ� stack�� ����
			temp.i = cur_i; // stack�� ���� i ����
			temp.j = cur_j; // stack�� ���� j ����
			//temp.dir++; // stack�� �̵��� ���� ����
			stack.push(temp);
			cur_i = next_i;
			cur_j = next_j;
		}
		else d++; // ���ο� ���� Ž��
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
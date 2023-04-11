#include "Maze.h"

template <typename T>
Maze<T>::Maze() {};

template <typename T>
void Maze<T>::maze_file()
{
	vector <int> maze_list;
	vector <int> maze_wall;
	ifstream file;
	string s, r;
	file.open("maze.csv", ios::in);

	int j = 1; // �� �ε���, ������ ����� ���� 1���� ����

	while (!file.eof())
	{
		string buf;
		string mark;
		file >> buf;
		int size_j = (buf.length() + 1) / 2;
		stringstream ss(buf);
		maze_list.push_back(1);

		while (getline(ss, mark, ','))
		{
			maze_list.push_back(stoi(mark));

			if (j % size_j == 0)// 15x15 ����̹Ƿ� i��° �࿡�� j(��)�� 15�� �Ǵ� ��� �� ����
			{
				maze_list.push_back(1);
				maze_map.push_back(maze_list);
				maze_list.clear();
			}

			j++;
		}
	}

	for (int k = 0; k < maze_map[0].size(); k++) maze_wall.push_back(1);
	maze_map.insert(maze_map.begin(), maze_wall);
	maze_map.push_back(maze_wall);

	file.close();
}
template <typename T>
void Maze<T>::maze_output(vector<vector<int>> maze_info)
{
	for (int i = 0; i < maze_info.size(); i++)
	{
		for (int j = 0; j < maze_info[0].size(); j++) cout << maze_info[i][j] << " ";

		cout << "\n";
	}
	cout << "\n";
}

template <typename T>
void  Maze<T>::start()
{
	maze_file();
	maze_mark.assign(maze_map.begin(), maze_map.end()); // ����

	cout << "\n< START >\n";
	cout << "\n0: FLOOR\n";
	cout << "\n1: WALL\n";
	cout << "\n2: PATH\n";
	cout << "\nINPUT MAZE\n";

	maze_output(maze_map);
	path();
}

template <typename T>
void Maze<T>::path()
{
	size = -1;
	maze_mark[1][1] = 1;
	items<int> temp = input(1, 1, E);
	push(temp);
	int cur_i;
	int cur_j;
	int d;
	int next_i;
	int next_j;

	while (size >= 0)
	{
		temp = pop();// stack���� ���� ���������� ����� i, j ���� 
		cur_i = temp.i;
		cur_j = temp.j;
		d = temp.dir;

		while (d < 4)
		{
			next_i = cur_i + motion[d].i;
			next_j = cur_j + motion[d].j;

			if (next_i == maze_map.size() - 2 && next_j == maze_map[0].size() - 2) // ����
			{
				d++;
				temp = input(cur_i, cur_j, d);
				push(temp);

				temp = input(next_i, next_j, d);
				push(temp);

				result();
				break;
			}

			else if (maze_mark[next_i][next_j] == 0 && maze_map[next_i][next_j] == 0) // ���ο� ��θ� ã�� ���
			{
				maze_mark[next_i][next_j] = 1; // ���ο� ��� mark�� 1�� ����

				//��������� �̵� ��θ� stack�� ����
				temp.i = cur_i; // stack�� ���� i ����
				temp.j = cur_j; // stack�� ���� j ����
				temp.dir = d++;

				//stack.push_back(temp);
				push(temp);

				cur_i = next_i;
				cur_j = next_j;
				d = N;
			}

			else d++;


		}
	}
}

template <typename T>
void Maze<T>::result()
{
	maze_result.assign(maze_map.begin(), maze_map.end()); // ����

	for (int k = 0; k <= size; k++) maze_result[stack[k].i][stack[k].j] = 2;


	cout << "\nOUTPUT MAZE\n";
	maze_output(maze_result);

	cout << "\nMOVEMENT COORDINATES\n";
	for (int k = 0; k <= size; k++) cout << "( " << stack[k].i << ", " << stack[k].j << " )" << "\n";


	save();
}

template <typename T>
items<T> Maze<T>::input(T i, T j, T d)
{
	items<T> temp;
	temp.i = i;
	temp.j = j;
	temp.dir = d;
	return temp;
}

template <typename T>
void Maze<T>::push(items<T> temp)
{
	size++;
	stack[size].i = temp.i;
	stack[size].j = temp.j;
	stack[size].dir = temp.dir;
}

template <typename T>
items<T> Maze<T>::pop()
{
	items<T> temp;

	if (size >= 0)
	{
		temp = stack[size];
		size--;
	}
	return temp;
}

template <typename T>
void Maze<T>::save()
{
	ofstream file("path.csv");
	if (file.is_open())
	{
		for (int k = 0; k <= size; k++) file << stack[k].i << "," << stack[k].j << "\n";
	}
	file.close();
	cout << "\nFILE SAVED\n";
}
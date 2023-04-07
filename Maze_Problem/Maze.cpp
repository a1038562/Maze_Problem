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
                maze_mark.push_back(maze_list);
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
    for (int i = 0; i < maze_mark.size(); i++)
    {
        for (int j = 0; j < maze_mark[0].size(); j++)
        {
            cout << maze_mark[i][j] << " ";
        }
        cout << endl;
    }
}
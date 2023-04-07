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
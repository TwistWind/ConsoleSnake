// ConsoleSnake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
#include <cstdio>  
#include <cstdlib>  
#include <ctime>  
#include <conio.h>  
#include <cmath>  
#include <windows.h> 

using namespace std;


void print_wall();
void cursor_locate(int x, int y);
void cursor_hide();
void Default_print_snake();
bool if_correct();
bool create_food();
bool snake_move();

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

struct node
{
	int x, y;
}snake[1000];
const int n = 40,m=24;
int snake_length, dir;
node food;
int direct[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };

int main()
{
	int hard;
	cout << "請輸入難度:";
	cin >> hard;
	if (hard <= 0 || hard>100)
	{
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}
	/*** 数据全部初始化，包括蛇长，位置，方向 ***/
	snake_length = 5;
	clock_t a, b;
	char ch;
	double hard_len;
	for (int i = 0; i <= 4; i++)
	{
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}
	dir = 3;

	system("cls");
	cursor_hide();
	print_wall();
	create_food();
	Default_print_snake();
	cursor_locate(m + 2, 0);
	cout << "Now length: ";
	while (1)
	{
		
		hard_len = (double)snake_length / (double)(m*n);
		
		a = clock();
		while (1)
		{
			b = clock();
			if (b - a >= (int)(400 - 30 * hard)*(1 - sqrt(hard_len))) break;
		}
		
		if (_kbhit())
		{
			ch = _getch();
			
				switch (ch)
				{
				case 72:
					if (dir == 2 || dir == 3)
						dir = 0;
					break;
				case 80:
					if (dir == 2 || dir == 3)
						dir = 1;
					break;
				case 75:
					cout << "55" << endl;
					if (dir == 0 || dir == 1)
						dir = 2;
					break;
				case 77:
					if (dir == 0 || dir == 1)
						dir = 3;
					break;
				}
		}
		
		if (!snake_move()) break;
		
		cursor_locate(m + 2, 12);
		cout << snake_length;
	}
	system("pause");
    return 0;
}


void print_wall() {
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
	cout << endl;
	for (int j = 0; j <= m - 1; j++)
	{
		cout << "|";
		for (int i = 1; i <= n; i++) cout << " ";
		cout << "|" << endl;
	}
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
}


void cursor_locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

// 隐藏游標
void cursor_hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

void Default_print_snake() {
	cursor_locate(snake[0].x, snake[0].y);
	cout << "5";
	for (int i = 1; i <= snake_length - 1; i++)
	{
		cursor_locate(snake[i].x, snake[i].y);
		cout << "*";
	}
}

//判斷碰撞
bool if_correct()
{
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == m + 1 || snake[0].y == n + 1) return false;
	for (int i = 1; i <= snake_length - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return false;
	}
	return true;
}

//食物創造
bool create_food()
{
	srand((unsigned)time(0));
	bool e;
	while (1)
	{
		srand(time(NULL));
		e = true;
		int i = rand()%25 + 3, j = rand() % 41 + 3;
		food.x = i; food.y = j;
		for (int k = 0; k <= snake_length - 1; k++)
		{
			if (snake[k].x == food.x && snake[k].y == food.y)
			{
				e = false; break;
			}
		}
		if (e) break;
	}
	cursor_locate(food.x, food.y);
	cout << "$";
	return true;
}

bool snake_move() {
	node temp;
	bool check = false;
	temp = snake[snake_length - 1];

	snake[0].x += direct[dir][0];
	snake[0].y += direct[dir][1];
	cursor_locate(snake[1].x, snake[1].y);
	cout << "*";

	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		snake_length++;
		check = true;
		snake[snake_length - 1] = temp;
	}

	else if (!check)
	{
		cursor_locate(temp.x, temp.y);
		cout << "7";
	}
	else create_food();
	cursor_locate(snake[0].x, snake[0].y);
	cout << "6";

	if (!if_correct())
	{
		system("cls");
		cout << "You lose!" << endl << "Length: " << snake_length << endl;
		return false;
	}
	return true;

}
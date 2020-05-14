#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;


bool GameOver;
const int width = 60;
const int height = 30;
int x, y, fruitX, fruitY, score;
int TailX[50], TailY[50];
int nTail;
enum Direction
{
	Stop = 0, Left, Right, Up, Down
};
Direction dir;

void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Setup()
{
	GameOver = false;
	dir = Stop;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	clearScreen();

}



void Draw()
{

	clearScreen();

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";

			else
			{
				bool print = false;

				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}

		cout << endl;
	}


	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score : " << score << endl;
	cout << "Use w,a,s,d (Keys) to control the snake" << endl;
	cout << "Press Q if you want exit game" << endl;
	cout << "Press P if you want pause game" << endl;

}


void Input()
{
	if (_kbhit())
	{
		switch (_getch())

		{
		case 'w':
			dir = Up;
			break;

		case 's':
			dir = Down;
			break;

		case 'a':
			dir = Left;
			break;

		case 'd':
			dir = Right;
			break;

		case 'q':
			GameOver = true;
			break;

		case 'p':
			system("pause");
			break;
		}
	}
}

void Logic()
{
	int PrevX = TailX[0];
	int PrevY = TailY[0];
	int Prev2X;
	int Prev2Y;
	TailX[0] = x;
	TailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		Prev2X = TailX[i];
		Prev2Y = TailY[i];
		TailX[i] = PrevX;
		TailY[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;
	}

	switch (dir)
	{
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	default:
		break;

	}

	//if (x > width || x < 0 || y > height || y < 0) with limits
		//GameOver = true;

	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;


	for (int i = 0; i < nTail; i++)
	{
		if (TailX[i] == x && TailY[i] == y)
			GameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score = score + 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}


}

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}


int main()
{
	Setup();
	fullscreen();

	while (!GameOver)
	{

	Draw();
	Logic();
	Input();
	Sleep(30);
	
	}

	return 0;
}
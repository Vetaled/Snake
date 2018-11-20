#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>

using namespace std;
bool gameOver;
const int width = 26;
const int hight = 26;
int teil_x[100];
int teil_y[100];
int number_teil;
int snake_x, snake_y, fruit_x, fruit_y, score;

enum eDirection{STOP = 0, LEFT , RIGHT , UP , DOWN};
eDirection dir;

void Setup(); //стартовый блок
void Draw(); //блок поля
void Input(); //блок управления
void Logic(); //блок логики действий

int main()
{
	setlocale(LC_ALL, "Ru");
	Setup();
	while(!gameOver) 
	{
		Draw();
		Input();
		Logic();
		Sleep(150);
	}
	return 0;
}

void Setup()
{
	gameOver = false;
	dir = STOP;
	snake_x = width / 2 - 1;
	snake_y = hight / 2 - 1;
	srand((unsigned)time(NULL));
	fruit_x = rand() % width;
	fruit_y = rand() % hight;
	score = 0;
}

void Draw()
{
	system("cls"); //system("clear") удаляет надписи в консоли
	for(int i = 0 ; i < width+1 ; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == snake_y && j == snake_x) //координаты змейки
				cout << "!";
			else if (i == fruit_y && j == fruit_x) //координаты фрукта
				cout << "*";
			else
			{
				bool print = false;
				for(int k = 0; k<number_teil;k++) //рисование хвоста
				{
					if (teil_x[k] == j && teil_y[k] == i)
					{
						print = true; //отвечает за хвост или пробел
						cout << "|";
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < width+1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl; //очки
}

void Input()
{
	if(_kbhit()) //отслеживает на какую клавишу нажали
	{
		switch(_getch())
		{
		case'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':  //выход и з игры
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prev_x = teil_x[0]; //предыдущая позиция по х , изначально равна 0
	int prev_y = teil_y[0]; //предыдущая позиция по у , изначально равна 0
	int prev_2x, prev_2y;
	teil_x[0] = snake_x; //задаем 1ый член змейки головой 00
	teil_y[0] = snake_y;
	for (int i = 1; i < number_teil; i++) // i от 1 так как начальный элемент [0] уже записан
	{
		prev_2x = teil_x[i]; //помещаем 2ой элемент в хвосте и т.д перемещение хвоста
		prev_2y = teil_y[i];
		teil_x[i] = prev_x;
		teil_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;

	}
		switch (dir) //управление
	{
	case LEFT:
		snake_x--;
	 	break;
	case RIGHT:
		snake_x++;
		break;
	case UP:
		snake_y--;
		break;
	case DOWN:
		snake_y++;
		break;

	}

	/*if (snake_x > width || snake_x < 0 || snake_y > hight || snake_y < 0)
		gameOver = true; //бортики*/

		if (snake_x >= width-1) //переползание змейки з границы
			snake_x = 0;
		else if (snake_x < 0)
			snake_x = width - 2; //-2 так как были смещения

		if (snake_y >= hight)
			snake_y = 0;
		else if (snake_y < 0)
			snake_y = hight - 1;


	for(int i = 0; i < number_teil; i++)
	{
		if (teil_x[i] == snake_x && teil_y[i] == snake_y) // если голова попадает в хвост
			gameOver = true;
	}

	if (snake_x == fruit_x && snake_y == fruit_y) //поедание фрукта и появление нового фрукта
	{
		score+=10;
		srand((unsigned)time(NULL));
		fruit_x = rand() % width;
		fruit_y = rand() % hight;
		number_teil++;
	}
}
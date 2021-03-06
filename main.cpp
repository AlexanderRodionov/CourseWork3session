#include <iostream>
#include <cstring>
#include <windows.h>
#include "Rabbit.h"
#include "Wolf.h"
#include "Manager.h"

using namespace std;

bool gameOver = false;
int day = 0;

bool is_digit(const char* S) 
{
	const char* temp = "0123456789";

	for (int i = 0; i < strlen(S); i++)
	{
		if (!strchr(temp, S[i]))
		{
			cout << "Недопустимый формат введенного значения!" << "\n" 
				<< "Перепроверьте и введите еще раз." << endl;
			return false;
		}			
	}

	return true;
}

void Draw(int one, int two, int three, Manager *mng, int height, int width)
{	
	mng->ManageAnimalsTurn(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			switch (mng->AnimalsAtPos(i, j))
			{
			case 0: 
				cout << ". "; 
				break; 
			case 1: 
				cout << "R "; 
				break;
			case 3:
				cout << "S "; 
				break;
			case 5:
				cout << "W ";
				break;
			case 4:
				cout << "С "; 
				break;
			case 6:
				cout << "Z "; 
				break;
			case 8:
				cout << "G "; 
				break;
			case 9:
				cout << "B "; 
				break;
			default:
				cout << "! "; 
				break;
			}
		}
		cout << "\n";
	}
	cout << "\n" << "День: " << day << "\n" << "\n";
	cout << "Кроликов: " << mng->GetNumOfRabbits(height, width) << "\n" <<
		"Волчиц: " << mng->GetNumOfSheWolfes(height, width) << "\n" <<
		"Волков: " << mng->GetNumOfWolfes(height, width) << "\n";

	day++;
}

int main()
{
	setlocale(0, "");

	int rab = 0, wol = 0, swol = 0;
	int height = 5, width = 5;
	char S[20];

	cout << "ЗАПРОГРАММИРОВАННАЯ ЭКОЛОГИЧЕСКАЯ МОДЕЛЬ ВОЛЧЬЕГО ОСТРОВА" << "\n";		
	cout << "\n" << "ОБОЗНАЧЕНИЯ НА КАРТЕ:" << "\n" << 
		"R - кролик" << "\n" <<
		"S - волчица" << "\n" <<
		"W - волк" << "\n" <<
		"С - кролик + волчица" << "\n" <<
		"Z - кролик + волк" << "\n" <<
		"G - волк + волчица" << "\n" <<
		"B - кролик + волк + волчица" << "\n";
	
	cout << "\n" << "ВВЕДИТЕ НАЧАЛЬНЫЕ ПАРАМЕТРЫ" << "\n";
tryAgain:
	cout << "Высота поля: " << endl;
	cin.getline(S, 20);
	while (!is_digit(S))
	{
		cin.getline(S, 20);
	}
	height = atoi(S);
	
	cout << "Ширина поля: " << endl;
	cin.getline(S, 20);
	while (!is_digit(S))
	{
		cin.getline(S, 20);
	}
	width = atoi(S);

	if ((height == 0) || (width == 0))
	{
		cout << "Недопустимые размеры поля (" << height << " на " << width << ") , повторите ввод размеров!" << endl;
		goto tryAgain;
	}
	cout << "Задано поле " << height << " на " << width << endl;
	cout << "Количество представителей каждого вида не больше " << height * width / 3 << endl;
rabAgain:
	cout << "Количество Кроликов: " << endl;
	cin.getline(S, 20);
	while (!is_digit(S))
	{
		cin.getline(S, 20);
	}
	rab = atoi(S);
	if (rab > height * width / 3)
	{
		cout << "Слишком много!" << endl;
		goto rabAgain;
	}
wolAgain: 
	cout << "Количество Волков: " << endl;
	cin.getline(S, 20);
	while (!is_digit(S))
	{
		cin.getline(S, 20);
	}
	wol = atoi(S);
	if (wol > height * width / 3)
	{
		cout << "Слишком много!" << endl;
		goto wolAgain;
	}
swolAgain:
	cout << "Количество Волчиц: " << endl;
	cin.getline(S, 20);
	while (!is_digit(S))
	{
		cin.getline(S, 20);
	}
	swol = atoi(S);
	if (swol > height * width / 3)
	{
		cout << "Слишком много!" << endl;
		goto swolAgain;
	}
			
	Manager *mng = new Manager(rab, swol, wol, height, width);

	while (!gameOver)
	{
		system("cls");

		Draw(rab, swol, wol, mng, height, width);	

		if ((mng->GetNumOfRabbits(height, width) == 0) && (mng->GetNumOfSheWolfes(height, width) == 0))
		{
			gameOver = true;
			continue;
		}
		if ((mng->GetNumOfRabbits(height, width) == 0) && (mng->GetNumOfWolfes(height, width) == 0))
		{
			gameOver = true;
			continue;
		}
		if ((mng->GetNumOfSheWolfes(height, width) == 0) && (mng->GetNumOfWolfes(height, width) == 0))
		{
			gameOver = true;
			continue;
		}

		Sleep(40);
	}
	
	system("pause");
	return 0;
}

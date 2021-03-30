#include "Manager.h"
#include "Rabbit.h"
#include "Wolf.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Manager::Manager(int _numOfRabbits, int _numOfSheWolfes, int _numOfWolfes, int height, int width) : 
	numOfRabbits(_numOfRabbits), numOfSheWolfes(_numOfSheWolfes), numOfWolfes(_numOfWolfes)
{
	srand(time(NULL));

	vecOfRabbits = new vector<Rabbit>;
	vecOfSheWolfes = new vector<Wolf>;
	vecOfWolfes = new vector<Wolf>;

	for (int i = 0; i < numOfRabbits; i++)
	{
		vecOfRabbits->push_back(Rabbit(rand() % height, rand() % width));
	}

	for (int i = 0; i < numOfSheWolfes; i++)
	{
		vecOfSheWolfes->push_back(Wolf(rand() % height, rand() % width));
	}

	for (int i = 0; i < numOfWolfes; i++)
	{
		vecOfWolfes->push_back(Wolf(rand() % height, rand() % width));
	}
}

Manager :: ~Manager()
{
	delete vecOfRabbits;
	delete vecOfSheWolfes;
	delete vecOfWolfes;
}

int* Manager::GetRabbitsAround(int xPos, int yPos)
{
	int* arr = new int[3];

	for (unsigned int i = 0; i < vecOfRabbits->size(); i++)
	{
		Rabbit* tempRab = &vecOfRabbits->at(i);
		if ((tempRab->GetXPos() >= xPos - 1) && (tempRab->GetXPos() <= xPos + 1) &&
			(tempRab->GetYPos() >= yPos - 1) && (tempRab->GetYPos() <= yPos + 1))
		{
			arr[0] = i;
			arr[1] = tempRab->GetXPos();
			arr[2] = tempRab->GetYPos();
			return arr;
		}
	}
	arr[0] = -1;
	return arr;
}

int* Manager::GetSheWolfesAround(int xPos, int yPos)
{
	int* arr = new int[3];

	for (unsigned int i = 0; i < vecOfSheWolfes->size(); i++)
	{
		Rabbit* tempWolf = &vecOfSheWolfes->at(i);

		if ((tempWolf->GetXPos() >= xPos - 1) && (tempWolf->GetXPos() <= xPos + 1) &&
			(tempWolf->GetYPos() >= yPos - 1) &&(tempWolf->GetYPos() <= yPos + 1))
		{
			arr[0] = i;
			arr[1] = tempWolf->GetXPos();
			arr[2] = tempWolf->GetYPos();

			return arr;
		}
	}

	arr[0] = -1;
	return arr;
}

void Manager::MoveRabbits(int height, int width)
{
	for (unsigned int i = 0; i < vecOfRabbits->size(); i++)
	{
		Rabbit* tempRab = &vecOfRabbits->at(i);

		if ((rand() % 5 == 0) && (numOfRabbits <= (height*width/3))) 
		{
			vecOfRabbits->push_back(Rabbit(tempRab->GetXPos(), tempRab->GetYPos()));
			numOfRabbits++;
		}

		tempRab->MoveTo(rand() % 9 + 1, height, width);
	}
}

void Manager::MoveSheWolfes(int height, int width)
{
	for (unsigned int i = 0; i < vecOfSheWolfes->size(); i++)
	{
		Wolf* tempWolf = &vecOfSheWolfes->at(i);

		if (tempWolf->GetScore() == 0)
		{
			vecOfSheWolfes->erase(vecOfSheWolfes->begin() + i);
			numOfSheWolfes--;
			continue;
		}

		int* arr = GetRabbitsAround(tempWolf->GetXPos(), tempWolf->GetYPos());

		if (arr[0] != -1)
		{
			if (tempWolf->GetXPos() == arr[1] && tempWolf->GetYPos() == arr[2])
			{
				vecOfRabbits->erase(vecOfRabbits->begin() + arr[0]);
				numOfRabbits--;
				tempWolf->AddScore(10);
				delete arr;
				continue;
			}
			else
			{
				tempWolf->MoveTo(arr[1], arr[2], height, width);
				tempWolf->AddScore(-1);
				delete arr;
				continue;
			}
		}

		tempWolf->MoveTo(rand() % 9 + 1, height,  width); 
		tempWolf->AddScore(-1);
		delete arr;
	}
}

void Manager::MoveWolfes(int height, int width)
{
	for (unsigned int i = 0; i < vecOfWolfes->size(); i++)
	{
		Wolf* tempWolf = &vecOfWolfes->at(i);

		if (tempWolf->GetScore() == 0)
		{
			vecOfWolfes->erase(vecOfWolfes->begin() + i);
			numOfWolfes--;
			continue;
		}

		int* arr = GetRabbitsAround(tempWolf->GetXPos(), tempWolf->GetYPos());

		if (arr[0] != -1)
		{
			if (tempWolf->GetXPos() == arr[1] && tempWolf->GetYPos() == arr[2])
			{
				vecOfRabbits->erase(vecOfRabbits->begin() + arr[0]);
				numOfRabbits--;
				tempWolf->AddScore(10);
				delete arr;
				continue;
			}
			else
			{
				tempWolf->MoveTo(arr[1], arr[2],  height,  width);
				tempWolf->AddScore(-1);
				delete arr;
				continue;
			}
		}

		delete arr;
		arr = GetSheWolfesAround(tempWolf->GetXPos(), tempWolf->GetYPos());

		if (arr[0] != -1) 
		{
			if (tempWolf->GetXPos() == arr[1] && tempWolf->GetYPos() == arr[2])
			{
				if ((rand() % 2 == 0) && (numOfSheWolfes <= (height*width/3)))
				{
					vecOfSheWolfes->push_back(Wolf(arr[1], arr[2]));
					numOfSheWolfes++;
				}
				else if (numOfWolfes <= (height*width/3))
				{
					vecOfWolfes->push_back(Wolf(arr[1], arr[2]));
					numOfWolfes++;
				}

				delete arr;
				continue;
			}
			else
			{
				tempWolf->MoveTo(arr[1], arr[2],  height,  width);
				tempWolf->AddScore(-1);
				delete arr;
				continue;
			}
		}

		tempWolf->MoveTo(rand() % 9 + 1,  height,  width);
		tempWolf->AddScore(-1);
		delete arr;
	}
}

void Manager::ManageAnimalsTurn(int height, int width)
{
	MoveRabbits(  height,  width);
	MoveSheWolfes(height, width);
	MoveWolfes(height, width);
}

int Manager::AnimalsAtPos(int xPos, int yPos)
{
	int result = 0;

	for (unsigned int i = 0; i < vecOfRabbits->size(); i++)
	{
		Rabbit* tempRab = &vecOfRabbits->at(i);

		if (tempRab->GetXPos() == xPos && tempRab->GetYPos() == yPos)
		{
			result++;
			break;
		}
	}

	for (unsigned int i = 0; i < vecOfSheWolfes->size(); i++)
	{
		Wolf* tempWolf = &vecOfSheWolfes->at(i);

		if (tempWolf->GetXPos() == xPos && tempWolf->GetYPos() == yPos)
		{
			result += 3;
			break;
		}
	}

	for (unsigned int i = 0; i < vecOfWolfes->size(); i++)
	{
		Wolf* tempWolf = &vecOfWolfes->at(i);

		if (tempWolf->GetXPos() == xPos && tempWolf->GetYPos() == yPos)
		{
			result += 5;
			break;
		}
	}

	return result;
}

int Manager::GetNumOfRabbits(int height, int width)
{
	return numOfRabbits; 
}

int Manager::GetNumOfSheWolfes(int height, int width)
{
	return numOfSheWolfes; 
}

int Manager::GetNumOfWolfes(int height, int width)
{
	return numOfWolfes;
}

Manager::Manager()
{

}

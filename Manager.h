#ifndef MANAGER_H
#define MANAGER_H

#include <vector>

using namespace std;

class Rabbit;
class Wolf;
class Manager
{
private:
	vector <Rabbit>* vecOfRabbits;
	vector <Wolf>* vecOfSheWolfes;
	vector <Wolf>* vecOfWolfes;
	
	int numOfRabbits;
	int numOfSheWolfes;
	int numOfWolfes;
	
	int* GetRabbitsAround(int xPos, int yPos);
	int* GetSheWolfesAround(int xPos, int yPos);

	void MoveRabbits(int height, int width);
	void MoveSheWolfes(int height, int width);
	void MoveWolfes(int height, int width);
	
public:
	Manager(int _numOfRabbits , int _numOfSheWolfes , int _numOfWolfes, int height, int width);
	void ManageAnimalsTurn(int height, int width);
	int AnimalsAtPos(int xPos, int yPos);
	int GetNumOfRabbits(int height, int width);
	int GetNumOfSheWolfes(int height, int width);
	int GetNumOfWolfes(int height, int width);
	Manager();
	~Manager();
};

#endif // MANAGER_H
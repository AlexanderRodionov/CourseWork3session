#include "Wolf.h"

Wolf::Wolf(int xPos, int yPos) : Rabbit(xPos, yPos), _score(10) 
{
	
}

int Wolf::GetScore()
{
	return _score; 
}

void Wolf::AddScore(int score)
{
	_score += score; 
}

Wolf::Wolf()
{
}

Wolf::~Wolf()
{
}

#ifndef WOLF_H
#define WOLF_H

#include "Rabbit.h"

class Wolf : public Rabbit
{
private:
	int _score;
public:
	Wolf(int xPos, int yPos);
	int GetScore();
	void AddScore(int score);
	Wolf();
	~Wolf();
};

#endif // WOLF_H

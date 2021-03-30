#ifndef RABBIT_H
#define RABBIT_H

class Rabbit
{
private:
	int _xPos, _yPos;
public:
	Rabbit(int xPos, int yPos);
	int GetXPos();
	int GetYPos();
	void MoveTo(int way, int height, int width);
	void MoveTo(int xPos, int yPos, int height, int width);
	Rabbit();
	~Rabbit();
};

#endif // RABBIT_H

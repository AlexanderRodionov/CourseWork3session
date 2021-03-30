#include "Rabbit.h"

Rabbit::Rabbit(int xPos, int yPos) : _xPos(xPos), _yPos(yPos)
{

}

int Rabbit::GetXPos()
{
	return _xPos;
}

int Rabbit::GetYPos()
{
	return _yPos; 
}

void Rabbit::MoveTo(int way, int height, int width)
{
	if (way < 1 || way > 9 || way == 5) 
	{
		return;
	}

	switch (way)
	{
	case 1:
		_xPos == 0 ? _xPos : _xPos--; 
		_yPos == 0 ? _yPos : _yPos--; 
		break;
	case 2:
		_xPos == 0 ? _xPos : _xPos--;
		break;
	case 3:
		_xPos == 0 ? _xPos : _xPos--;
		_yPos == (width - 1) ? _yPos : _yPos++;
		break;
	case 4:
		_yPos == 0 ? _yPos : _yPos--;
		break;
	case 6:
		_yPos == (width - 1) ? _yPos : _yPos++;
		break;
	case 7:
		_xPos == (height - 1) ? _xPos : _xPos++;
		_yPos == 0 ? _yPos : _yPos--;
		break;
	case 8:
		_xPos == (height - 1) ? _xPos : _xPos++;
		break;
	case 9:
		_xPos == (height - 1) ? _xPos : _xPos++;
		_yPos == (width - 1) ? _yPos : _yPos++;
		break;
	}
}

void Rabbit::MoveTo(int xPos, int yPos, int height, int width)
{
	if (xPos >= 0 && xPos < height)
	{
		_xPos = xPos;
	}
	if (yPos >= 0 && yPos < width)
	{
		_yPos = yPos;
	}
}

Rabbit::Rabbit()
{
}

Rabbit::~Rabbit()
{
}

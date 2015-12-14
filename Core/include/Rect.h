#ifndef _RECT_H
#define _RECT_H

class Rect
{
public:
	float x;
	float y;
	float width;
	float height;

	Rect()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

#endif
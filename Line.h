#pragma once
#include "Point.h"
class Line
{
public:
	Line(int, int, int, int);
	Line(void);
	~Line(void);
	void set_point(int x, int y);
	void draw(void);
	Point point_from;
	Point point_to;
	Point cropped_point_from;
	Point cropped_point_to;
	short flag_from;
	short flag_to;
private:
	short flag;
};


#pragma once
#include "Line.h"
#include "Parent.h"

class Square : public Parent{
public:
	Square(void);	
	virtual void citio(Line * line_in);
	virtual void addPoint(double x, double y);
	virtual void draw(void);
private:
	Point left_down;
	Point right_top;
	short flag;
	int reccur_citio(Line * line_in, Line* line_result);
	void add_flag_to_point(Line * line_in);
};
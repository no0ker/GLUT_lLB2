#pragma once
#include <vector>
#include "Point.h"
#include "Line.h"
#include "Parent.h"

class Polygon : public Parent
{
public:
	~Polygon(void);

	virtual void addPoint(double x, double y);
	virtual void draw(void);
	virtual void citio(Line* line_in);

	std::vector<Point> points;
	std::vector<Point> points_normal;
	
private:
	bool lines_is_right;
	void add_Normals(void);
	bool is_Convex(void);
};


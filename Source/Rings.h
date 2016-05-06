#ifndef RINGS_H
#define RINGS_H
#include <vector>
#include <GL/glut.h>
#include <Windows.h>
#include <MMSystem.h>
#include "Geometry.h"
#include "Point3.h"

using namespace std;

class Rings
{
public:
	void draw(bool, Point3 currentPos);
	Rings();

private:
	vector<Point3> positions;
	vector<float> angles;
	int currentRing;
	void ring(bool, Point3, float);
	bool detectCollision(Point3);
};

#endif
#ifndef POINT3_H
#define POINT3_H
#include <iostream>

using namespace std;

class Point3
{
public:
	float x, y, z;
	void set(float, float, float);
	void set(Point3&);
	Point3(float, float, float);
	Point3();
	void build4tuple(float []);
};
#endif
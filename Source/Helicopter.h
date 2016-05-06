#ifndef HELICOPTER_H
#define HELICOPTER_H
#include <iostream>
#include <GL/glut.h>
#include "Body.h"
#include "Cockpit.h"
#include "Tail.h"

using namespace std;

class Helicopter
{
private:
	Body body;
	Tail tail;
	Cockpit cockpit;
	bool highBeam;
	bool lightOn;
	float rotorsRotationAngle;
	float helicopterAngleZ;
	float helicopterAngleY;
	float helicopterAngleX;

public:
	Helicopter();
	void setParameters(bool, bool, float, float, float, float);
	void draw(bool);
};
#endif
#ifndef BODY_H
#define BODY_H
#include <iostream>
#include <GL/glut.h>
#include "ImageLoader.h"
#include "Geometry.h"

using namespace std;

class Body
{
public:
	Body();
	void draw(bool type, bool beam, bool light, float rotAngle);

private:
	bool highBeam;
	bool lightOn;
	float rotorsRotationAngle;
	GLuint _textureId[2];

	GLuint loadTexture(Image*);
	void landingGear(bool);
	void under(bool);
	void back(bool);
	void floor(bool);
	void top(bool);
	void bigDoors(bool);
	void smallDoors(bool);
	void engine(bool);
	void rotor(bool);
	void spotLight();
	void rotatingLight();
};
#endif
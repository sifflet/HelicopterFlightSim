#ifndef TAIL_H
#define TAIL_H
#include <iostream>
#include <GL/glut.h>
#include "ImageLoader.h"
#include "Geometry.h"

using namespace std;

class Tail
{
public:
	Tail();
	void draw(bool, float);

private:
	float rotorsRotationAngle;

	GLuint _textureId[2];

	GLuint loadTexture(Image*);
	void mainPart(bool);
	void endPart(bool);
	void wings(bool);
	void rotor(bool);
};
#endif
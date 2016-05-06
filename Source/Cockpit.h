#ifndef COCKPIT_H
#define COCKPIT_H
#include <iostream>
#include <GL/glut.h>
#include "Geometry.h"
#include "ImageLoader.h"

using namespace std;

class Cockpit
{
public:
	void draw(bool);
	Cockpit();

private:
	GLuint _textureId[2];

	GLuint loadTexture(Image*);
	void seatArea(bool);
	void nose(bool);
};
#endif
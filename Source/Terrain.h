#ifndef TERRAIN_H
#define TERRAIN_H
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "Point3.h"
#include "Vector3.h"
#include "ImageLoader.h"
#include "ObjLoader.h"
#include "HeightmapLoader.h"
#include "Geometry.h"

using namespace std;

class Terrain
{
public:
	Terrain();
	void draw(bool);

private:
	vector<Point3> vertices;
	vector<vector<GLuint>> faces;
	vector<Vector3> normals;
	HeightmapLoader hml;

	GLuint _textureId[3];

	GLuint loadTexture(Image*);

	Vector3 calculateNormal(Point3);
	void surfaceObj();
	void surfaceHMap();
	void map();
};

#endif
#ifndef OBJLOADER_H
#define OBJLOADE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include <vector>
#include "Vector3.h"
#include "Point3.h"

using namespace std;

class ObjLoader
{
private:
	Vector3 calculateNormal(vector<GLuint>);
	vector<Point3> vertices;
	vector<Vector3> normals;
	vector<vector<GLuint>> faces;
public:
	vector<Point3> getVertices();
	vector<Vector3> getNormals();
	vector<vector<GLuint>> getFaces();
	void loadObj(const char*);
};
#endif
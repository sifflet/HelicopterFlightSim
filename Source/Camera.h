#ifndef CAMERA_H
#define CAMERA_H
#include "Point3.h"
#include "Vector3.h"
#include <GL/glut.h>

using namespace std;

class Camera
{
private:
	Point3 eye;
	Point3 look;
	Vector3 u, v, n;
	int rotatedZ;
	float movedX;
	float movedY;
	float movedZ;

public:

	void setModelviewMatrix();
	Camera();
	Point3 getEye();
	Vector3 getUpVec();
	void reset();
	void set(Point3, Point3, Vector3, float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(int);
	void slide(float, float, float);
	void move(Vector3);
};
#endif
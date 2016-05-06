#ifndef VECTOR3_H
#define VECTOR3_H
#include <math.h>
#include "Point3.h"

using namespace std;

class Vector3
{
public:
	float x, y, z;
	void set(float, float, float);
	void set(Vector3& v);
	Vector3 flip();
	Vector3(float, float, float);
	Vector3(const Vector3&);
	Vector3();
	float getVector3Length();
	void normalizeVector3();
	Vector3 operator+ (const Vector3&) const;
	Vector3 operator- (const Vector3&) const;
	Vector3 operator* (const float) const;
	float operator* (const Vector3&) const;
	Vector3 cross(Vector3);
};
#endif
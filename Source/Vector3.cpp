#include "Vector3.h"

using namespace std;

void Vector3::set(float dx, float dy, float dz)
{
	x = dx;
	y = dy;
	z = dz;
}

void Vector3::set(Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 Vector3::flip()
{
	return Vector3(this->x * -1, this-> y * -1, this->z * -1);
}

Vector3::Vector3(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3()
{
	x = y = z = 0;
}

float Vector3::getVector3Length()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vector3::normalizeVector3()
{
	float length = getVector3Length();

	if(length != 0)
	{
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}
}

Vector3 Vector3::operator+ (const Vector3& v) const
{
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator- (const Vector3& v) const
{
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator* (float r) const
{
	return Vector3(this->x * r, this->y * r, this->z * r);
}

// Dot product
float Vector3::operator* (const Vector3& v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3 Vector3::cross(Vector3 v)
{
	Vector3 result = Vector3();

	result.x = this->y * v.z - this->z * v.y;
	result.y = this->z * v.x - this->x * v.z;
	result.z = this->x * v.y - this->y * v.x;

	return result;
}

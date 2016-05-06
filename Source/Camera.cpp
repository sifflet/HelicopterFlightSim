#include "Camera.h"

using namespace std;


Camera::Camera()
{
	eye = Point3();
	u = Vector3(1.0, 0.0, 0.0);
	v = Vector3(0.0, 1.0, 0.0);
	n = Vector3(0.0, 0.0, -1.0);

	movedX = 0;
	movedY = 0;
	movedZ = 0;

	setModelviewMatrix();
}

Point3 Camera::getEye()
{
	return this->eye;
}

Vector3 Camera::getUpVec()
{
	return this->u;
}

void Camera::setModelviewMatrix()
{
	float m[16];

	Vector3 eVec(eye.x, eye.y, eye.z);

	m[0] = u.x; m[4] = u.y; m[8] = u.z;  m[12] = -(eVec*u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z;  m[13] = -(eVec*v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -(eVec*n);
	m[3] = 0;   m[7] = 0;   m[11] = 0;   m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::reset()
{
	eye = Point3();
	u = Vector3(1.0, 0.0, 0.0);
	v = Vector3(0.0, 1.0, 0.0);
	n = Vector3(0.0, 0.0, -1.0);

	rotatedZ = 0.0;
	setModelviewMatrix();
}

void Camera::set(Point3 Eye, Point3 Look, Vector3 up, float rotationZ)
{
	this->eye.set(Eye);
	this->look.set(Look);

	this->movedX = Look.x;
	this->movedY = Look.y;
	this->movedZ = Look.z;
	this->rotatedZ = rotationZ;

	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);

	u.set(n.cross(up));
	n.normalizeVector3();
	u.normalizeVector3();
	v.set(u.cross(n));
	setModelviewMatrix();
}

// Roll
void Camera::rotateX(float angle)
{
	float cs = cos(3.14159265/180 * angle);
	float sn = sin(3.14159265/180 * angle);

	Vector3 t(u);
	u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z);
	setModelviewMatrix();
}

// Pitch
void Camera::rotateY(float angle)
{
	float cs = cos(3.14159265/180 * angle);
	float sn = sin(3.14159265/180 * angle);

	Vector3 rotAxis(u.flip());
	Point3 eyeO(eye.x - movedX, eye.y - movedY, eye.z - movedZ);

	float p1 = (pow(rotAxis.x,2)+(1-pow(rotAxis.x,2))*cs)*eyeO.x + (rotAxis.x*rotAxis.y*(1-cs)+rotAxis.z*sn)*eyeO.y + (rotAxis.x*rotAxis.z*(1-cs)-rotAxis.y*sn)*eyeO.z;
	float p2 = (rotAxis.x*rotAxis.y*(1-cs)-rotAxis.z*sn)*eyeO.x + (pow(rotAxis.y,2)+(1-pow(rotAxis.y,2))*cs)*eyeO.y + (rotAxis.y*rotAxis.z*(1-cs)+rotAxis.x*sn)*eyeO.z;
	float p3 = (rotAxis.x*rotAxis.z*(1-cs)+rotAxis.y*sn)*eyeO.x + (rotAxis.y*rotAxis.z*(1-cs)-rotAxis.x*sn)*eyeO.y + (pow(rotAxis.z,2)+(1-pow(rotAxis.z,2))*cs)*eyeO.z;

	eye.set(p1 + movedX, p2 + movedY, p3 + movedZ);

	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	n.normalizeVector3();
	
	v.set(u.cross(n));
	v.normalizeVector3();

	setModelviewMatrix();
}

/*
 *	Yaw
 */
void Camera::rotateZ(int angle)
{
	float cs = cos(3.14159265/180 * angle);
	float sn = sin(3.14159265/180 * angle);

	Point3 eyeO(eye.x - movedX, 0.0, eye.z - movedZ);
	
	float p1 = cs*eyeO.x - sn*eyeO.z;
	float p3 = sn*eyeO.x + cs*eyeO.z;

	eye.set(p1 + movedX, eye.y, p3 + movedZ);

	rotatedZ += angle;

	double circleTangentSlope = 0;

	switch(rotatedZ)
	{
		case 90:
		case -270:
			u.set(0.0, 0.0, 1.0);
			break;
		case 180:
		case -180:
			u.set(-1.0, 0.0, 0.0);
			break;
		case 270:
		case -90:
			u.set(0.0, 0.0, -1.0);
			break;
		case 360:
		case -360:
			rotatedZ = 0;
		case 0:
			u.set(1.0, 0.0, 0.0);
			break;
			
		default:
			circleTangentSlope = -(eye.x - movedX) / (eye.z - movedZ); // using the derivative of the equation of a circle

			if((rotatedZ > 0 && rotatedZ < 90) || (rotatedZ < -270 && rotatedZ > -360))
			{
				u.set(1.0, 0.0, circleTangentSlope);
			}
			else if((rotatedZ > 90 && rotatedZ < 180) || (rotatedZ < -180 && rotatedZ > -270))
			{
				u.set(-1.0, 0.0, -circleTangentSlope);
			}
			else if((rotatedZ > 180 && rotatedZ < 270) || (rotatedZ < -90 && rotatedZ > -180))
			{
				u.set(-1.0, 0.0, -circleTangentSlope);
			}
			else if((rotatedZ > 270 && rotatedZ < 360) || (rotatedZ < 0 && rotatedZ > -90))
			{
				u.set(1.0, 0.0, circleTangentSlope);
			}
			break;
	}
	u.normalizeVector3();
	
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	n.normalizeVector3();
	
	v.set(u.cross(n));
	v.normalizeVector3();
	
	setModelviewMatrix();
}

void Camera::slide(float delU, float delV, float delN)
{
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	setModelviewMatrix();
}

void Camera::move(Vector3 newLook)
{
	this->look.set(look.x + newLook.x, look.y + newLook.y, look.z + newLook.z);
	eye.set(eye.x + newLook.x, eye.y + newLook.y, eye.z + newLook.z);

	movedX += newLook.x;
	movedY += newLook.y;
	movedZ += newLook.z;

	setModelviewMatrix();
}
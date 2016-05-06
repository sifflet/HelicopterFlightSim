#include "Helicopter.h"

using namespace std;

Helicopter::Helicopter()
{
	this->highBeam = false;
	this->lightOn = false;
	this->rotorsRotationAngle = 0;
	this->helicopterAngleZ = 0;
	this->helicopterAngleY = 0;
	this->helicopterAngleX = 0;

	this->body = Body();
	this->tail = Tail();
	this->cockpit = Cockpit();
}

void Helicopter::setParameters(bool beam, bool light, float rotAngle, float heliAngleZ, float heliAngleY, float heliAngleX)
{
	this->highBeam = beam;
	this->lightOn = light;
	this->rotorsRotationAngle = -rotAngle;
	this->helicopterAngleZ = heliAngleZ;
	this->helicopterAngleY = heliAngleY;
	this->helicopterAngleX = heliAngleX;
}

void Helicopter::draw(bool type)
{
	glPushMatrix();
	glRotatef(this->helicopterAngleX, 0.0, 1.0, 0.0);
	glRotatef(this->helicopterAngleZ, 0.0, 0.0, 1.0);
	glRotatef(this->helicopterAngleY, 1.0, 0.0, 0.0);
	body.draw(type, highBeam, lightOn, rotorsRotationAngle);
	cockpit.draw(type);
	tail.draw(type, rotorsRotationAngle);
	glPopMatrix();
}
#include "Rings.h"

using namespace std;

Rings::Rings()
{
	this->currentRing = 0;
	//up
	positions.push_back(Point3(0.0, 100.0, 300.0));
	angles.push_back(0.0);

	positions.push_back(Point3(0.0, 300.0, 900.0));
	angles.push_back(0.0);

	positions.push_back(Point3(0.0, 400.0, 1200.0));
	angles.push_back(0.0);

	// strafe
	positions.push_back(Point3(-100.0, 500.0, 2000.0));
	angles.push_back(0.0);

	positions.push_back(Point3(100.0, 500.0, 2500.0));
	angles.push_back(0.0);

	positions.push_back(Point3(-150.0, 300.0, 3000.0));
	angles.push_back(0.0);

	positions.push_back(Point3(175.0, 400.0, 3700.0));
	angles.push_back(0.0);

	//up
	positions.push_back(Point3(175.0, 800.0, 5000.0));
	angles.push_back(0.0);

	positions.push_back(Point3(200.0, 900.0, 6000.0));
	angles.push_back(0.0);

	positions.push_back(Point3(-300.0, 1750.0, 7500.0));
	angles.push_back(-22.5);

	positions.push_back(Point3(-500.0, 2000.0, 8000.0));
	angles.push_back(-45.0);

	positions.push_back(Point3(-1000.0, 2500.0, 8500.0));
	angles.push_back(-90.0);

	positions.push_back(Point3(-1500.0, 2400.0, 8000.0));
	angles.push_back(-135.0);

	//down
	positions.push_back(Point3(-2000.0, 1800.0, 7600.0));
	angles.push_back(-135.0);

	positions.push_back(Point3(-3500.0, 500.0, 7600.0));
	angles.push_back(-90.0);

	positions.push_back(Point3(-5700.0, 1300.0, 7600.0));
	angles.push_back(-90.0);

	positions.push_back(Point3(-6300.0, 600.0, 6500.0));
	angles.push_back(-180.0);

}

void Rings::ring(bool type, Point3 position, float angle)
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle, 0, 1, 0);
		torus(type);
	glPopMatrix();
}

bool Rings::detectCollision(Point3 heliPos)
{
	float bound = 7.0;
	bool result = false;
	Point3 ringPos = positions[currentRing];

	if(heliPos.z <= ringPos.z + bound && heliPos.z >= ringPos.z - bound)
	{
		if(heliPos.x <= ringPos.x + bound && heliPos.x >= ringPos.x - bound)
		{
			if(heliPos.y <= ringPos.y + bound && heliPos.y >= ringPos.y - bound)
			{
				result = true;
			}
		}
	}

	return result;
}

void Rings::draw(bool type, Point3 currentPos)
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 0.0, 0.0);

	ring(type, positions[currentRing], angles[currentRing]);
	
	glColor3f(0.0, 1.0, 0.0);

	ring(type, positions[currentRing+1], angles[currentRing+1]);
	ring(type, positions[currentRing+2], angles[currentRing+2]);

	if(detectCollision(currentPos))
	{
		currentRing++;
	}

	if(currentRing == positions.size() - 1)
	{
		currentRing = 0;
	}

	glDisable(GL_COLOR_MATERIAL);
}

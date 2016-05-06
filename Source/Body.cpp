#include "Body.h"

using namespace std;

Body::Body()
{
	Image* image = loadBMP("Metal.bmp");
	_textureId[0] = loadTexture(image);

	image = loadBMP("Metal2.bmp");
	_textureId[1] = loadTexture(image);
	delete image;
}

GLuint Body::loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

void Body::landingGear(bool type)
{
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.06, 0.06, 3);
	glTranslatef(-28, -17, -0.6);
	cylinder(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.06, 0.06, 3);
	glTranslatef(28, -17, -0.6);
	cylinder(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 1, 0, 0);
	glScalef(0.06, 0.06, 0.7);
	glTranslatef(-20, -7, 1.4);
	cylinder(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 1, 0, 0);
	glScalef(0.06, 0.06, 0.7);
	glTranslatef(20, -7, 1.4);
	cylinder(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(-45, 1, 0, 0);
	glScalef(0.06, 0.06, 0.7);
	glTranslatef(-20, 7, 1.4);
	cylinder(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(-45, 1, 0, 0);
	glScalef(0.06, 0.06, 0.7);
	glTranslatef(20, 7, 1.4);
	cylinder(type, _textureId[1]);
	glPopMatrix();
}

void Body::under(bool type)
{
	GLdouble clipPlane1[] = {0, -1, 0, -0.5};

	glEnable(GL_CLIP_PLANE1);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(1.4, 1, 3.88);
	glTranslatef(0, 0.5, -0.75);
	glClipPlane(GL_CLIP_PLANE1, clipPlane1);
	cylinder(type, _textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE1);
}

void Body::back(bool type)
{
	GLdouble clipPlane1[] = {0, 1, 0, -0.15};
	GLdouble clipPlane2[] = {0, 0, -1, 1.8};
	GLdouble clipPlane3[] = {-0.31, 0, 1, 0.34};
	GLdouble clipPlane4[] = {-0.31, 0, -1, 0.34};

	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE2);

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(1.85, 1.5, 1);
	glTranslatef(0, -0.5, 1.7);
	glClipPlane(GL_CLIP_PLANE1, clipPlane1);
	glClipPlane(GL_CLIP_PLANE2, clipPlane2);
	cone(type, _textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);

	glPushMatrix();
	glRotatef(35, 0, 1, 0);
	glScalef(1.8, 1.3, 0.1);
	glTranslatef(0.8, 0.9, 24);
	cube(_textureId[0]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-35, 0, 1, 0);
	glScalef(1.8, 1.3, 0.1);
	glTranslatef(0.8, 0.9, -24);
	cube(_textureId[0]);
	glPopMatrix();

	glEnable(GL_CLIP_PLANE3);
	glEnable(GL_CLIP_PLANE4);

	glPushMatrix();
	glScalef(1.5, 0.1, 3.4);
	glTranslatef(1.7, 18, 0);
	glClipPlane(GL_CLIP_PLANE3, clipPlane3);
	glClipPlane(GL_CLIP_PLANE4, clipPlane4);
	cube(_textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE3);
	glDisable(GL_CLIP_PLANE4);
}

void Body::floor(bool type)
{
	glPushMatrix();
	glScalef(3.6, 0.1, 3.2);
	cube(_textureId[0]);
	glPopMatrix();
}

void Body::top(bool type)
{
	glPushMatrix();
	glScalef(3.6, 0.1, 3.2);
	glTranslatef(0, 18, 0);
	cube(_textureId[0]);
	glPopMatrix();
}

void Body::bigDoors(bool type)
{
	glPushMatrix();
	glScalef(2.4, 1.8, 0.1);
	glTranslatef(0.25, 0.5, 16.8);
	cube(_textureId[0]);
	glTranslatef(0, 0, -33.6);
	cube(_textureId[0]);
	glPopMatrix();

	// Windows
	glColor3ub(0.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(1, 0.7, 0.1);
	glTranslatef(0.1, 1.7, 17);
	cube(NULL);
	glTranslatef(1.1, 0, 0);
	cube(NULL);
	glTranslatef(0, 0, -34);
	cube(NULL);
	glTranslatef(-1.1, 0, 0);
	cube(NULL);
	glPopMatrix();

	glColor3ub(64, 95, 0);
}

void Body::smallDoors(bool type)
{
	glPushMatrix();
	glRotatef(-10.0, 0, 1, 0);
	glScalef(1.2, 1.8, 0.1);
	glTranslatef(-0.75, 0.5, 17.9);
	cube(_textureId[0]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(10.0, 0, 1, 0);
	glScalef(1.2, 1.8, 0.1);
	glTranslatef(-0.75, 0.5, -17.9);
	cube(_textureId[0]);
	glPopMatrix();
}

void Body::engine(bool type)
{
	glPushMatrix();
	glTranslatef(2.5, 1.85, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(1.5, 1, 2);
	cone(type, _textureId[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 2, 0);
	glScalef(3, 1, 2.5);
	cube(_textureId[0]);
	glPopMatrix();
}

void Body::rotor(bool type)
{
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.5);
	cone(type, _textureId[0]);
	glPopMatrix();

	glPushMatrix();
		glRotatef(this->rotorsRotationAngle, 0, 1, 0);
		// Blades
		glPushMatrix();
			glTranslatef(4, 3.5, 0);
			glScalef(8, 0.1, 0.5);
			cube(_textureId[1]);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-4, 3.5, 0);
			glScalef(8, 0.1, 0.5);
			cube(_textureId[1]);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 3.5, 4);
			glRotatef(90, 0, 1, 0);
			glScalef(8, 0.1, 0.5);
			cube(_textureId[1]);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 3.5, -4);
			glRotatef(-90, 0, 1, 0);
			glScalef(8, 0.1, 0.5);
			cube(_textureId[1]);
		glPopMatrix();
	glPopMatrix();
}

void Body::spotLight()
{
	float cutOffAngle = 0;

	GLfloat highDirection[] = {1.0, 1.0, 0.0};
	GLfloat lowDirection[] = {1.0, 0.5, 0.0};

	(this->highBeam) ? cutOffAngle = 60 : cutOffAngle = 30; 
	(lightOn) ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

	GLfloat SpotDiffuseLight[] = {1.0, 1.0, 1.0};
    GLfloat SpotSpecularLight[] = {1.0, 1.0, 1.0};
    
    glLightfv (GL_LIGHT1, GL_SPECULAR, SpotSpecularLight);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, SpotDiffuseLight);

	GLfloat SpotLightPosition[] = {-4.6, 0.0, 0.0, 1.0};
	
	glPushMatrix();
		glTranslatef(-4.6, 0.0, 0.0);
		glRotatef(180, 0, 0, 1);
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, cutOffAngle);
		glLightfv(GL_LIGHT1, GL_POSITION, SpotLightPosition);

		if(highBeam)
		{
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, highDirection);
		}
		else
		{
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lowDirection);
		}

	glPopMatrix();
}

void Body::draw(bool type, bool beam, bool light, float rotAngle)
{
	this->highBeam = beam;
	this->lightOn = light;
	this->rotorsRotationAngle = rotAngle;

	if(type)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	GLfloat mat[4];
	
	mat[0] = 0.05;
	mat[1] = 0.05;
	mat[2] = 0.05;
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = 0.05;
	mat[1] = 0.05;
	mat[2] = 0.05;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = 0.07;
	mat[1] = 0.07;
	mat[2] = 0.07;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	glEnable(GL_COLOR_MATERIAL);
	glColor3ub(64, 95, 0);
	floor(type);
	top(type);
	bigDoors(type);
	smallDoors(type);
	back(type);
	under(type);
	engine(type);
	glDisable(GL_COLOR_MATERIAL);

	mat[0] = 0.25;
	mat[1] = 0.25;
	mat[2] = 0.25;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = 0.4;
	mat[1] = 0.4;
	mat[2] = 0.4;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = 0.77;
	mat[1] = 0.77;
	mat[2] = 0.77;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 76.8);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.5, 0.5, 0.5);
	landingGear(type);
	rotor(type);
	glDisable(GL_COLOR_MATERIAL);

	spotLight();
}
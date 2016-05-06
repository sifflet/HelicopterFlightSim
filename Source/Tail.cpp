#include "Tail.h"

using namespace std;

Tail::Tail()
{
	Image* image = loadBMP("Metal.bmp");
	_textureId[0] = loadTexture(image);

	image = loadBMP("Metal2.bmp");
	_textureId[1] = loadTexture(image);
	delete image;
}

GLuint Tail::loadTexture(Image* image)
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

void Tail::mainPart(bool type)
{
	GLdouble clipPlane1[] = {0, 0, -1, 1.7};
	glEnable(GL_CLIP_PLANE1);

	glPushMatrix();
	glTranslatef(3, 1, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.5, 0.8, 4);
	glClipPlane(GL_CLIP_PLANE1, clipPlane1);
	cone(type, _textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE1);
}

void Tail::endPart(bool type)
{
	glPushMatrix();
	glTranslatef(9.5, 2.85, 0);
	glRotatef(55, 0, 0, 1);
	glScalef(2, 0.8, 0.1);
	cube(_textureId[0]);
	glPopMatrix();
}

void Tail::wings(bool type)
{
	glPushMatrix();
	glTranslatef(6.8, 1.5, 0);
	glScalef(1, 0.1, 3.7);
	cube(_textureId[1]);
	glPopMatrix();
}

void Tail::rotor(bool type)
{
	glPushMatrix();
	glTranslatef(9.8, 3.6, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.1, 0.1, 0.3);
	cone(type, _textureId[1]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.8, 3.65, -0.55);
		glRotatef(this->rotorsRotationAngle, 0, 0, 1);
		// Blades
		glPushMatrix();
			glTranslatef(0,0.5,0);
			glScalef(0.2, 1.2, 0.1);
			cube(_textureId[1]);
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(120, 0, 0, 1);
			glTranslatef(0, 0.5, 0);
			glScalef(0.2, 1.2, 0.1);
			cube(_textureId[1]);
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(-120, 0, 0, 1);
			glTranslatef(0, 0.5, 0);
			glScalef(0.2, 1.2, 0.1);
			cube(_textureId[1]);
		glPopMatrix();
		
	glPopMatrix();
}

void Tail::draw(bool type, float angle)
{
	this->rotorsRotationAngle = angle;

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
	mainPart(type);
	endPart(type);
	wings(type);
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
	rotor(type);
	glDisable(GL_COLOR_MATERIAL);
}
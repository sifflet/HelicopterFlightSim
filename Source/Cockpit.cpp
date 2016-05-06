#include "Cockpit.h"

using namespace std;

Cockpit::Cockpit()
{
	Image* image = loadBMP("Metal.bmp");
	_textureId[0] = loadTexture(image);

	image = loadBMP("Glass.bmp");
	_textureId[1] = loadTexture(image);
	delete image;
}

GLuint Cockpit::loadTexture(Image* image)
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

void Cockpit::seatArea(bool type)
{
	GLdouble clipPlane0[] = {1.5, -0.5, 0, 4.2};
	GLdouble clipPlane2[] = {1.5, -0.5, 0, 4.5};
	GLdouble clipPlane3[] = {0.3, 0, 0.5, 0.22};
	GLdouble clipPlane4[] = {0.3, 0, -0.5, 0.22};
	GLdouble clipPlane5[] = {0, -1, 0, 1.8};

	// Sides
	glEnable(GL_CLIP_PLANE2);
	glClipPlane(GL_CLIP_PLANE2, clipPlane2);

	glPushMatrix();
	glScalef(1.2, 1.8, 0.1);
	glTranslatef(-1.9, 0.5, 15.2);
	cube(_textureId[0]);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.2, 1.8, 0.1);
	glTranslatef(-1.9, 0.5, -15.2);
	cube(_textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE2);

	// Side windows
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, clipPlane0);

	glPushMatrix();
	glScalef(0.9, 1, 0.1);
	glTranslatef(-2.6, 1.2, 15.3);
	cube(_textureId[0]);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.9, 1, 0.1);
	glTranslatef(-2.6, 1.2, -15.3);
	cube(_textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE0);

	// Front Windows
	glEnable(GL_BLEND); //Enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function
	glEnable(GL_CLIP_PLANE5);
	glClipPlane(GL_CLIP_PLANE5, clipPlane5);
	glColor4f(1.0, 1.0, 1.0, 0.3);
	glPushMatrix();
		glTranslatef(-3, 1.2, 0.88);
		glRotatef(90, 0, 1, 0);
		glRotatef(35, 0.7, 1, 0);
		glScalef(1.4, 1.4, 0.1);
		cube(_textureId[1]);
	glPopMatrix();

	glColor4f(0.0, 0.0, 0.0, 0.3);
	glPushMatrix();
		glTranslatef(-3, 1.2, -0.88);
		glRotatef(90, 0, 1, 0);
		glRotatef(-35, -0.7, 1, 0);
		glScalef(1.4, 1.4, 0.1);
		cube(NULL);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE5);
	glDisable(GL_BLEND);
	glColor3ub(64, 95, 0);

	// Piece between the windows
	glPushMatrix();
	glTranslatef(-3.35, 1.2, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(20, 1, 0, 0);
	glScalef(0.5, 1.4, 0.1);
	cube(_textureId[0]);
	glPopMatrix();

	// Top
	glEnable(GL_CLIP_PLANE3);
	glEnable(GL_CLIP_PLANE4);
	glPushMatrix();
	glTranslatef(-2.45, 1.81, 0);
	glScalef(1.3, 0.1, 3);
	glClipPlane(GL_CLIP_PLANE3, clipPlane3);
	glClipPlane(GL_CLIP_PLANE4, clipPlane4);
	cube(_textureId[0]);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE3);
	glDisable(GL_CLIP_PLANE4);
}

void Cockpit::nose(bool type)
{
	GLdouble clipPlane1[] = {-1, 0, 0, 0};
	glEnable(GL_CLIP_PLANE1);

	glPushMatrix();
	glScalef(1.67, 0.7, 1.6);
	glTranslatef(-1.75, 0, 0);
	glClipPlane(GL_CLIP_PLANE1, clipPlane1);
	sphere(type, _textureId[0]);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE1);
}

void Cockpit::draw(bool type)
{
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
	seatArea(type);
	nose(type);
	glDisable(GL_COLOR_MATERIAL);
}
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iostream>
#include <GL/glut.h>

using namespace std;

inline void cube(GLuint textureId)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// front
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	//right
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//back
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	//left
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	//bottom
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	//top
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

inline void cone(bool type, GLuint textureId)
{
	GLUquadricObj * qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(type)
	{
		gluQuadricDrawStyle(qobj, GLU_LINE);
		gluCylinder(qobj, 1, 0.0, 2.5, 16, 16);
	}else
	{
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluCylinder(qobj, 1, 0.0, 2.5, 16, 16);
	}

	gluDeleteQuadric(qobj);

	glDisable(GL_TEXTURE_2D);
}

inline void cylinder(bool type, GLuint textureId)
{
	GLUquadricObj * qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE); 
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(type)
	{
		gluQuadricDrawStyle(qobj, GLU_LINE);
		gluCylinder(qobj, 1.24, 1.24, 1.18, 16, 16);
	}else
	{
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluCylinder(qobj, 1.24, 1.24, 1.18, 16, 16);
	}

	gluDeleteQuadric(qobj);

	glDisable(GL_TEXTURE_2D);
}

inline void sphere(bool type, GLuint textureId)
{
	GLUquadricObj * qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE); 
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(type)
	{
		gluQuadricDrawStyle(qobj, GLU_LINE);
		gluSphere(qobj, 1, 16, 16);
	}else
	{
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluSphere(qobj, 1, 16, 16);
	}

	gluDeleteQuadric(qobj);

	glDisable(GL_TEXTURE_2D);
}

inline void torus(bool type)
{
	if(type)
	{
		glutWireTorus(1.5, 15.0, 16, 16);
	}else
	{
		glutSolidTorus(1.5, 15.0, 16, 16);
	}
}

#endif
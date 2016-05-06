#include "Terrain.h"

using namespace std;


//Makes the image into a texture, and returns the id of the texture
GLuint Terrain::loadTexture(Image* image)
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

Terrain::Terrain()
{
	this->hml = HeightmapLoader();
	hml.loadHeightmap("Heightmap.bmp");
	
	Image* image = loadBMP("Grass.bmp");
	_textureId[0] = loadTexture(image);

	image = loadBMP("Helipad.bmp");
	_textureId[1] = loadTexture(image);

	image = loadBMP("Sky.bmp");
	_textureId[2] = loadTexture(image);
	delete image;
	
	ObjLoader objLoad;
	objLoad.loadObj("map.obj");

	this->vertices = objLoad.getVertices();
	this->normals = objLoad.getNormals();
	this->faces = objLoad.getFaces();
}

void Terrain::surfaceObj()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0, 1.0, 1.0);
	
	for(unsigned int i = 0; i < faces.size(); ++i)
	{
		float normalVec[3] = {normals[i].x, normals[i].y, normals[i].z};
		
		float vertex1[3] = {vertices[faces[i][0]].x, vertices[faces[i][0]].y, vertices[faces[i][0]].z};
		float vertex2[3] = {vertices[faces[i][1]].x, vertices[faces[i][1]].y, vertices[faces[i][1]].z};
		float vertex3[3] = {vertices[faces[i][2]].x, vertices[faces[i][2]].y, vertices[faces[i][2]].z};

		glBegin(GL_TRIANGLES);
		glNormal3fv(normalVec);
		glTexCoord2f(0,0);
		glVertex3fv(vertex1);
		glTexCoord2f(0,1);
		glVertex3fv(vertex2);
		glTexCoord2f(1,1);
		glVertex3fv(vertex3);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void Terrain::surfaceHMap()
{
	for(unsigned int i = 0; i < hml.heightPoints.size(); ++i)
	{
		glBegin(GL_POINTS);
		glVertex3f(hml.heightPoints[i].x, hml.heightPoints[i].y, hml.heightPoints[i].z);
		glEnd();
	}
}

void Terrain::map()
{
	surfaceObj();
}

void Terrain::draw(bool type)
{
	GLfloat mat[4];

	mat[0] = 0.05;
	mat[1] = 0.05;
	mat[2] = 0.05;
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = 0.5;
	mat[1] = 0.5;
	mat[2] = 0.5;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = 0.7;
	mat[1] = 0.7;
	mat[2] = 0.7;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	if(type)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(-4800.0, 223.5, 6600.0);
		glScalef(300.0, 300.0, 300.0);
		map();
	glPopMatrix();

	//surfaceHMap();

	// helipad
	glPushMatrix();
		glTranslatef(0.0, -1.5, 0.0);
		glScalef(20.0, 1.0, 20.0);
		cube(_textureId[1]);
	glPopMatrix();

	// skybox
	glPushMatrix();
		glScalef(30000, 30000, 30000);
		cube(_textureId[2]);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}
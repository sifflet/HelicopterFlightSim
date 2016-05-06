#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
#include <sstream>
#include <Windows.h>
#include <MMSystem.h>
#include "Helicopter.h"
#include "Terrain.h"
#include "Camera.h"
#include "Vector3.h"
#include "Point3.h"
#include "Rings.h"
#include "HeightmapLoader.h"
#include <GL/glut.h>

using namespace std;

// Initial size of graphics window.
const int WIDTH = 800;
const int HEIGHT = 600;

// Current size of window
int width = WIDTH;
int height = HEIGHT;

// Mouse position
double xMouse = 0.5;
double yMouse = 0.5;

// Bounds of viewing frustum
double nearPlane = 0.5;
double farPlane = 100000.0;

// Viewing angle
double fovy = 40.0;

// Variables
bool type = false; // used to switch between wire (true) or solid (false)
float scale = 1;
static long font = (long)GLUT_BITMAP_8_BY_13;
int frameCounter = 0;
float fps = 0.0;
time_t lastTime;
time_t currentTime = 0.0;
float returnToZero = 0.15; // has to be lower than angleMod
vector<bool> keyStates(256, false); // stores which keys are pressed
vector<bool> keySpecialStates(256, false); // stores which special keys are pressed
float sunRotationStep = 0.001;
float sunRotationAngle = 0.0;
float sunLightRadius = 7000.0;
bool engineStart = false;
bool fullScreen = false;

Terrain terrain;
Helicopter heli;
Rings rings;

// Helicopter variables
bool spotLightHighBeam = false;
float spotLightCutOffAngle = 30.0;
bool spotLightOn = false;
float rotorsRotationStep = 0.0;
float rotorsRotationAngle = 0.0;
float helicopterAngleZ = 0.0;
float helicopterAngleY = 0.0;
float helicopterAngleX = 0.0;
Vector3 noseDirection (0.0, 0.0, 0.0);

// Movement variables
const Vector3 gravity = Vector3(0.0, -9.8, 0.0); // gravity
Point3 position = Point3(0.0, 0.0, 0.0);
float speed = 0.0;
float maxSpeed = 10.0;
float angleMod = 0.75;
Vector3 velocity = Vector3(0.0, 0.0, 0.0);
Vector3 momentum = Vector3(0.0, 0.0, 0.0);

// Camera variables
Camera cam = Camera();
float camRotatedZ = 0.0;
float camRotationAngle = 2.0;

// initial camera
Point3 eye = Point3(0.0, 0.0, -20.0);
Point3 look = Point3(0.0, 0.0, 0.0);
Vector3 up = Vector3(0.0, 1.0, 0.0);

//Initializes 3D rendering
void initRendering()
{
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (double)w / (double)h, nearPlane, farPlane);
}

void light() {

	// Sunlight
	GLfloat SunDiffuseLight[] = {1.0, 1.0, 1.0};

    glLightfv (GL_LIGHT0, GL_DIFFUSE, SunDiffuseLight);
   
	float lightPosX = -4800.0 + sunLightRadius * cos(sunRotationAngle);
	float lightPosZ = 6600.0;
	float lightPosY = 223.5 + sunLightRadius * sin(sunRotationAngle);

	glEnable(GL_COLOR_MATERIAL);
	glColor3ub(255, 239, 0);
	glPushMatrix();
		glTranslatef(lightPosX, lightPosY, lightPosZ);
		glScalef(10.0, 10.0, 10.0);
		sphere(type, NULL);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);

    GLfloat SunLightPosition[] = {lightPosX, lightPosY, lightPosZ, 1.0};
    glLightfv (GL_LIGHT0, GL_POSITION, SunLightPosition);

	glEnable(GL_LIGHT0);
}

void changeNoseDirection()
{
	noseDirection.set(sin(3.14159265/180 * helicopterAngleX) * cos(3.14159265/180 * -helicopterAngleZ), sin(3.14159265/180 * -helicopterAngleZ), cos(3.14159265/180 * -helicopterAngleX) * cos(3.14159265/180 * -helicopterAngleZ));
	noseDirection.normalizeVector3();
}


Vector3 freeMovement()
{
	float angleZ = helicopterAngleZ + 90;
	float angleY = helicopterAngleY + 90;
	float angleX = helicopterAngleX;

	Vector3 velocityZ;
	Vector3 velocityX;

	velocityZ.set(-speed*cos(3.14159265/180 * (angleZ))*sin(3.14159265/180 * (angleX)), speed*sin(3.14159265/180 * (angleZ)), -speed*cos(3.14159265/180 * (angleZ))*cos(3.14159265/180 * (angleX)));
	velocityX.set(-speed*cos(3.14159265/180 * (angleY))*cos(3.14159265/180 * (angleX)), speed*sin(3.14159265/180 * (angleY)), speed*cos(3.14159265/180 * (angleY))*sin(3.14159265/180 * (angleX)));
	velocity.set(velocityZ + velocityX + gravity);

	changeNoseDirection();

	return velocity;
}

void writeBitmapString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void calculateFps()
{
	if((currentTime - lastTime) > 3)
	{
		fps = frameCounter / 3;
		frameCounter = 0;

		lastTime = time(NULL);
	}
}

void mouseMovement(int mx, int my)
{
	xMouse = double(mx) / double(width);
	yMouse = double(my) / double(height);

	glutPostRedisplay();
}

void keyPressed (unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'j':
	case 'J':
		type = !type;		// switch to wirefram or solid view
		break;
	case 'r':
	case 'R':
		engineStart = !engineStart;

		if(engineStart)
		{
			PlaySound(L"Heli.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		break;
	default:
		keyStates[key] = true;
		break;
	}
}

void keyUp (unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

void keyOperations (void)
{
	if(keyStates['f'] || keyStates['F']) cam.slide(0, 0, -2.0);	// slide camera forward
	if(keyStates['b'] || keyStates['B']) cam.slide(0, 0, 2.0);	// slide camera backward
	if(keyStates['l'] || keyStates['L']) cam.rotateX(-2.0);
	if(keyStates['k'] || keyStates['K']) cam.rotateX(2.0);
	if(keyStates['z']) scale += 0.2;							// zoom in
	if(keyStates['Z']) scale -= 0.2;							// zoom out
	if(keyStates['h']) spotLightHighBeam = false;				// switch to low beam
	if(keyStates['H']) spotLightHighBeam = true;				// switch to high beam
	if(engineStart)
	{
		if(keyStates[' '])											// accelerate
		{
			if(speed < maxSpeed)
			{
				speed += 0.05;
				rotorsRotationStep += 0.3;
			}
		}
		if(keyStates['c'])											// decelerate
		{
			if(speed > -maxSpeed)
			{
				speed -= 0.05;
				rotorsRotationStep -= 0.3;
			}
		}
	}
	if(keyStates['w']) helicopterAngleZ += angleMod;			// adjust pitch
	if(keyStates['s']) helicopterAngleZ -= angleMod;			// adjust pitch
	if(keyStates['e']) helicopterAngleY += angleMod;			// roll helicopter to the right
	if(keyStates['q']) helicopterAngleY -= angleMod;			// roll helicopter to the left
	if(keyStates['d'])											// yaw helicopter to the right
	{
		helicopterAngleX += 1.0;
		cam.rotateZ(-1.0);
	}
	if(keyStates['a'])											// yaw helicopter to the left
	{
		helicopterAngleX -= 1.0;
		cam.rotateZ(1.0);
	}
	if(keyStates['m'] || keyStates['M'])						// reset everything
	{
		position.set(0.0, 0.0, 0.0);
		speed = 0.0;
		helicopterAngleX = 0.0;
		helicopterAngleY = 0.0;
		helicopterAngleZ = 0.0;
		rotorsRotationAngle = 0.0;
		rotorsRotationStep = 0.0;

		eye.set(0.0, 0.0, -1.0);
		look.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		cam.set(eye, look, up, 0.0);
	}
	if(keyStates[27]) exit(0);									// <esc>: exit
}

void keySpecial(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F2:
		spotLightOn = !spotLightOn;
		break;
	case GLUT_KEY_F4:
		fullScreen = !fullScreen;

		if(fullScreen)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow(width, height);
			glutPositionWindow(100, 100);
		}
		break;
	default:
		keySpecialStates[key] = true;
		break;
	}
}

void keySpecialUp(int key, int x, int y)
{
	keySpecialStates[key] = false;
}

void keySpecialOperations(void)
{
	if(keySpecialStates[GLUT_KEY_LEFT]) cam.rotateZ(-camRotationAngle);
	if(keySpecialStates[GLUT_KEY_RIGHT]) cam.rotateZ(camRotationAngle);
	if(keySpecialStates[GLUT_KEY_UP]) cam.rotateY(camRotationAngle);
	if(keySpecialStates[GLUT_KEY_DOWN]) cam.rotateY(-camRotationAngle);
}

void idle()
{
	rotorsRotationAngle += rotorsRotationStep;

	if(rotorsRotationAngle > 360)
	{
		rotorsRotationAngle -= 360;
	}

	sunRotationAngle += sunRotationStep;

	if(sunRotationAngle > 360)
	{
		sunRotationAngle -= 360;
	}

	if(helicopterAngleY > 0.0)
	{
		helicopterAngleY -= returnToZero;
		if(helicopterAngleY < 0.0) helicopterAngleY = 0.0;
	}
	else if(helicopterAngleY < 0.0)
	{
		helicopterAngleY += returnToZero;
		if(helicopterAngleY > 0.0) helicopterAngleY = 0.0;
	}

	if(helicopterAngleZ > 0.0)
	{
		helicopterAngleZ -= returnToZero;
		if(helicopterAngleZ < 0.0) helicopterAngleZ = 0.0;
	}
	else if(helicopterAngleZ < 0.0)
	{
		helicopterAngleZ += returnToZero;
		if(helicopterAngleZ > 0.0) helicopterAngleZ = 0.0;
	}

	if(!engineStart)
	{
		if(speed > 0)
		{
			speed -= 0.005;
		}

		if(rotorsRotationStep > 0)
		{
			rotorsRotationStep -= 0.1;
		}
	}

	glutPostRedisplay();
}

//Draws the 3D scene
void drawScene()
{
	keyOperations();
	keySpecialOperations();

	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	light();

	// Draw helicopter
	glPushMatrix();
		Vector3 move;
		move = freeMovement();
		Point3 oldPos(position);
		position.set(position.x + move.x, position.y + move.y, position.z + move.z);
		
		if(position.y < 0.0)
		{
			move.set(move.x, 0.0, move.z);
			position.set(position.x, 0.0, position.z);
		}

		if(position.x > 1473 || position.x < -10527)
		{
			move.set(0.0, 0.0, 0.0);
			position.set(oldPos);
		}

		if(position.z > 11000 || position.z < -1000)
		{
			move.set(0.0, 0.0, 0.0);
			position.set(oldPos);
		}
		
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale, scale, scale);
		glRotatef(90, 0, 1, 0);

		heli.setParameters(spotLightHighBeam, spotLightOn, rotorsRotationAngle, helicopterAngleZ, helicopterAngleY, helicopterAngleX);
		heli.draw(type);
	glPopMatrix();

	cam.move(move);

	// Draw terrain
	glPushMatrix();
		terrain.draw(type);
	glPopMatrix();

	//Draw rings
	rings.draw(type, position);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	//Create the window
	glutCreateWindow("Helicopter");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutMotionFunc(mouseMovement);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecial);
	glutSpecialUpFunc(keySpecialUp);
	glutIdleFunc(idle);

	glViewport(0, 0, WIDTH, HEIGHT);

	cam.set(eye, look, up, 0.0);
	heli = Helicopter();
	terrain = Terrain();
	rings = Rings();

	lastTime = time(NULL);
	currentTime = time(NULL);

	glutMainLoop();
	return 0;
}


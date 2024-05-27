#include "SceneObjects.h"

#define AXIS_LINE_COUNT 30
#define LINE_SIZE 0.5f

void DrawBackgroundWithColor(float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(-100, -100, -10);
	glVertex3f(100, -100, -10);
	glVertex3f(100, 100, -10);
	glVertex3f(-100, 100, -10);
	glEnd();
	//glRectf(scale_x_start, scale_y_start, scale_x_end, scale_y_end);
}

void DrawText(std::string str, float x, float y)
{
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str.at(i));
	}
}

void DrawText(float num, float x, float y)
{
	std::string str = std::to_string(num);
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str.at(i));
	}
}

void Draw3DAxis(bool draw_x, bool draw_y, bool draw_z)
{
	//x axis red
	if (draw_x) {
		glColor3f(1, 0, 0);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(-1000, 0, 0);
		glVertex3f(1000, 0, 0);
		glEnd();

		//draw axis count
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int i = -AXIS_LINE_COUNT; i < AXIS_LINE_COUNT; i++)
		{
			glVertex3f(i, -(LINE_SIZE / 2), 0);
			glVertex3f(i, (LINE_SIZE / 2), 0);
		}
		glEnd();
	}

	if (draw_y) {
		//y axis green
		glColor3f(0, 1, 0);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(0, -500, 0);
		glVertex3f(0, 500, 0);
		glEnd();

		//draw axis count
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int i = -AXIS_LINE_COUNT; i < AXIS_LINE_COUNT; i++)
		{
			glVertex3f(-(LINE_SIZE / 2), i, 0);
			glVertex3f((LINE_SIZE / 2), i, 0);
		}
		glEnd();
	}

	if (draw_z) {
		//z axis blue
		glColor3f(0, 0, 1);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 1000);
		glVertex3f(0, 0, -1000);
		glEnd();

		//draw axis count
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int i = -AXIS_LINE_COUNT; i < AXIS_LINE_COUNT; i++)
		{
			glVertex3f(-(LINE_SIZE / 2), 0, i);
			glVertex3f((LINE_SIZE / 2), 0, i);
		}
		glEnd();
	}
}

void DrawSceneObjSphere()
{
	glPushMatrix();
	glScalef(1.2, 1.2, 1.2);
	glutSolidSphere(1, 20, 20);
	glColor3f(0, 0, 0);
	glutWireSphere(1, 20, 20);
	glPopMatrix();
}

void DrawSceneObjCube()
{
	glutSolidCube(2);
	glColor3f(0, 0, 0);
	glutWireCube(2);
}

void DrawSceneObjCone()
{
	glPushMatrix();
	glRotatef(90, -1, 0, 2);
	glutSolidCone(1, 2, 15, 15);
	glColor3f(0, 0, 0);
	glutWireCone(1, 2, 15, 15);
	glPopMatrix();
}

void DrawSceneObjTorus()
{
	glPushMatrix();
	glutSolidTorus(1, 1, 15, 15);
	glColor3f(0, 0, 0);
	glutWireTorus(1, 1, 15, 15);
	glPopMatrix();
}

void DrawSceneObjDodecohedron()
{
	glPushMatrix();
	glutSolidDodecahedron();
	glColor3f(0, 0, 0);
	glutWireDodecahedron();
	glPopMatrix();
}

void DrawSceneObjOctahedron()
{
	glPushMatrix();
	glutSolidOctahedron();
	glColor3f(0, 0, 0);
	glutWireOctahedron();
	glPopMatrix();
}

void DrawSceneObjTetrahedron()
{
	glPushMatrix();
	glutSolidTetrahedron();
	glColor3f(0, 0, 0);
	glutWireTetrahedron();
	glPopMatrix();
}

void DrawSceneObjCosahedron()
{
	glPushMatrix();
	glutSolidIcosahedron();
	glColor3f(0, 0, 0);
	glutWireIcosahedron();
	glPopMatrix();
}

void DrawSceneObjTeapot()
{
	glPushMatrix();
	glRotatef(45,-1,1,0);
	glutSolidTeapot(1);
	glColor3f(0, 0, 0);
	glutWireTeapot(1);
	glPopMatrix();
}

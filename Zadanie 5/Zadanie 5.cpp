#include "stdafx.h"
#include "math.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

GLdouble ox = 0.0, oy = 0.0, oz = 0.0;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
GLfloat windowWidth;
GLfloat windowHeight;
vector<GLdouble> x_cord;
vector<GLdouble> y_cord;
int point = 0;

void drawText(const char *text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double matrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i<length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	string text = "ilosc wierzcholkow: " + std::to_string(point);
	drawText(text.data(), text.size(), 10, 10);

	for (int x = 0; x < x_cord.size(); x++)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x_cord.at(x), y_cord.at(x)); // center of circle
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				x_cord.at(x) + (cos(i*twicePi / triangleAmount) / 50),
				y_cord.at(x) + (sin(i*twicePi / triangleAmount) / 50)
			);
		}
		glEnd();

		if (x > 0)
		{

			glLineWidth(2.5);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
			glVertex2f(x_cord.at(x), y_cord.at(x));
			glVertex2f(x_cord.at(x - 1), y_cord.at(x - 1));
			glEnd();
		}
	}


	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) {
	bool add = true;
	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	GLfloat wx = x, wy, wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y;
	wy = y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);
	gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);
	glutPostRedisplay();

	for (int counter = 0; counter < x_cord.size(); counter++)
	{
		if ((ox == x_cord.at(counter)) && (oy == y_cord.at(counter)))
		{
			add = false;
		}

		else if ((ox >= x_cord.at(0) - 0.02) && (ox <= x_cord.at(0) + 0.02) && (oy >= y_cord.at(0) - 0.02) && (oy <= y_cord.at(0) + 0.02))
		{
			point--;
			break;
		}
	}


	if (add == true)
	{
		point++;
		x_cord.push_back(ox);
		y_cord.push_back(oy);
	}
}

void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zadanie 5.");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(Mouse);
	SetupRC();
	glutMainLoop();
}
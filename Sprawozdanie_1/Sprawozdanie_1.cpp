// Sprawozdanie_1.cpp : Defines the entry point for the console application.

//n=10

//

#include "stdafx.h"
#include "math.h"
#include "iostream"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Pocztkowy rozmiar i pozycja prostokta
GLfloat x_1 = 100.0f;
GLfloat y_1 = 150.0f;
GLfloat angle = 0;
GLsizei rsize = 30;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
// Wywo�ywana w celu przerysowania sceny
void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT);
	// Aktualny kolor rysuj�cy - czerwony
	//	R	G	B
	glColor3f(0.7f, 0.2f, 0.3f);
	// Narysowanie sze�ciok�ta wype�nionego aktualnym kolorem
	int triangleAmount = 10;
	GLfloat twicePi = 2.0f * 3.14;
	angle += 0.8f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x_1, y_1, 0);
	glRotatef(angle, 0.0, 0.0, -2.0);
	glTranslatef(-x_1, -y_1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x_1, y_1); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x_1 + (6.0*cos(i*twicePi / triangleAmount)) * 4,
			y_1 + (6.0*sin(i*twicePi / triangleAmount)) * 4
		);
	}
	glEnd();
	glPopMatrix();
	glFlush();
	// Wys�anie polece� do wykonania - !!! dla animacji to jest inne polecenie
	glutSwapBuffers();
}


///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielko��
void TimerFunction(int value) {
	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if (x_1 > windowWidth - rsize || x_1 < 20)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if (y_1 > windowHeight - rsize || y_1 < 20)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy�o swoj wielko�� w czasie, gdy kwadrat odbija� si� od     
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza      
	// przestrzeni� ograniczajc�.     
	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	// Wykonanie przesuni�cia kwadratu
	x_1 += xstep;
	y_1 += ystep;

	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT przy ka�dej zmianie wielko�ci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SetupRC(void) {

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zadanie 3. i 4.");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();

}
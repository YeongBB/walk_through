#include<GL/glut.h>

GLfloat Mx = 0.0, Mz = 0.0;
GLfloat Mox = 0.0, Moy = 0.0;
GLfloat movx = 0.0, movy = 0.0;
GLfloat go = 0.01;

#define WIDTH 500
#define HIGHT 500

void floor()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glBegin(GL_QUADS);
			glVertex3f(0.5, 0, 0.5);
			glVertex3f(0.5, 0, -0.5);
			glVertex3f(-0.5, 0, -0.5);
			glVertex3f(-0.5, 0, 0.5);
			glTranslatef(1, 0, 0);
			glEnd();
			glPopMatrix();
		}
		glTranslatef(-99, 0, -1);
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(Mx, 1, Mz, movx, movy, 0, 0, 1, 0);
	floor();
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Mox = x;
		Moy = y;
	}
}
void Motion(int x, int y)
{
	float ax = x;
	float ay = y;
	movx = ax - Mox * go;
	movy = ay - Moy * go;
	glutPostRedisplay();
}

void Mkey(unsigned char key, int x, int  y)
{
	switch (key)
	{
	case 'w':
		Mx -= 0.01;
		break;
	case 's':
		Mx += 0.01;
		break;
	case 'a':
		Mz -= 0.01;
		break;
	case 'd':
		Mz += 0.01;
		break;
	}
	glutPostRedisplay();
}
void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
		-1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HIGHT);
	glutCreateWindow("OPen");
	glClearColor(0.4, 0.4, 0.4, 0);
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Mkey);
	glutMainLoop();
}
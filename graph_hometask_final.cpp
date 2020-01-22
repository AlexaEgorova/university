#include <iostream>

#include "glut.h"
#include "display.cpp"

using namespace std;

void DrawMyCube(GLfloat size)
{
  glBegin(GL_QUADS);
  // левая грань
  glVertex3f(-size / 2, -size / 2, -size / 2);
  glVertex3f(-size / 2, size / 2, -size / 2);
  glVertex3f(-size / 2, size / 2, size / 2);
  glVertex3f(-size / 2, -size / 2, size / 2);
  // правая грань
  glVertex3f(size / 2, -size / 2, -size / 2);
  glVertex3f(size / 2, -size / 2, size / 2);
  glVertex3f(size / 2, size / 2, size / 2);
  glVertex3f(size / 2, size / 2, -size / 2);
  // нижняя грань
  glVertex3f(-size / 2, -size / 2, -size / 2);
  glVertex3f(-size / 2, -size / 2, size / 2);
  glVertex3f(size / 2, -size / 2, size / 2);
  glVertex3f(size / 2, -size / 2, -size / 2);
  // верхняя грань
  glVertex3f(-size / 2, size / 2, -size / 2);
  glVertex3f(-size / 2, size / 2, size / 2);
  glVertex3f(size / 2, size / 2, size / 2);
  glVertex3f(size / 2, size / 2, -size / 2);
  // задняя грань
  glVertex3f(-size / 2, -size / 2, -size / 2);
  glVertex3f(size / 2, -size / 2, -size / 2);
  glVertex3f(size / 2, size / 2, -size / 2);
  glVertex3f(-size / 2, size / 2, -size / 2);
  // передняя грань
  glVertex3f(-size / 2, -size / 2, size / 2);
  glVertex3f(size / 2, -size / 2, size / 2);
  glVertex3f(size / 2, size / 2, size / 2);
  glVertex3f(-size / 2, size / 2, size / 2);
  glEnd();
}

void init() {
  glClearColor(0.9, 0.9, 0.9, 0.9);
}

double smallAlpha = 0.8;
double middleAlpha = 0.4;
double bigAlpha = 0.3;

bool isFogged = false;
bool isSmoothed = false;

GLfloat fogColor[4] = { 1, 1, 0, 1 };


void display_() {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix(); // Запоминается локальная система координат
  glRotatef(100.0, 1.0, 1.0, 1.0);
  glColor4f(0, 0, 1, smallAlpha);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  DrawMyCube(0.5);

  glRotatef(-40.0, 1.0, 1.0, 1.0);
  glColor4f(0, 1, 0, middleAlpha);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  DrawMyCube(0.7);

  glLineWidth(3);
  glRotatef(-40.0, 1.0, 1.0, 1.0);
  glColor4f(1, 0, 0, bigAlpha); 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutWireCube(1);
  glLineWidth(1);

  glPopMatrix(); // Восстанавливается локальная система координат
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'h':
  case 'H':
    cout << "------------------HELP------------------" << endl;
    cout << "--Press S to enable/disable smoothing---" << endl;
    cout << "--Press F to enable/disable fogging-----" << endl;
    cout << "----------------------------------------" << endl;
    cout << "---Press L to show only little figure---" << endl;
    cout << "---Press M to show only middle figure---" << endl;
    cout << "---Press B to show only big figure------" << endl;
    cout << "---Press A to show all the figures------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "-----------Press Esc to exit------------" << endl;
    break;
  case 's':
  case 'S':
    if (isSmoothed) {
      cout << "Disable smoothing" << endl;
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_LINE_SMOOTH);
      glDisable(GL_POLYGON_SMOOTH);
      isSmoothed = false;
      break;
    }
    else {
      cout << "Enable smooth" << endl;
      glEnable(GL_POINT_SMOOTH);
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_LINE_SMOOTH);
      glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_POLYGON_SMOOTH);
      glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
      isSmoothed = true;
      break;
    }
  case 'l':
  case 'L':
    cout << "Show little figure" << endl;
    smallAlpha = (double)(1 + rand() % 9) / 10;
    middleAlpha = 0;
    bigAlpha = 0;
    break;
  case 'm':
  case 'M':
    cout << "Show middle figure" << endl;
    smallAlpha = 0;
    middleAlpha = (double)(1 + rand() % 9) / 10;
    bigAlpha = 0;
    break;
  case 'b':
  case 'B':
    cout << "Show big figure" << endl;
    smallAlpha = 0;
    middleAlpha = 0;
    bigAlpha = (double)(1 + rand() % 9) / 10;
    break;
  case 'a':
  case 'A':
    cout << "Show all figures" << endl;
    smallAlpha = 0.8;
    middleAlpha = 0.4;
    bigAlpha = 0.3;
    break;
  case 'f':
  case 'F':
    if (isFogged) {
      cout << "Disable fog" << endl;
      glDisable(GL_FOG);
      isFogged = false;
    } else {
      cout << "Enable fog" << endl;
      glEnable(GL_FOG);
      fogColor[0] = (double)(1 + rand() % 9) / 10;
      fogColor[1] = (double)(1 + rand() % 9) / 10;
      fogColor[2] = (double)(1 + rand() % 9) / 10;
      glFogi(GL_FOG_MODE, GL_LINEAR);
      glFogfv(GL_FOG_COLOR, fogColor);
      glFogf(GL_FOG_DENSITY, 0.6);
      glHint(GL_FOG_HINT, GL_DONT_CARE);
      glFogf(GL_FOG_START, 0.1);
      glFogf(GL_FOG_END, 0.5);
      isFogged = true;
    }
    break;
  case 27:
    exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(550, 550);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("");

  cout << "...press h for help..." << endl;

  init();
  glutDisplayFunc(display_);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}


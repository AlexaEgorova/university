#include <iostream>

#include "glut.h"

using namespace std;

auto src = 0;
auto dst = 0;
auto redAlpha = 0.6;
auto blueAlpha = 0.3;

bool   gp;                              // G Нажата? ( Новое )
GLuint filter;                          // Используемый фильтр для текстур
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR }; // Хранит три типа тумана
GLuint fogfilter = 0;                    // Тип используемого тумана
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Цвет тумана

void init() {
  glClearColor(0.9, 0.9, 0.9, 1);

  glEnable(GL_BLEND);
  src = GL_SRC_ALPHA;
  dst = GL_ONE_MINUS_SRC_ALPHA;
  glBlendFunc(src, dst);
  //glShadeModel(GL_SMOOTH);

  //glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
  //glEnable(GL_POLYGON_SMOOTH);

  //glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
  //glEnable(GL_POINT_SMOOTH);

  //glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  //glEnable(GL_LINE_SMOOTH);

  //glEnable(GL_POINT_SMOOTH);
  //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  //// Сглаживание линий
  //glEnable(GL_LINE_SMOOTH);
  //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  //// Сглаживание полигонов    
  //glEnable(GL_POLYGON_SMOOTH);
  //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


}

/*
GL_ONE
GL_ZERO
GL_SRC_COLOR
GL_ONE_MINUS_SRC_COLOR
GL_DST_COLOR
GL_ONE_MINUS_DST_COLOR
GL_SRC_ALPHA
GL_ONE_MINUS_SRC_ALPHA
GL_DST_ALPHA
GL_ONE_MINUS_DST_ALPHA
GL_CONSTANT_COLOR
GL_ONE_MINUS_CONSTANT_COLOR
GL_CONSTANT_ALPHA
GL_ONE_MINUS_CONSTANT_ALPHA
GL_SRC_ALPHA_SATURATE
*/

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor4f(1, 0, 0, redAlpha);
  glRectf(-0.5, -0.3, 0.3, 0.5);

  glEnable(GL_BLEND);
  glBlendFunc(src, dst);

  glColor4f(0, 0, 1, blueAlpha);
  glRectf(-0.3, -0.5, 0.5, 0.3);

  glLineWidth(5);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  glColor4f(0, 1, 0, 0.7);  // рисуем треугольник
  glVertex3d(-0.2, -0.7, 0);
  glVertex3d(0.1, -0.2, 0);
  glVertex3d(0.4, -0.7, 0);
  glEnd();

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case'a': 
  case 'A':
    std::cout << "A's pressed" << std::endl;
    dst = GL_ONE_MINUS_SRC_ALPHA;
    break;
  case's':
  case 'S':
    std::cout << "S's pressed" << std::endl;
    dst = GL_ONE;
    break;
  case'd':
  case 'D':
    std::cout << "D's pressed" << std::endl;
    dst = GL_ZERO;
    break;
  case'f':
  case 'F':
    std::cout << "F's pressed" << std::endl;
    dst = GL_DST_ALPHA;
    break;
  case'r':
  case 'R':
    std::cout << "R's pressed" << std::endl;
    if (redAlpha < 1)
      redAlpha += 0.1;
    break;
  case't':
  case 'T':
    std::cout << "T's pressed" << std::endl;
    if (redAlpha > 0)
      redAlpha -= 0.1;
    break;
  case 'g':
  case 'G':
    std::cout << "G's pressed" << std::endl;
    fogfilter += 1;                    // Увеличиние fogfilter на 1
    if (fogfilter >= 3) {
      glDisable(GL_FOG);
      fogfilter = 0;
    }
    else {
      glClearColor(0.8, 0.8, 0.8, 1);
      glEnable(GL_FOG);                       // Включает туман (GL_FOG)
      glFogi(GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана
      glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
      glFogf(GL_FOG_DENSITY, 0.5f);          // Насколько густым будет туман
      glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
      glFogf(GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман
      glFogf(GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается.
    }
    //glFogi(GL_FOG_MODE, fogMode[fogfilter]); // Режим тумана
    break;
  case 27:
    exit(0);
    break;
  }

  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(550, 550);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("");

  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}


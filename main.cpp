#include <QCoreApplication>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2World.h>
#include "GL/glut.h"
#include <iostream>

void draw(void)
{
  //Background color
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  //Draw order

  glFlush();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    glutInit(&argc, argv);

    //Simple buffer
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Car Game");

    //Call to the drawing function
    glutDisplayFunc(draw);
    glutMainLoop();

    std::cout << "Bye!!" << std::endl;

    return a.exec();
}

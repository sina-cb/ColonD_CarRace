#include <QCoreApplication>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity, true);

    std::cout << world.GetGravity().Length() << std::endl;

    return a.exec();
}

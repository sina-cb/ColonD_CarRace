#include "../Game/Render.h"
#include "../Game/Game.h"
#include "../Learning/SimpleDriver.h"
#include "../Learning/ANNDriver.h"
#include "glui/GL/glui.h"
#include "../Learning/Driver.h"
#include <cstdio>
#include <typeinfo>

namespace
{
Game* game;
Driver* driver;
Settings settings;
int32 width = 1024;
int32 height = 768;
int32 framePeriod = 16;
int32 mainWindow;
float settingsHz = 60.0;
GLUI *glui;
float32 viewZoom = 1.0f;
b2Vec2 viewCenter(0.0f, 20.0f);
int tx, ty, tw, th;
bool rMouseDown;
b2Vec2 lastp;
}

void RestartSystem();

void Resize(int32 w, int32 h)
{
    width = w;
    height = h;

    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float32 ratio = float32(tw) / float32(th);

    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = viewCenter - extents;
    b2Vec2 upper = viewCenter + extents;

    // L/R/B/T
    gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

b2Vec2 ConvertScreenToWorld(int32 x, int32 y)
{
    float32 u = x / float32(tw);
    float32 v = (th - y) / float32(th);

    float32 ratio = float32(tw) / float32(th);
    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = viewCenter - extents;
    b2Vec2 upper = viewCenter + extents;

    b2Vec2 p;
    p.x = (1.0f - u) * lower.x + u * upper.x;
    p.y = (1.0f - v) * lower.y + v * upper.y;
    return p;
}

// This is used to control the frame rate (60Hz).
void Timer(int)
{
    glutSetWindow(mainWindow);
    glutPostRedisplay();
    glutTimerFunc(framePeriod, Timer, 0);
}

void SimulationLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    game->SetTextLine(30);
    settings.hz = settingsHz;

    game->Step(&settings);

    driver->drive();

    game->DrawTitle(5, 15, driver->Name());

    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
    B2_NOT_USED(x);
    B2_NOT_USED(y);

    switch (key)
    {
    case 27:
        delete(driver);
        delete(game);
        exit(0);
        break;

        // Press 'z' to zoom out.
    case 'z':
        viewZoom = b2Min(1.1f * viewZoom, 20.0f);
        Resize(width, height);
        break;

        // Press 'x' to zoom in.
    case 'x':
        viewZoom = b2Max(0.9f * viewZoom, 0.02f);
        Resize(width, height);
        break;

        // Press 'r' to reset.
    case 'r':
        RestartSystem();
        break;

    case 'p':
        settings.pause = !settings.pause;
        break;

    case 's':
        driver->start();
        break;
    case 'd':
        driver->stop();
        break;
    case 't':
        driver->toggle_train();
        break;

    default:
        if (game)
        {
            game->Keyboard(key);
        }
    }
}

void KeyboardSpecial(int key, int x, int y)
{
    B2_NOT_USED(x);
    B2_NOT_USED(y);

    switch (key)
    {
    case GLUT_ACTIVE_SHIFT:
        // Press left to pan left.
    default:
        if (game)
        {
            game->KeyboardSpecial(key, x, y);
        }
    }
}

void Mouse(int32 button, int32 state, int32 x, int32 y)
{
    // Use the mouse to move things around.
    if (button == GLUT_LEFT_BUTTON)
    {
        int mod = glutGetModifiers();
        b2Vec2 p = ConvertScreenToWorld(x, y);
        if (state == GLUT_DOWN)
        {
            b2Vec2 p = ConvertScreenToWorld(x, y);
            if (mod == GLUT_ACTIVE_SHIFT)
            {
                game->ShiftMouseDown(p);
            }
            else
            {
                game->MouseDown(p);
            }
        }

        if (state == GLUT_UP)
        {
            game->MouseUp(p);
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lastp = ConvertScreenToWorld(x, y);
            rMouseDown = true;
        }

        if (state == GLUT_UP)
        {
            rMouseDown = false;
        }
    }
}

void MouseMotion(int32 x, int32 y)
{
    b2Vec2 p = ConvertScreenToWorld(x, y);
    game->MouseMove(p);

    if (rMouseDown)
    {
        b2Vec2 diff = p - lastp;
        viewCenter.x -= diff.x;
        viewCenter.y -= diff.y;
        Resize(width, height);
        lastp = ConvertScreenToWorld(x, y);
    }
}

void Restart(int)
{
    delete game;
    delete driver;
    game = new Game();
    driver = new SimpleDriver(game->car);

    Resize(width, height);
}

void RestartSystem(){
    game->Restart();
    driver->Restart();
}

void Pause(int)
{
    settings.pause = !settings.pause;
}

void SingleStep(int)
{
    settings.pause = 1;
    settings.singleStep = 1;
}

void KeyboardUp(unsigned char key, int x, int y)
{
    game->KeyboardUp(key);
}

void KeyboardSpecialUp(int key, int x, int y)
{
    game->KeyboardSpecialUp(key, x, y);
}

int main(int argc, char** argv)
{
    GameVersion version = {1, 2, 1};

    game = new Game();
    driver = new ANNDriver(game->car, false, true);
//    driver = new SimpleDriver(game->car);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    char title[32];
    sprintf(title, "Top-down Car Race Simulation v.%d.%d.%d - By Sina Solaimanpour", version.major, version.minor, version.revision);
    mainWindow = glutCreateWindow(title);
    //glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glutDisplayFunc(SimulationLoop);
    GLUI_Master.set_glutReshapeFunc(Resize);
    GLUI_Master.set_glutKeyboardFunc(Keyboard);
    GLUI_Master.set_glutSpecialFunc(KeyboardSpecial);
    GLUI_Master.set_glutMouseFunc(Mouse);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialUpFunc(KeyboardSpecialUp);
    glutMotionFunc(MouseMotion);

    // Use a timer to control the frame rate.
    glutTimerFunc(framePeriod, Timer, 0);

    glutMainLoop();

    return 0;
}

#include <windows.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

float ratio;

bool spinMode = true;

int HourOfDay = 0, DayOfYear = 0;
int AnimateIncrement = 24;

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void setup_opengl()
{
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(spinMode){
        HourOfDay += AnimateIncrement;
        DayOfYear += HourOfDay/24;

        HourOfDay = HourOfDay%24;
        DayOfYear = DayOfYear%365;
    }


    glLoadIdentity();

    gluLookAt(0.0f,0.0f,5.0f,
              0.0f,0.0f,0.0f,
              0.0f,1.0f,0.0f);

    glRotatef((GLfloat)(360.0*DayOfYear/365.0),0.0f,1.0f,0.0f);

    glColor3f(1.0f,1.0f,1.0f);
    glutSolidSphere(1.0f,12,10);
    glScalef(1.0f,1.0f,2.0f);

    glRotatef((GLfloat)(360.0*DayOfYear/365.0),0.0f,1.0f,0.0f);
    glTranslatef(1.8f,0.0f,0.0f);
    glPushMatrix();
    glRotatef((GLfloat)(360.0*HourOfDay/24.0),0.0f,1.0f,0.0f);
    glRotatef(1.0f,0.0f,0.0f,1.0f);
    glColor3f(0.2f,0.2f,1.0f);
    glutWireSphere(0.2f,12,10);
    glPopMatrix();

    glRotatef((GLfloat)(360.0*12.5*DayOfYear/365.0),0.0f,1.0f,0.0f);
    glRotatef(1.0f,0.0f,0.0f,1.0f);
    glTranslatef(0.5f,0.0f,0.0f);
    glColor3f(0.3f,0.3f,0.3f);
    glutWireSphere(0.1f,12,10);

    glRotatef((GLfloat)(360.0*22.5*DayOfYear/365.0),0.0f,1.0f,1.0f);
    glTranslatef(0.3f,0.0f,0.0f);
    glColor3f(0.8f,0.8f,0.8f);
    glutWireSphere(0.05f,12,10);
    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch(key){
        case 'a':
            if(spinMode)
                spinMode = false;
            else
                spinMode = true;
            break;
        case 27:
            exit(0);
    }
}

void processSpecialKeys(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
            AnimateIncrement *= 2;
            if (0 == AnimateIncrement)
                AnimateIncrement = 1;
            break;
        case GLUT_KEY_DOWN:
            AnimateIncrement /= 2;
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Solar System");

    setup_opengl();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
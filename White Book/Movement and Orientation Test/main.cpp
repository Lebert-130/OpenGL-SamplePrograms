#include <windows.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

float ratio;

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

void RenderStockScene()
{
    GLfloat v0[3], v1[3], v2[3], v3[3], delta;
    int color = 0;

    delta = 0.5f;

    //define the two colors
    GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
    GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

    v0[1] = v1[1] = v2[1] = v3[1] = 0.0f;

    glLineWidth(2);

    //Y-axis line
    glBegin(GL_LINES);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
    glEnd();

    //X-axis line
    glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(1.0f,0.0f,0.0f);
    glEnd();

    //Z-axis line
    glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,1.0f);
    glEnd();

    glBegin(GL_QUADS);
        for(int x = -5; x <= 5; x++)
        {
            for(int z = -5; z <= 5; z++)
            {
                glColor3fv((color++)%2 ? color1 : color2);

                v0[0] = 0.0f+delta*z;
                v0[2] = 0.0f+delta*x;

                v1[0] = v0[0]+delta;
                v1[2] = v0[2];

                v2[0] = v0[0]+delta;
                v2[2] = v0[2]+delta;

                v3[0] = v0[0];
                v3[2] = v0[2]+delta;

                glVertex3fv(v0);
                glVertex3fv(v1);
                glVertex3fv(v2);
                glVertex3fv(v3);
            }
        }
    glEnd();
}

void RenderScene()
{
    static float angle;
    static float position;
    static bool changeDir;

    glLineWidth(1);

    if(position >= -1.5f && !changeDir)
    {
        position -= 0.01f;
    } else {
        changeDir = true;
    }

    if(position <= 0.0f && changeDir)
    {
        position += 0.01f;
    } else {
        changeDir = false;
    }
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.2f, 0.0f, position);
    glRotatef(angle++, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireSphere(0.6f,12,10);
    glColor3f(0.5f, 0.5f, 1.0f);
    glutWireCube(1.0f);
    glColor3f(0.7f,0.7f,0.7f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidTeapot(0.5f);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0f,0.0f,5.0f,
              0.0f,0.0f,0.0f,
              0.0f,1.0f,0.0f);

    glTranslatef(-0.2f, -0.7f, -2.0f);
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    RenderStockScene();
    glPopMatrix();

    glPushMatrix();
    RenderScene();
    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
            exit(0);
    }
}

void processSpecialKeys(int key, int x, int y)
{
    //switch(key){
    //    case GLUT_KEY_UP:
    //        AnimateIncrement *= 2;
    //        if (0 == AnimateIncrement)
    //            AnimateIncrement = 1;
    //        break;
    //    case GLUT_KEY_DOWN:
    //        AnimateIncrement /= 2;
    //        break;
    //}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Movement and Orientation Test");

    setup_opengl();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
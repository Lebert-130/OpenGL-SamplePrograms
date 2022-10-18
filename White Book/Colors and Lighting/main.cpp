#include <windows.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <stdio.h>

float ratio;
int id_selected;
int time;
int frame = 0; int timebase = 0;
char fps_txt[30];
bool lightMode;

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

void StockSceneTriangles()
{
    GLfloat surface0[3] = {0.0f, 0.0f, 0.0f};
    GLfloat surface1[3] = {5.0f, 0.0f, 0.0f};
    GLfloat surface2[3] = {5.0f, 0.0f, -5.0f};
    GLfloat surface3[3] = {0.0f, 0.0f, -5.0f};
    GLfloat surface4[3] = {-5.0f, 0.0f, -5.0f};
    GLfloat surface5[3] = {-5.0f, 0.0f, 0.0f};
    GLfloat surface6[3] = {-5.0f, 0.0f, 5.0f};
    GLfloat surface7[3] = {0.0f, 0.0f, 5.0f};
    GLfloat surface8[3] = {5.0f, 0.0f, 5.0f};
    GLfloat surface9[3] = {5.0f, 0.0f, 0.0f};

    GLfloat color1[3] = {0.5f, 0.0f, 0.0f};
    GLfloat color2[3] = {0.0f, 0.0f, 0.5f};

    glBegin(GL_TRIANGLES);
        glColor3fv(color1);
        glVertex3fv(surface0);
        glVertex3fv(surface1);
        glVertex3fv(surface2);
        glColor3fv(color2);
        glVertex3fv(surface0);
        glVertex3fv(surface2);
        glVertex3fv(surface3);
        glColor3fv(color1);
        glVertex3fv(surface0);
        glVertex3fv(surface3);
        glVertex3fv(surface4);
        glColor3fv(color2);
        glVertex3fv(surface0);
        glVertex3fv(surface4);
        glVertex3fv(surface5);
        glColor3fv(color1);
        glVertex3fv(surface0);
        glVertex3fv(surface5);
        glVertex3fv(surface6);
        glColor3fv(color2);
        glVertex3fv(surface0);
        glVertex3fv(surface6);
        glVertex3fv(surface7);
        glColor3fv(color1);
        glVertex3fv(surface0);
        glVertex3fv(surface7);
        glVertex3fv(surface8);
        glColor3fv(color2);
        glVertex3fv(surface0);
        glVertex3fv(surface8);
        glVertex3fv(surface9);
    glEnd();
}

void RenderCheckboard()
{
    GLfloat v0[3], v1[3], v2[3], v3[3], delta;
    int color = 0;

    delta = 0.5f;

    //define the two colors
    GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
    GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

    v0[1] = v1[1] = v2[1] = v3[1] = 0.0f;

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

void GenerateStockScene(int id)
{
    glNewList(id, GL_COMPILE);
        if(id == 1) RenderCheckboard();
        if(id == 2) StockSceneTriangles();
    glEndList();

    id_selected = id;
}

void setup_opengl()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    if(lightMode){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    GenerateStockScene(1);
}

void RenderStockScene()
{
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
}

void RenderScene()
{
    glLineWidth(1);

    if(lightMode){
        GLfloat materialDiffuse[] = {0.2f,0.2f,0.2f,1.0f};
        GLfloat materialAmbient[] = {0.5f,0.5f,0.5f,1.0f};
        GLfloat lightPosition[] = {0.0f,3.0f,0.0f,1.0f};
        GLfloat lightAmbient[] = {0.0f,1.0f,0.0f,1.0f};
        GLfloat spotDirection[] = {-1.0f,-5.0f,0.0f};

        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5f);

        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);
    }

    glColor3f(0.0f,0.0f,0.0f);
    glutSolidSphere(0.3f,12,10);

    GLfloat color1[3] = {1.0f,0.0f,0.0f};
    GLfloat color2[3] = {0.0f,1.0f,0.0f};
    GLfloat color3[3] = {0.0f,0.0f,1.0f};
    GLfloat color4[3] = {1.0f,1.0f,1.0f};
    GLfloat color5[3] = {0.0f,0.0f,0.0f};
    GLfloat color6[3] = {1.0f,0.0f,1.0f};
    GLfloat color7[3] = {0.0f,1.0f,1.0f};
    GLfloat color8[3] = {1.0f,1.0f,0.0f};

    //Connect the four sides
    glBegin(GL_QUAD_STRIP);
        glColor3fv(color6);
        glVertex3f(-1.0f,1.0f,1.0f);
        glColor3fv(color1);
        glVertex3f(-1.0f,-1.0f,1.0f);
        glColor3fv(color4);
        glVertex3f(1.0f,1.0f,1.0f);
        glColor3fv(color8);
        glVertex3f(1.0f,-1.0f,1.0f);
        glColor3fv(color7);
        glVertex3f(1.0f,1.0f,-1.0f);
        glColor3fv(color2);
        glVertex3f(1.0f,-1.0f,-1.0f);
        glColor3fv(color3);
        glVertex3f(-1.0f,1.0f,-1.0f);
        glColor3fv(color5);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glColor3fv(color6);
        glVertex3f(-1.0f,1.0f,1.0f);
        glColor3fv(color1);
        glVertex3f(-1.0f,-1.0f,1.0f);
    glEnd();

    //The Bottom
    glBegin(GL_QUADS);
        glColor3fv(color1);
        glVertex3f(-1.0f,-1.0f,1.0f);
        glColor3fv(color8);
        glVertex3f(1.0f,-1.0f,1.0f);
        glColor3fv(color2);
        glVertex3f(1.0f,-1.0f,-1.0f);
        glColor3fv(color5);
        glVertex3f(-1.0f,-1.0f,-1.0f);
    glEnd();
}

void renderScene()
{
    float fps;

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);

    if(time - timebase > 1000){
        fps = frame*1000.0/(time-timebase);
        sprintf(fps_txt,"FPS: %4.2f",fps);
        timebase = time;
        frame = 0;
    }

    float fraction = fps/60;

    if(fps <= 40.0f)
        Sleep(4);
    else
        Sleep(8);

    static float cam_angle;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0f,0.0f,5.0f,
              0.0f,0.0f,0.0f,
              0.0f,1.0f,0.0f);

    glColor3f(1.0f,1.0f,1.0f);

    glTranslatef(-0.1f, -0.3f, -2.0f);
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(cam_angle++, -1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    //RenderStockScene();
    //glCallList(id_selected);
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
        case 76:
        case 108:
            if(!lightMode){
                lightMode = true;
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            } else {
                lightMode = false;
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
            }
    }
}

void processSpecialKeys(int key, int x, int y)
{
    //static bool alreadyGenerated;

    //switch(key){
    //    case GLUT_KEY_UP:
    //        if (id_selected < 2)
    //            id_selected++;

    //            if(!alreadyGenerated){
    //                GenerateStockScene(id_selected);
    //                alreadyGenerated = true;
    //            }
    //        break;
    //    case GLUT_KEY_DOWN:
    //        if (id_selected >= 2)
    //            id_selected--;
    //        break;
    //}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Colors and Lighting");

    setup_opengl();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
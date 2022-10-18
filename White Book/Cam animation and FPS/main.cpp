#include <windows.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <stdio.h>

float ratio;
int id_selected;
int time;
int frame = 0; int timebase = 0;
char fps_txt[30];

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
    glRotatef(angle++*2, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireSphere(0.6f,12,10);
    glColor3f(0.5f, 0.5f, 1.0f);
    glutWireCube(1.0f);
    glColor3f(0.7f,0.7f,0.7f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidTeapot(0.5f);
}

void renderBitmapString(float x, float y, void* font, char* string)
{
    char* c;
    glRasterPos2f(x, y);
    for(c = string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

void renderStrokeString(float x, float y, float z, char* string)
{
    char* c;

    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(30.0f,0.0f,1.0f,0.0f);
    glScalef(1/152.38, 1/152.38, 1/152.38);
    for(c = string; *c; c++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
    }
    glPopMatrix();
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
    renderBitmapString(-0.6f,1.2f,GLUT_BITMAP_TIMES_ROMAN_24,"This is a teapot");
    renderBitmapString(-2.05f,1.9f,GLUT_BITMAP_HELVETICA_18,fps_txt);
    renderBitmapString(-1.9f,-1.2f,GLUT_BITMAP_TIMES_ROMAN_24,"Use up and down keys to change stock scene");

    glTranslatef(-0.2f, -0.7f, -2.0f);
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(cam_angle++, 0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    RenderStockScene();
    glCallList(id_selected);
    glPopMatrix();

    glPushMatrix();
    RenderScene();
    glPopMatrix();

    glColor3f(1.0f,0.0f,0.0f);
    renderStrokeString(-4.0f,1.0f,-5.0f,"I'm 3D text");

    glColor3f(0.0f,1.0f,0.0f);
    renderStrokeString(-3.5f,1.0f,-4.0f,"I'm 3D text");

    glColor3f(0.0f,0.0f,1.0f);
    renderStrokeString(-3.0f,1.0f,-3.0f,"I'm 3D text");

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
    static bool alreadyGenerated;

    switch(key){
        case GLUT_KEY_UP:
            if (id_selected < 2)
                id_selected++;

                if(!alreadyGenerated){
                    GenerateStockScene(id_selected);
                    alreadyGenerated = true;
                }
            break;
        case GLUT_KEY_DOWN:
            if (id_selected >= 2)
                id_selected--;
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Cam animation and FPS");

    setup_opengl();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
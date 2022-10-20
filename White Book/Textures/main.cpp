#include <windows.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <GL/glaux.h>

#include "image.h"

float ratio;
int id_selected;
int time;
int frame = 0; int timebase = 0;
int zoom = 5;
char fps_txt[30];
bool debugLights;
bool filter_mode;
AUX_RGBImageRec* image;

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

void GenerateScene()
{
    glNewList(3, GL_COMPILE);
        glTranslatef(0.0f,0.0f,1.0f);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(-1.0f,-1.0f,0.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(-1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(1.0f,-1.0f,0.0f);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(-1.0f,-1.0f,-2.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(-1.0f,1.0f,-2.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(-1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(-1.0f,-1.0f,0.0f);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(1.0f,-1.0f,-2.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(1.0f,1.0f,-2.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(1.0f,-1.0f,0.0f);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(-1.0f,-1.0f,-2.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(-1.0f,1.0f,-2.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(1.0f,1.0f,-2.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(1.0f,-1.0f,-2.0f);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(-1.0f,-1.0f,-2.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(-1.0f,-1.0f,0.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(1.0f,-1.0f,0.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(1.0f,-1.0f,-2.0f);
        glEnd();

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(-1.0f,1.0f,-2.0f);
            glTexCoord2f(0.0f,6.0f);
            glVertex3f(-1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,6.0f);
            glVertex3f(1.0f,1.0f,0.0f);
            glTexCoord2f(6.0f,0.0f);
            glVertex3f(1.0f,1.0f,-2.0f);
        glEnd();
    glEndList();
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
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    image = auxDIBImageLoadA("clouds.bmp");

    GenerateStockScene(1);
    GenerateScene();
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

void RenderLights()
{
    glEnable(GL_LIGHTING);
    glNormal3f(0,1,0); //This seems to fix the issue, kinda

    GLfloat materialSpecular[4] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat materialShininess[1] = {128.0f};
    GLfloat materialAmbient[4] = {0.25f,0.25f,0.25f,1.0f};
    GLfloat materialDiffuse[4] = {0.4f,0.4f,0.4f,1.0f};
    GLfloat local_ambient[] = {0.0f,0.0f,0.0f,1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,local_ambient);

    GLfloat ambient0[] = {0.0f,0.0f,0.0f,1.0f};
    GLfloat white[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat specular0[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat position0[] = {-2.0f,0.0f,0.0f,1.0f};

    GLfloat ambient1[] = {0.0f,0.0f,0.0f,1.0f};
    GLfloat red[] = {1.0,0.0f,0.0f,1.0f};
    GLfloat specular1[] = {1.0f,0.0f,0.0f,1.0f};
    GLfloat position1[] = {2.0f,2.0f,0.0f,1.0f};

    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient0);
    glLightfv(GL_LIGHT0,GL_POSITION,position0);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular0);

    glLightfv(GL_LIGHT1,GL_AMBIENT,ambient1);
    glLightfv(GL_LIGHT1,GL_POSITION,position1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,red);
    glLightfv(GL_LIGHT1,GL_SPECULAR,specular1);

    glMaterialfv(GL_FRONT,GL_SPECULAR,materialSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,materialShininess);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,materialDiffuse);
    glMaterialfv(GL_FRONT,GL_AMBIENT,materialAmbient);

    if(debugLights){
        /* I don't know why when I enable debug mode, the lighting is rendered
        properly? It's really weird, I added glNormal3f at the beginning of the function
        and in this condition at the end,so lighting stays the same. Without them, when the
        program starts, the red light is missing, but when I activate debug mode, now it's there.*/

        glDisable(GL_LIGHTING);
        glBindTexture(GL_TEXTURE_2D,NULL);

        glPushMatrix();
        glColor3fv(white);
        glTranslatef(position0[0], position0[1], position0[2]);
        glutWireSphere(0.15f, 12, 10);
        glPopMatrix();

        glPushMatrix();
        glColor3fv(red);
        glTranslatef(position1[0], position1[1], position1[2]);
        glutWireSphere(0.15, 12, 10);
        glPopMatrix();

        glEnable(GL_LIGHTING);
        glNormal3f(0,1,0);
        glColor3fv(white);
    }
}

void renderStrokeString(float x, float y, float z, char* string)
{
    char* c;

    glPushMatrix();
    glTranslatef(x,y,z);
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
        timebase = time;
        frame = 0;
    }

    float fraction = fps/60;

    if(fps <= 40.0f)
        Sleep(2);
    else
        Sleep(4);

    static float cam_angle;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0f,0.0f,(float)zoom,
              0.0f,0.0f,0.0f,
              0.0f,1.0f,0.0f);

    glColor3f(1.0f,1.0f,1.0f);

    //glTranslatef(-1.0f, -0.8f, -2.0f);
    //glRotatef(10.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(cam_angle++, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    //RenderStockScene();
    //glCallList(id_selected);
    glPopMatrix();

    glPushMatrix();
    RenderLights();
    GLuint gl_texture = SelectImage(image);
    glCallList(3);
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
            if(!debugLights){
                debugLights = true;
            } else {
                debugLights = false;
            }
    }
}

void processSpecialKeys(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP:
            if(zoom >= 2)
                zoom--;
            break;
        case GLUT_KEY_DOWN:
            zoom++;
            break;
        case GLUT_KEY_RIGHT:
            filter_mode = true;
            break;
        case GLUT_KEY_LEFT:
            filter_mode = false;
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(480,480);
    glutCreateWindow("Textures");

    setup_opengl();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}
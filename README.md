# OpenGL-SamplePrograms

This is all the programs I have made while reading the OpenGL white book, I have used a Windows 95 machine to make them, and I had fun while making them, learning stuff that I didn't know about OpenGL.

By the way, don't use GLUT, it sucks. GLUT gave me a hard time trying to terminate the process properly by pressing the X button but without success, so the only way to terminate the program properly is by pressing the esc key. If you happen to close the window by pressing the X button by accident, you have to open the task manager and terminate it manually, I tried many things to make it terminate properly but it's just too difficult for me, never had such issues with FreeGLUT, so I recommend using FreeGLUT instead.

Expect to see more sample programs in the future, including sample programs from the red book.

## Switch from GLUT to FreeGLUT
If you are going to follow my advice, don't forget to change `#include <GL/glut.h>` to `#include <GL/freeglut.h>` for every single program you want to compile.

Also remove `#define GLUT_DISABLE_ATEXIT_HACK` from the code, since that's no longer required for FreeGLUT.

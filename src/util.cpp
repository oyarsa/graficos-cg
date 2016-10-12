#include "util.h"
#include <cstring>
#include <GL/glut.h>

void print_string(void* font, GLfloat x, GLfloat y, const char* s)
{
    if (!s) return;

    glRasterPos2f(x, y);

    for (int i = 0; s[i]; i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

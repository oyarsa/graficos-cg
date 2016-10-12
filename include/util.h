#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <sstream>
#include <GL/gl.h>

/// Imprime uma string na tela
void print_string(void* font, GLfloat x, GLfloat y, const char* s);

template <typename T>
std::string to_string(const T& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

#endif // UTIL_H

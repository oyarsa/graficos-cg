#include "grafico.h"
#include <stdexcept>

const GLfloat Grafico::cor_horda[]    = {1.0f, 0.0f, 0.0f};
const GLfloat Grafico::cor_alianca[]  = {0.0f, 0.0f, 1.0f};

Grafico::Grafico(GLfloat tamanho_x, GLfloat tamanho_y)
    : Grafico({}, tamanho_x, tamanho_y) {}

Grafico::Grafico(const std::vector<Servidor>& servidores,
                 GLfloat tamanho_x, GLfloat tamanho_y)
    : servidores_{&servidores},
      tamanho_x_{tamanho_x},
      tamanho_y_{tamanho_y}
{}

const std::vector<Servidor>& Grafico::servidores() const
{
    return *servidores_;
}

GLfloat Grafico::tamanho_x() const
{
    return tamanho_x_;
}
GLfloat Grafico::tamanho_y() const
{
    return tamanho_y_;
}

void Grafico::set_servidores(const std::vector<Servidor>& servidores)
{
    servidores_ = &servidores;
}

void Grafico::set_tamanho_x(GLfloat tamanho_x)
{
    tamanho_x_ = tamanho_x;
}

void Grafico::set_tamanho_y(GLfloat tamanho_y)
{
    tamanho_y_ = tamanho_y;
}

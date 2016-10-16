#ifndef GRAFICO_PIZZA_H
#define GRAFICO_PIZZA_H

#include <GL/gl.h>
#include <vector>
#include "servidor.h"
#include "grafico.h"

class Grafico_pizza : public Grafico
{
    public:
        Grafico_pizza() = default;
        Grafico_pizza(GLfloat raio, GLfloat tamanho_x, GLfloat tamanho_y);

        Grafico_pizza(const std::vector<Servidor>& servidores, GLfloat raio,
                   GLfloat tamanho_x, GLfloat tamanho_y);
        void desenha() override;
        void configura_window(GLsizei x, GLsizei y,
                              GLsizei w, GLsizei h) override;
    private:
        void desenha_circulo(const Servidor& servidor, GLfloat x, GLfloat y, GLfloat raio);
        GLfloat raio_;
        void desenha_legenda();
};

#endif // GRAFICO_PIZZA_H

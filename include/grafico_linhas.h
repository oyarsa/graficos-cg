#ifndef GRAFICO_LINHAS_H
#define GRAFICO_LINHAS_H

#include <vector>
#include <tuple>
#include <GL/gl.h>
#include <GL/glut.h>
#include "grafico.h"

class Grafico_linhas : public Grafico
{
public:

    Grafico_linhas() = default;

    Grafico_linhas(GLfloat tamanho_x, GLfloat tamanho_y);

    Grafico_linhas(const std::vector<Servidor>& servidores,
                   GLfloat tamanho_x, GLfloat tamanho_y);

    /// Desenha um gráfico de barras na tela
    void desenha() override;
    /// Configura o recorte que será exibido
    void configura_window(GLsizei x, GLsizei y,
                          GLsizei w, GLsizei h) override;

private:

    void desenha_eixos();

    std::pair<GLfloat, GLfloat> calcular_dimensoes_x();

    void desenha_linhas(GLfloat pos_x, GLfloat tamanho_barras, GLfloat espaco_x);

    void desenha_legenda();

    GLfloat proporcao_barras_ = 5.0f;
    const GLfloat borda_x_;
    const GLfloat borda_y_;
};

#endif

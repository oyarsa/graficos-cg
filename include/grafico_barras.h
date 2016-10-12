#ifndef GRAFICO_BARRAS_H
#define GRAFICO_BARRAS_H

#include <vector>
#include <tuple>
#include <GL/gl.h>
#include <GL/glut.h>
#include "grafico.h"

class Grafico_barras : public Grafico
{
public:
    // Construtores

    /// Inicializa membros para valores padr�o
    /// `tamanho_x` e `tamanho_y` ser�o inicializados para 0.
    /// `servidores` ser� inicializado para vazio.
    Grafico_barras() = default;
    /// Inicializa `tamanho_x` e `tamanho_y` de acordo com os par�metros
    /// `servidores` ser� inicializado para vazio.
    Grafico_barras(GLfloat tamanho_x, GLfloat tamanho_y);
    /// Inicializa `tamanho_x`, `tamanho_y` e `servidores` de acordo com os
    /// par�metros, copiando o vector
    Grafico_barras(const std::vector<Servidor>& servidores,
                   GLfloat tamanho_x, GLfloat tamanho_y);

    /// Desenha um gr�fico de barras na tela
    void desenha() override;
    /// Configura o recorte que ser� exibido
    void configura_window(GLsizei x, GLsizei y,
                          GLsizei w, GLsizei h) override;

private:
    // Desenha as linhas dos eixos, assim como valores das porcentagens
    // do eixo Y
    void desenha_eixos();

    // Calcula o espa�o entre cada barra e o tamanho de cada uma
    // de acordo com o n�mero de servidores
    // @return Par (espaco_x, tamanho_barras)
    std::pair<GLfloat, GLfloat> calcular_dimensoes_x();

    // Desenha duas barras, uma para cada fac��o, come�ando na posi��o `pos_x`,
    // com largura `tamanho_barras`, de acordo com os dados do Servidor
    void desenha_barras(GLfloat pos_x, GLfloat tamanho_barras,
                        const Servidor& servidor);

    // Desenha a legenda no canto do gr�fico com as cores e nomes de cada fac��o
    void desenha_legenda();

    // Propor��o entre o espa�o entre as barras e o tamanho de cada barra
    GLfloat proporcao_barras_ = 5.0f;
    const GLfloat borda_x_;
    const GLfloat borda_y_;
};

#endif // GRAFICO_BARRAS_H

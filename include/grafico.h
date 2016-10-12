#ifndef GRAFICO_H
#define GRAFICO_H

#include <vector>
#include <GL/gl.h>
#include "servidor.h"

class Grafico
{
public:
    static const GLfloat cor_horda[];
    static const GLfloat cor_alianca[];

    // Construtores
    /// Inicializa membros para valores padr�o
    /// `tamanho_x` e `tamanho_y` ser�o inicializados para 0.
    /// `servidores` ser� inicializado para vazio.
    Grafico() = default;
    /// Inicializa `tamanho_x` e `tamanho_y` de acordo com os par�metros
    /// `servidores` ser� inicializado para vazio.
    Grafico(GLfloat tamanho_x, GLfloat tamanho_y);
    /// Inicializa `tamanho_x`, `tamanho_y` e `servidores` de acordo com os
    /// par�metros, copiando o vector
    Grafico(const std::vector<Servidor>& servidores,
            GLfloat tamanho_x, GLfloat tamanho_y);

    virtual ~Grafico() {}

    // Getters
    /// Retorna a lista de servidores que ir�o popular o gr�fico
    const std::vector<Servidor>& servidores() const;
    /// Retorna o tamanho do eixo X do gr�fico
    GLfloat tamanho_x() const;
    /// Retorna o tamanho do eixo Y do gr�fico
    GLfloat tamanho_y() const;

    // Setters
    /// Estabelece a lista de servidores que ir�o popular o gr�fico
    void set_servidores(const std::vector<Servidor>& servidores);
    /// Estabelece o tamanho do eixo X do gr�fico
    void set_tamanho_x(GLfloat tamanho_x);
    /// Estabelece o tamanho do eixo Y do gr�fico
    void set_tamanho_y(GLfloat tamanho_y);

    /// Desenha um gr�fico na tela
    virtual void desenha() = 0;
    /// Configura o recorte que ser� exibido
    virtual void configura_window(GLsizei x, GLsizei y,
                                  GLsizei w, GLsizei h) = 0;

private:
    // Lista de servidores que ir�o popular o gr�fico
    const std::vector<Servidor>* servidores_;
    // Tamanho do eixo X
    GLfloat tamanho_x_;
    // Tamanho do eixo Y
    GLfloat tamanho_y_;
};


#endif // GRAFICO_H

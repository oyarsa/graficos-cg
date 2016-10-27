#include "grafico_linhas.h"
#include <stdexcept>
#include <cstdio>
#include "util.h"
#include <vector>

Grafico_linhas::Grafico_linhas(GLfloat tamanho_x, GLfloat tamanho_y)
    : Grafico_linhas({}, tamanho_x, tamanho_y) {}

Grafico_linhas::Grafico_linhas(const std::vector<Servidor>& servidores,
                               GLfloat tamanho_x, GLfloat tamanho_y)
    : Grafico(servidores, tamanho_x, tamanho_y),
      borda_x_{tamanho_x/10 * 2.0f},
      borda_y_{tamanho_y/10 * 1.0f}{}


void Grafico_linhas::desenha()
{

    GLfloat espaco_x, tamanho_barras;
    std::tie(espaco_x, tamanho_barras) = calcular_dimensoes_x();

    GLfloat pos_x = espaco_x;


    desenha_linhas(pos_x, tamanho_barras, espaco_x);

    ///faz os nomes aparecerem embaixo do grafico na ordem correta
    for (Servidor servidor : servidores()) {
        auto fonte = servidores().size() < 6 ? GLUT_BITMAP_HELVETICA_12 : GLUT_BITMAP_HELVETICA_10;
        print_string(fonte, pos_x, -0.4f, servidor.nome().c_str());
        pos_x += espaco_x + tamanho_barras;
    }

    desenha_eixos();
    print_string(GLUT_BITMAP_HELVETICA_18, tamanho_x() / 5, -(2*borda_y_/3),
                 "Porcentagem das faccoes por servidor");
    desenha_legenda();
}

void Grafico_linhas::desenha_eixos()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    const auto max_x = tamanho_x() + borda_x_/3;
    const auto max_y = tamanho_y() + borda_y_/3;

    // Desenhar uma linha de 0,0 a 0,tamanho_y
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, max_y);
    glEnd();
    // Desenha seta que indica direção do eixo
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f, max_y);
        glVertex2f(0.2f, max_y);
        glVertex2f(0.0f, max_y + 0.4f);
    glEnd();

    const auto espaco_txt = 0.7f*tamanho_x()/10;
    // Imprimir a legenda do eixo (% facção)
    print_string(GLUT_BITMAP_9_BY_15, -espaco_txt, max_y + 0.5f, "% Faccao");

    // Desenhar os traços das porcentagens
    auto delta = tamanho_y() / 10;
    glBegin(GL_LINES);
    for (GLfloat y = delta; y <= tamanho_y(); y += delta) {
        glVertex2f(-0.1f, y);
        glVertex2f(0.1f, y);
    }
    glEnd();

    // Desenha texto das porcentagens
    for (GLfloat y = delta; y <= tamanho_y(); y += delta) {
        auto val = y / tamanho_y() * 100;
        print_string(GLUT_BITMAP_9_BY_15, -espaco_txt, y, to_string(val).c_str());
    }

    // Desenhar uma linha de 0,0 a tamanho_x,0
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(max_x, 0.0f);
    glEnd();
    // Desenha seta que indica direção do eixo
    glBegin(GL_TRIANGLES);
        glVertex2f(max_x, -0.2f);
        glVertex2f(max_x, 0.2f);
        glVertex2f(max_x + 0.4f, 0.0f);
    glEnd();

    // Imprimir a legenda do eixo (nome do servidor)
    print_string(GLUT_BITMAP_9_BY_15, max_x + 0.5f, 0.0f, "Nome do");
    print_string(GLUT_BITMAP_9_BY_15, max_x + 0.5f, -0.3f, "servidor");
}

std::pair<GLfloat, GLfloat> Grafico_linhas::calcular_dimensoes_x()
{
    const auto n = servidores().size();
    GLfloat espaco_x = tamanho_x() / (n * (proporcao_barras_ + 1));
    GLfloat tamanho_barras = proporcao_barras_ * espaco_x;
    return {espaco_x, tamanho_barras};
}

void Grafico_linhas::desenha_linhas(GLfloat pos_x, GLfloat tamanho_barras, GLfloat espaco_x)
{
    auto x = pos_x;

    ///desenha a linha do grafico da horda
    glColor3fv(Grafico::cor_horda);
    glBegin(GL_LINE_STRIP);
        for (const Servidor& servidor : servidores()) {
            glVertex2f(x, servidor.porcentagem_horda() * tamanho_y());
                x += espaco_x + tamanho_barras;
        }
    glEnd();

    x = pos_x;

    ///desenha a linha do grafico da alliança
    glColor3fv(Grafico::cor_alianca);
    glBegin(GL_LINE_STRIP);
        for (const Servidor& servidor : servidores()) {
            glVertex2f(x, servidor.porcentagem_alianca()* tamanho_y());
            x += espaco_x + tamanho_barras;
        }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
}

void Grafico_linhas::desenha_legenda()
{
    // Tamanho X e Y da legenda
    const auto tam_x = 3.5f * tamanho_x() / 10;
    const auto tam_y = 2.0f * tamanho_y() / 10;
    // Ponto de origem do quadrado da legenda no espaço
    const auto origem_x = tamanho_x() - tam_x + 1.25f*borda_x_;
    const auto origem_y = tamanho_y() - tam_y + borda_y_ - 0.5f;

    // Tamanho dos quadrados das cores
    const auto tam_quad = 0.25f * tam_y;
    // Tamanho Y do texto 'Legenda'
    const auto tam_texto_y = 0.2f * tam_y;

    // Comprimento Y do espaço entre a borda e o conteúdo
    const auto borda_leg_y = 0.1125 * tam_y;
    // Espaço entre os dois itens
    const auto espaco_y = 0.075f * tam_y;

    // Comprimento X do espaço entre a borda e o conteúdo
    const auto borda_leg_x = 0.1f * tam_x;

    // Leva o eixo para a origem da legenda
    glTranslatef(origem_x, origem_y, 0.0f);

    // Desenha o contorno
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, tam_y);
        glVertex2f(tam_x, tam_y);
        glVertex2f(tam_x, 0.0f);
    glEnd();

    // Desenhar um quadradado de cor Grafico::cor_alianca e a legenda "Aliança"
    auto pos_y = borda_leg_y;

    glColor3fv(Grafico::cor_alianca);
    glBegin(GL_QUADS);
        glVertex2f(borda_leg_x, pos_y);
        glVertex2f(borda_leg_x, pos_y + tam_quad);
        glVertex2f(borda_leg_x + tam_quad, pos_y + tam_quad);
        glVertex2f(borda_leg_x + tam_quad, pos_y);
    glEnd();

    // Imprime texto "Aliança"
    glColor3f(0.0f, 0.0f, 0.0f);
    print_string(GLUT_BITMAP_9_BY_15, borda_leg_x + tam_quad + 0.15f,
                 pos_y + 0.2f, "Alianca");

    // Desenhar um quadradado de cor Grafico::cor_horda e a legenda "Horda"
    pos_y += tam_quad + espaco_y;

    glColor3fv(Grafico::cor_horda);
    glBegin(GL_QUADS);
        glVertex2f(borda_leg_x, pos_y);
        glVertex2f(borda_leg_x, pos_y + tam_quad);
        glVertex2f(borda_leg_x + tam_quad, pos_y + tam_quad);
        glVertex2f(borda_leg_x + tam_quad, pos_y);
    glEnd();

    // Imprime texto "Horda"
    glColor3f(0.0f, 0.0f, 0.0f);
    print_string(GLUT_BITMAP_9_BY_15, borda_leg_x + tam_quad + 0.15f,
                 pos_y + 0.2f, "Horda");

    // Desenha o texto "Legenda"
    pos_y += tam_quad + tam_texto_y/2;
    glColor3f(0.0f, 0.0f, 0.0f);
    auto posicao_leg_x = tam_x/8 * tamanho_x()/10; // tentativa de centralizar o texto
    print_string(GLUT_BITMAP_TIMES_ROMAN_24, posicao_leg_x, pos_y, "Legenda");
}

void Grafico_linhas::configura_window(GLsizei x, GLsizei y,
                                      GLsizei w, GLsizei h)
{
    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const auto centro_x = (2*borda_x_ + tamanho_x()) / 2;
    const auto centro_y = (2*borda_y_ + tamanho_y()) / 2;

    const GLdouble left = -0.75*borda_x_;
    const GLdouble right = tamanho_x() + 1.5*borda_x_;
    const GLdouble bottom = -borda_y_;
    const GLdouble top = tamanho_y() + borda_y_;

    if (w <= h) {
        auto delta = centro_y*h/w - centro_y;
        gluOrtho2D(left, right, bottom-delta, top+delta);
    } else {
        auto delta = centro_x*w/h - centro_x;
        gluOrtho2D(left-delta, right+delta, bottom, top);
    }
}

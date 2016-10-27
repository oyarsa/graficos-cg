#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <grafico_pizza.h>
#include <cstdlib>
#include <util.h>

const auto M_PI = acos(-1);

Grafico_pizza::Grafico_pizza(GLfloat raio, GLfloat tamanho_x, GLfloat tamanho_y)
    : Grafico_pizza({}, raio, tamanho_x, tamanho_y) {}


Grafico_pizza::Grafico_pizza(const std::vector<Servidor>& servidores, GLfloat raio,
                             GLfloat tamanho_x, GLfloat tamanho_y)
    : Grafico(servidores, tamanho_x, tamanho_y),
      raio_{raio} {}

// Função callback de redesenho da janela de visualização
void Grafico_pizza::desenha_circulo(const Servidor& servidor, GLfloat x, GLfloat y, GLfloat raio)
{
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
    float i = 0;
    int numTriangulos = 40;
    GLfloat ang_tri = 2*M_PI/numTriangulos;
	// Altera a cor do desenho para cinza
	glColor3fv(Grafico::cor_alianca);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x,y);
	for(; i <= servidor.porcentagem_alianca()*numTriangulos; i++){
        glVertex2f(
            x + (raio * cos(i * ang_tri)),
            y + (raio * sin(i * ang_tri))
        );

	}
    glVertex2f(
            x + (raio * cos(i * ang_tri)),
            y + (raio * sin(i * ang_tri))
        );
	glEnd();

    glColor3fv(Grafico::cor_horda);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x,y);
	for(; i <= numTriangulos; i++){
        glVertex2f(
            x + (raio * cos(i * ang_tri)),
            y + (raio * sin(i * ang_tri))
        );
	}glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    print_string(GLUT_BITMAP_HELVETICA_18, -2.0f, -raio_ - 2.0f, servidor.nome().c_str());

    glColor3fv(Grafico::cor_alianca);
    print_string(GLUT_BITMAP_HELVETICA_12, raio_ + 1.0f, 1.0f,
                 (to_string(servidor.porcentagem_alianca() * 100) + "%").c_str());

    glColor3fv(Grafico::cor_horda);
    print_string(GLUT_BITMAP_HELVETICA_12, raio_ + 1.0f, -1.0f,
                 (to_string(servidor.porcentagem_horda() * 100) + "%").c_str());
}

void Grafico_pizza::desenha() {
    auto idx_servidor = rand() % servidores().size();
    const auto& servidor = servidores()[idx_servidor];
    glClear(GL_COLOR_BUFFER_BIT);
    desenha_circulo(servidor, 0.0f ,0.0f , raio_);

    glColor3f(0.0f, 0.0f, 0.0f);
    print_string(GLUT_BITMAP_TIMES_ROMAN_24, -tamanho_x() / 2.0f, -(3.0f*tamanho_y()/4.0f),
                 "Porcentagem das faccoes por servidor");

    print_string(GLUT_BITMAP_9_BY_15, tamanho_x()/10.0f, -0.975f*tamanho_y(),
                 "Pressione 3 para trocar de servidor");
    desenha_legenda();
    glFlush();
}

void Grafico_pizza::desenha_legenda()
{
    // Tamanho X e Y da legenda
    const auto tam_x = 4.5f * tamanho_x() / 10;
    const auto tam_y = 3.0f * tamanho_y() / 10;
    // Ponto de origem do quadrado da legenda no espaço
    const auto origem_x = 0.9*tamanho_x() - tam_x;
    const auto origem_y = 0.8*tamanho_y() - tam_y;

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

// Função callback chamada quando o tamanho da janela é alterado
void Grafico_pizza::configura_window(GLsizei x, GLsizei y,
                                     GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(x, y, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior,
	// superior) mantendo a proporção com a janela de visualização
	if (w <= h)
		gluOrtho2D (-tamanho_x(), tamanho_x(), -tamanho_y()*h/w, tamanho_y()*h/w);
	else
		gluOrtho2D (-tamanho_x()*w/h, tamanho_x()*w/h, -tamanho_y(), tamanho_y());
}


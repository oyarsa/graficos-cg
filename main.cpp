#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <memory>
#include <algorithm>

#include <parse_entrada.h>
#include <grafico.h>
#include <grafico_barras.h>
#include <grafico_linhas.h>
#include <util.h>

#ifdef _WIN32
const std::string caminho_padrao = "data\\data_us.json";
#else
const std::string caminho_padrao = "data/data_us.json";
#endif

const std::string nome_janela = "Gráficos";

const GLsizei tamanho_janela_x = 700;
const GLsizei tamanho_janela_y = 700;
const GLsizei posicao_inicial_x = 5;
const GLsizei posicao_inicial_y = 5;

static std::unique_ptr<Grafico> grafico{nullptr};
static std::vector<Servidor> servidores;

static GLsizei width;
static GLsizei height;

const static GLfloat proporcao_info = 0.05;
const GLdouble info_left = -100.0f;
const GLdouble info_right = 100.0f;
const GLdouble info_bottom = -10.0f;
const GLdouble info_top = 10.0f;

static GLsizei borda_y;
static GLsizei borda_x = 0;

void configura_window_info()
{
    glViewport(borda_x, 0, width-borda_x, borda_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(info_left, info_right, info_bottom, info_top);
}

void desenha_info_usuario()
{
    glColor3f(0.2, 0.2, 0.2);
    glRectf(info_left, info_bottom, info_right, info_top);

    const auto tam_y = info_top - info_bottom;
    const auto tam_x = info_right - info_left;

    glColor3f(1, 1, 1);
    print_string(GLUT_BITMAP_9_BY_15, info_left + tam_x/8,
                 info_bottom + tam_y/3, "1 - Barras");
    print_string(GLUT_BITMAP_9_BY_15, info_left + 3.5*tam_x/8,
                 info_bottom + tam_y/3, "2 - Linhas");
    print_string(GLUT_BITMAP_9_BY_15, info_left + 6*tam_x/8,
                 info_bottom + tam_y/3, "3 - Pizza");
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);

    grafico->configura_window(borda_x, borda_y, width-borda_x, height-borda_y);
    grafico->desenha();
    configura_window_info();
    desenha_info_usuario();

    glFlush();
}

void inicializa()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void altera_tam_janela(GLsizei w, GLsizei h)
{
    width = std::max(w, 1);
    height = std::max(h, 1);
    borda_y = static_cast<int>(proporcao_info * height);
}

void teclado(unsigned char key, int x, int y)
{
    switch (key) {
        case '1':
            grafico.reset(new Grafico_barras(servidores, 20, 20));
            break;
        case '2':
            grafico.reset(new Grafico_linhas(servidores, 20, 20));
            break;
        case '3':
            std::cout << "lets\n";
            break;
    }
    desenha();
}

void run_opengl()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(posicao_inicial_x, posicao_inicial_y);
	glutInitWindowSize(tamanho_janela_x, tamanho_janela_y);
	glutCreateWindow(nome_janela.c_str());
	glutDisplayFunc(desenha);
	glutReshapeFunc(altera_tam_janela);
	glutKeyboardFunc(teclado);
	inicializa();
	glutMainLoop();

}

template<typename Pred>
std::vector<Servidor> filtrar_servidores(
    const std::vector<Servidor>& servidores,
    Pred p
)
{
    std::vector<Servidor> novo;
    std::copy_if(begin(servidores), end(servidores), std::back_inserter(novo), p);
    return novo;
}

int main(int argc, char *argv[])
{
    std::string caminho;

    if (argc == 2) {
        caminho = argv[1];
    } else {
        caminho = caminho_padrao;
    }

    servidores = carregar_servidores(caminho);
    grafico.reset(new Grafico_barras(servidores, 20, 20));
    servidores = filtrar_servidores(servidores, [](const Servidor& s) {
        return s.regiao() == "Brazil";
    });

    run_opengl();
}

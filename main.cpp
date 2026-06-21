#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Botao.h"
#include "ferramentas/FerramentaPonto.h"
#include "ferramentas/FerramentaLinha.h"        
#include "ferramentas/FerramentaPoligono.h"
#include "ferramentas/FerramentaSelecao.h"
#include "Controlador.h"

Ferramenta* ferramentaAtiva = nullptr;
std::vector<Forma*> desenhosNaTela;
std::vector<Botao> meusBotoes;

FerramentaPonto ferramentaPonto;
FerramentaLinha ferramentaLinha;
FerramentaPoligono ferramentaPoligono;
FerramentaSelecao ferramentaSelecao;
bool desenhandoNaTela = false;

Controlador controlador(meusBotoes, desenhosNaTela, ferramentaAtiva, desenhandoNaTela);

int larguraJanela = 800;
int alturaJanela = 600;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void reshape(int w, int h) {
    larguraJanela = w;
    alturaJanela = h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void desenharTexto(float x, float y, void* fonte, std::string texto) {
    glRasterPos2f(x, y);
    for (char c : texto) {
        glutBitmapCharacter(fonte, c);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (Botao& b : meusBotoes) {
        b.desenhar();
    }

    for (Forma* f : desenhosNaTela) {
        f->desenhar();
    }

    if (ferramentaAtiva == &ferramentaPoligono) {
        glColor3f(0.4f, 0.4f, 0.4f); 
        desenharTexto(2.0f, 3.0f, GLUT_BITMAP_HELVETICA_12, "Dica: Pressione ESC para fechar o poligono.");
    } 
    else if (ferramentaAtiva == &ferramentaLinha) {
        glColor3f(0.4f, 0.4f, 0.4f);
        desenharTexto(2.0f, 3.0f, GLUT_BITMAP_HELVETICA_12, "Dica: Pressione ENTER, ESPACO ou ESC para reiniciar a reta.");
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    float mundoX = x * (200.0f / larguraJanela);
    float mundoY = (alturaJanela - y) * (150.0f / alturaJanela);
    
    controlador.processarMouse(button, state, mundoX, mundoY);
    glutPostRedisplay();
}

void multiplicarMatrizes(float m1[3][3], float m2[3][3], float res[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i][j] = 0.0f;
            for (int k = 0; k < 3; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void transformarComPontoFixo(Forma* f, float matrizBase[3][3]) {
    float cx, cy;
    f->obterCentro(cx, cy);

    // matriz de translação - leva o centroide para a origem 
    float tIda[3][3] = {
        {1.0f, 0.0f, -cx},
        {0.0f, 1.0f, -cy},
        {0.0f, 0.0f, 1.0f}
    };

    // matriz de translação - coloca o centróide a posiçao original 
    float tVolta[3][3] = {
        {1.0f, 0.0f, cx},
        {0.0f, 1.0f, cy},
        {0.0f, 0.0f, 1.0f}
    };

    float temp[3][3];
    float matrizComposta[3][3];

    // concatenação depois da multiplicacao 
    multiplicarMatrizes(matrizBase, tIda, temp);
    multiplicarMatrizes(tVolta, temp, matrizComposta);

    f->aplicarTransformacao(matrizComposta);
}

void keyboard(unsigned char key, int x, int y) {
    // 13 = Enter | 27 = Esc | 32 = Barra de Espaço
    if (key == 13 || key == 27 || key == 32) { 
        if (ferramentaAtiva != nullptr) {
            ferramentaAtiva->finalizar_acao();
            glutPostRedisplay(); 
        }
    }

    // pega o desenho selecionado
    Forma* selecionada = nullptr;
    for (Forma* f : desenhosNaTela) {
        if (f->selecionada) {
            selecionada = f;
            break;
        }
    }

    if (selecionada != nullptr) {
        if (key == 'x' || key == 'X') {
            // reflexao baseado no eixo x fixo (ref vertical - eixo y que muda)
            float mReflexaoX[3][3] = {
                {1.0f,  0.0f, 0.0f},
                {0.0f, -1.0f, 0.0f},
                {0.0f,  0.0f, 1.0f}
            };
            transformarComPontoFixo(selecionada, mReflexaoX);
            glutPostRedisplay();
        }
        else if (key == 'y' || key == 'Y') {
            // reflexao baseado no eixo y fixo (ref vertical - eixo x que muda)
            float mReflexaoY[3][3] = {
                {-1.0f, 0.0f, 0.0f},
                {0.0f,  1.0f, 0.0f},
                {0.0f,  0.0f, 1.0f}
            };
            transformarComPontoFixo(selecionada, mReflexaoY);
            glutPostRedisplay();
        }
        else if (key == 'h' || key == 'H') {
            // cisalhamento horizontal (distorce no eixo x)
            float shx = 0.2f; 
            float mCisalhamentoH[3][3] = {
                {1.0f,  shx,  0.0f},
                {0.0f, 1.0f,  0.0f},
                {0.0f, 0.0f,  1.0f}
            };
            transformarComPontoFixo(selecionada, mCisalhamentoH);
            glutPostRedisplay();
        }
        else if (key == 'v' || key == 'V') {
            // cisalhamento vertical (distorce no eixo y)
            float shy = 0.2f; 
            float mCisalhamentoV[3][3] = {
                {1.0f, 0.0f,  0.0f},
                {shy,  1.0f,  0.0f},
                {0.0f, 0.0f,  1.0f}
            };
            transformarComPontoFixo(selecionada, mCisalhamentoV);
            glutPostRedisplay();
        }
    }
}

void motion(int x, int y) {
    float mundoX = x * (200.0f / larguraJanela);
    float mundoY = (alturaJanela - y) * (150.0f / alturaJanela);
    
    controlador.processarMotion(mundoX, mundoY);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Paint");
    
    init();
    
    meusBotoes.push_back(Botao(2, 136, 28, 12, "Ponto", &ferramentaPonto));
    meusBotoes.push_back(Botao(32, 136, 28, 12, "Reta", &ferramentaLinha));
    meusBotoes.push_back(Botao(62, 136, 40, 12, "Poligono", &ferramentaPoligono));
    meusBotoes.push_back(Botao(104, 136, 35, 12, "Selecionar", &ferramentaSelecao));

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}
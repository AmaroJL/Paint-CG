#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Botao.h"
#include "FerramentaPincel.h"
#include "Controlador.h"

Ferramenta* ferramentaAtiva = nullptr;
std::vector<Forma*> desenhosNaTela;
std::vector<Botao> meusBotoes;

FerramentaPincel ferramentaPincel;
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

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (Botao& b : meusBotoes) {
        b.desenhar();
    }

    for (Forma* f : desenhosNaTela) {
        f->desenhar();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    float mundoX = x * (200.0f / larguraJanela);
    float mundoY = (alturaJanela - y) * (150.0f / alturaJanela);
    
    controlador.processarMouse(button, state, mundoX, mundoY);
    glutPostRedisplay();
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
    
    meusBotoes.push_back(Botao(2, 136, 28, 12, "Pincel", &ferramentaPincel));
  
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}
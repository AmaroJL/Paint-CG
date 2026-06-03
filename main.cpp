#include <GL/glut.h>
#include <vector>
#include <iostream>

// --- 1. ESTRUTURAS DE DADOS ---

enum TipoObjeto {
    PONTO,
    RETA,
    POLIGONO
};

struct Ponto2D {
    float x, y;
};

struct Objeto {
    TipoObjeto tipo;
    std::vector<Ponto2D> vertices; // Guarda os cliques que formam a figura
    
    bool selecionado = false; 

    // Valores para as futuras transformações geométricas (mover, girar, escalar)
    float translacaoX = 0.0f, translacaoY = 0.0f;
    float angulo = 0.0f;
    float escalaX = 1.0f, escalaY = 1.0f;
};

// Guarda tudo o que for criado na tela
std::vector<Objeto> cena;

int larguraJanela = 800;
int alturaJanela = 600;


// --- 2. CONFIGURAÇÕES DO OPENGL ---

void inicializa() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void redimensiona(int w, int h) {
    larguraJanela = w;
    alturaJanela = h;

    glViewport(0, 0, w, h); 
    
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();            

    // Inversão do eixo Y (passando 'h' na base e '0' no topo).
    // Isso faz o (0,0) ficar no canto superior esquerdo, casando com a coordenada do clique do mouse.
    gluOrtho2D(0, w, h, 0);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT); 


    glFlush(); // Manda a placa de vídeo renderizar as formas imediatamente
}


// --- 3. FUNÇÃO PRINCIPAL ---

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutInitWindowPosition(100, 100); 
    
    glutCreateWindow("Meu Paint em OpenGL - Projeto de CG");

    inicializa();

    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);

    glutMainLoop();

    return 0;
}
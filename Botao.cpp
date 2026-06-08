#include "Botao.h"

Botao::Botao(float x, float y, float w, float h, std::string texto, Ferramenta* ferramenta) {
    this->x = x;
    this->y = y;
    this->largura = w;
    this->altura = h;
    this->texto = texto;
    this->ferramenta = ferramenta;
}

void Botao::realizar_acao() {
    if (ferramentaAtiva == ferramenta) {
        ferramentaAtiva = nullptr;
    } else {
        ferramentaAtiva = ferramenta;
    }
}

void Botao::desenhar() {
    if (ferramentaAtiva == ferramenta && ferramenta != nullptr) {
        glColor3f(0.4f, 0.7f, 1.0f);
    } else {
        glColor3f(0.2f, 0.5f, 0.8f);
    }
    
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    
    float larguraTexto = texto.length() * 1.5f;
    float centroX = x + (largura - larguraTexto) / 2.0f;
    float centroY = y + (altura - 3.0f) / 2.0f;
    
    glRasterPos2f(centroX, centroY);
    
    for(char c : texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }  
}

bool Botao::clicado(float mundoX, float mundoY) {
    if (mundoX >= x && mundoX <= x + largura &&
        mundoY >= y && mundoY <= y + altura) {
        return true;
    }
    return false;
}
#ifndef LINHAFORMA_H
#define LINHAFORMA_H

#include "Forma.h"
#include <GL/glut.h>
#include <cmath>

class LinhaForma : public Forma {
private:
    static const int DENTRO = 0;   // 0000
    static const int ESQUERDA = 1; // 0001
    static const int DIREITA = 2;  // 0010
    static const int BAIXO = 4;    // 0100
    static const int CIMA = 8;     // 1000

    // Verifica onde um ponto está em relação ao retângulo de tolerância
    int calcularCodigoDeRegiao(float px, float py, float xmin, float xmax, float ymin, float ymax) {
        int codigo = DENTRO;
        if (px < xmin)      codigo |= ESQUERDA;
        else if (px > xmax) codigo |= DIREITA;
        if (py < ymin)      codigo |= BAIXO;
        else if (py > ymax) codigo |= CIMA;
        return codigo;
    }

public:
    float x1, y1, x2, y2;

    LinhaForma(float x, float y) : x1(x), y1(y), x2(x), y2(y) {}
    
    void setFim(float x, float y) { 
        x2 = x; 
        y2 = y; 
    }
    
    void desenhar() override {
        glPushMatrix(); // Salva a matriz do universo atual
        glTranslatef(novox, novoy, 0.0f); // Move o universo, o fundo

        glLineWidth(4.0f);

        if (selecionada) glColor3f(1.0f, 0.5f, 0.0f);
        else glColor3f(0.0f, 0.0f, 1.0f);

        
        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        glLineWidth(1.0f);

        glPointSize(4.0f);
        glBegin(GL_POINTS);
            glVertex2f(x1, y1); // Marca o local do 1º clique
            
            if (x1 != x2 || y1 != y2) {
                glVertex2f(x2, y2); 
            }
        glEnd();

        glPopMatrix(); // Restaura o universo
    }

    bool clicado(float mx, float my, float tol) override {
        // Seleção desativada para a ferramenta Reta a pedido do usuário
        return false;
    }
};

#endif
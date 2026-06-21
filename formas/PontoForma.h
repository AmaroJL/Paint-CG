#ifndef PONTOFORMA_H
#define PONTOFORMA_H

#include "Forma.h"
#include <GL/glut.h>

class PontoForma : public Forma {
private:
    float x, y;
public:
    PontoForma(float x, float y) : x(x), y(y) {}
    void desenhar() override {
        glPushMatrix();
        glTranslatef(novox, novoy, 0.0f);
        
        glPointSize(10.0f);

        if (selecionada) glColor3f(1.0f, 0.5f, 0.0f);
        else glColor3f(1.0f, 0.0f, 0.0f);
        
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
        
        glPopMatrix();
    }

    bool clicado(float mx, float my, float tol) override {
        if (x >= (mx - tol) && x <= (mx + tol) && y >= (my - tol) && y <= (mx + y)) {
            return true;
        } 
        return false;
    }

    void aplicarTransformacao(float m[3][3]) override {
        float nx = m[0][0] * x + m[0][1] * y + m[0][2] * 1.0f;
        float ny = m[1][0] * x + m[1][1] * y + m[1][2] * 1.0f;
        x = nx;
        y = ny;
    }

    void obterCentro(float &cx, float &cy) override {
        cx = x;
        cy = y;
    }
};

#endif
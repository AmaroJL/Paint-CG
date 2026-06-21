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
};

#endif
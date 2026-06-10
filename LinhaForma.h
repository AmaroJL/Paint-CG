#ifndef LINHAFORMA_H
#define LINHAFORMA_H

#include "Forma.h"
#include <GL/glut.h>

class LinhaForma : public Forma {
public:
    float x1, y1, x2, y2;

    LinhaForma(float x, float y) : x1(x), y1(y), x2(x), y2(y) {}
    
    void setFim(float x, float y) { 
        x2 = x; 
        y2 = y; 
    }
    
    void desenhar() override {
        glLineWidth(4.0f);
        glColor3f(0.0f, 0.0f, 1.0f); // Azul
        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        glPointSize(4.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POINTS);
            glVertex2f(x1, y1); // Marca o local do 1º clique
            
            if (x1 != x2 || y1 != y2) {
                glVertex2f(x2, y2); 
            }
        glEnd();
    }
};

#endif
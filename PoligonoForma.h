#ifndef POLIGONOFORMA_H
#define POLIGONOFORMA_H

#include "Forma.h"
#include <GL/glut.h>
#include <vector>

class PoligonoForma : public Forma {
public:
    struct Vertice { float x, y; };
    std::vector<Vertice> vertices;

    PoligonoForma(float x, float y) {
        addVertice(x, y);
    }
    
    void addVertice(float x, float y) {
        vertices.push_back({x, y});
    }
    
    void desenhar() override {
        if (vertices.empty()) return;
        
        // Preenche o interior do poligno
        glColor3f(0.2f, 0.8f, 0.2f);
        glBegin(GL_POLYGON);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
        
        // Linha de referência para usuário
        glColor3f(0.2f, 0.8f, 0.2f);
        glLineWidth(4.0f);
        glBegin(GL_LINE_LOOP);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();

        // Adiciona um ponto como referência para usuário
        glPointSize(4.0f);
        glColor3f(0.2f, 0.8f, 0.2f);
        glBegin(GL_POINTS);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
    }
};

#endif
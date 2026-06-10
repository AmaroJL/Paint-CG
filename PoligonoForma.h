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
        
        // Desenha o interior do polígono (Verde)
        glColor3f(0.2f, 0.8f, 0.2f); 
        glBegin(GL_POLYGON);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
        
        // Desenha o contorno do polígono (Preto) para melhor visualização
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
    }
};

#endif
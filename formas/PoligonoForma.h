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

        glPushMatrix();
        glTranslatef(novox, novoy, 0.0f);
        
        if (selecionada) glColor3f(1.0f, 0.5f, 0.0f);
        else glColor3f(0.2f, 0.8f, 0.2f);

        // Preenche o interior do poligno
        glBegin(GL_POLYGON);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
        
        // Linha de referência para usuário
        glLineWidth(4.0f);
        glBegin(GL_LINE_LOOP);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();

        glLineWidth(1.0f);

        // Adiciona um ponto como referência para usuário
        glPointSize(4.0f);
        glBegin(GL_POINTS);
        for (auto& v : vertices) {
            glVertex2f(v.x, v.y);
        }
        glEnd();

        glPopMatrix();
    }

    bool clicado(float mx, float my, float tol) override {
        if (vertices.size() < 3) return false;
        
        float mx_local = mx - novox;
        float my_local = my - novoy;
        
        int intersecoes = 0;
        int n = vertices.size();
        
        for (int i = 0; i < n; ++i) {
            Vertice p1 = vertices[i];
            Vertice p2 = vertices[(i + 1) % n];
            
            // Ignorar arestas horizontais
            if (p1.y == p2.y && p1.y == my_local) {
                continue;
            }
            
            bool cruzou = false;
            
            // Intersecção exata sobre vértices: conta apenas se o outro vértice estiver acima
            if (p1.y == my_local) {
                if (p2.y > my_local && p1.x > mx_local) {
                    cruzou = true;
                }
            } else if (p2.y == my_local) {
                if (p1.y > my_local && p2.x > mx_local) {
                    cruzou = true;
                }
            } else if ((p1.y < my_local && p2.y > my_local) || (p1.y > my_local && p2.y < my_local)) {
                // Caso não trivial: calcula a abscissa (x) da interseção
                float xi = p1.x + (my_local - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                if (xi > mx_local) {
                    cruzou = true;
                }
            }
            
            if (cruzou) {
                intersecoes++;
            }
        }
        
        selecionada = (intersecoes % 2 != 0);
        return selecionada;
    }
};

#endif
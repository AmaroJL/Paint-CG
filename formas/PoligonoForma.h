#ifndef POLIGONOFORMA_H
#define POLIGONOFORMA_H

#include "Forma.h"
#include <GL/glut.h>
#include <vector>

class PoligonoForma : public Forma {
public:
    struct Vertice { float x, y; };
    std::vector<Vertice> vertices;

private:
    //orientacao de (p, q, r)
    // 0-mesma linha, 1-horario , 2-antihorario
    int orientacao(Vertice p, Vertice q, Vertice r) {
        float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0.0f) return 0;
        return (val > 0.0f) ? 1 : 2;
    }

public:
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
        
        // Se estiver selecionado, usa cor laranja, senão usa verde
        if (selecionada) {
            glColor3f(1.0f, 0.5f, 0.0f);
        } else {
            glColor3f(0.2f, 0.8f, 0.2f); 
        }
        
        // Preenche o interior do polígono
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

    void aplicarTransformacao(float m[3][3]) override {
        for (auto& v : vertices) {
            float nx = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * 1.0f;
            float ny = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * 1.0f;
            v.x = nx;
            v.y = ny;
        }
    }

    void obterCentro(float &cx, float &cy) override {
        if (vertices.empty()) { cx = 0; cy = 0; return; }
        cx = 0; cy = 0;
        for (auto& v : vertices) {
            cx += v.x;
            cy += v.y;
        }
        cx /= vertices.size();
        cy /= vertices.size();
    }

    //marcha de jarvis
    void transformarEmConvexo() {
        int n = vertices.size();
        if (n < 3) return;

        std::vector<Vertice> fecho;

        //pega o vertice mais a esquerda
        int l = 0;
        for (int i = 1; i < n; i++) {
            if (vertices[i].x < vertices[l].x) {
                l = i;
            }
        }

        //começa a marcha -> termina voltando pro ponto inicial
        int p = l, q;
        do {
            // add o ponto atual ao fecho convexo
            fecho.push_back(vertices[p]);

            // pega o prox 'q' tal que (p, i, q) seja anti-horaria para todo 'i'
            q = (p + 1) % n;
            for (int i = 0; i < n; i++) {
                if (orientacao(vertices[p], vertices[i], vertices[q]) == 2) {
                    q = i;
                }
            }

            p = q;
        } while (p != l);

        //substitui os verticies concavos pelo convexo
        vertices = fecho;
    }
};

#endif
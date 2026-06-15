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
    }

    bool clicado(float mx, float my, float tol) override {
        // Vértices do retângulo de tolerância
        float xmin = mx - tol;
        float xmax = mx + tol;
        float ymin = my - tol;
        float ymax = my + tol;

        // Recebem as posições dos pontos da reta (inicial e final) em relação ao retângulo de tolerância
        int cod1 = calcularCodigoDeRegiao(x1, y1, xmin, xmax, ymin, ymax);
        int cod2 = calcularCodigoDeRegiao(x2, y2, xmin, xmax, ymin, ymax);

        bool aceito = false;
        
        // Criação de cópias das duas pontas da reta
        float px1 = x1, py1 = y1, px2 = x2, py2 = y2;

        while (true) {
            if ((cod1 == 0) && (cod2 == 0)) {
                // A reta esta totalmente dentro do retângulo de tolerância
                aceito = true;
                break;
            } else if (cod1 & cod2) {
                // A reta está totalmente fora do retângulo de tolerância
                break;
            } else {
                // A reta cruza pelo menos uma borda do retângulo de tolerância
                int codFora = (cod1 != 0) ? cod1 : cod2;
                float x_interseccao = 0.0f, y_interseccao = 0.0f;

                // Usa as fórmulas matemáticas da equação da reta para encontrar o ponto de intersecção
                if (codFora & CIMA) {
                    x_interseccao = px1 + (px2 - px1) * (ymax - py1) / (py2 - py1);
                    y_interseccao = ymax;
                } else if (codFora & BAIXO) {
                    x_interseccao = px1 + (px2 - px1) * (ymin - py1) / (py2 - py1);
                    y_interseccao = ymin;
                } else if (codFora & DIREITA) {
                    y_interseccao = py1 + (py2 - py1) * (xmax - px1) / (px2 - px1);
                    x_interseccao = xmax;
                } else if (codFora & ESQUERDA) {
                    y_interseccao = py1 + (py2 - py1) * (xmin - px1) / (px2 - px1);
                    x_interseccao = xmin;
                }

                // Substitui o ponto que estava fora pelo novo ponto de intersecção que acabámos de calcular
                if (codFora == cod1) {
                    px1 = x_interseccao;
                    py1 = y_interseccao;
                    cod1 = calcularCodigoDeRegiao(px1, py1, xmin, xmax, ymin, ymax);
                } else {
                    px2 = x_interseccao;
                    py2 = y_interseccao;
                    cod2 = calcularCodigoDeRegiao(px2, py2, xmin, xmax, ymin, ymax);
                }
            }
        }
        
        return aceito;
    }
};

#endif
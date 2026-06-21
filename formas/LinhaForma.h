#ifndef LINHAFORMA_H
#define LINHAFORMA_H

#include "Forma.h"
#include <GL/glut.h>
#include <cmath>
#include <sstream>

class LinhaForma : public Forma {
private:
    static const int DENTRO = 0;   
    static const int ESQUERDA = 1; 
    static const int DIREITA = 2;  
    static const int BAIXO = 4;    
    static const int CIMA = 8;     

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
        glPushMatrix(); 
        glTranslatef(novox, novoy, 0.0f); 

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
            glVertex2f(x1, y1); 
            if (x1 != x2 || y1 != y2) {
                glVertex2f(x2, y2); 
            }
        glEnd();

        glPopMatrix(); 
    }

    bool clicado(float mx, float my, float tol) override {
        return false;
    }

    std::string exportar() override {
        std::stringstream ss;
        ss << "LINHA " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << novox << " " << novoy;
        return ss.str();
    }
};

#endif
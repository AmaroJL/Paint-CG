#ifndef BOTAO_H
#define BOTAO_H

#include <GL/glut.h>
#include <string>
#include "ferramentas/Ferramenta.h"

extern Ferramenta* ferramentaAtiva;

class Botao {
public:
    float x, y, largura, altura;
    std::string texto;
    Ferramenta* ferramenta;
    
    Botao(float x, float y, float w, float h, std::string texto, Ferramenta* ferramenta);
    void desenhar();
    bool clicado(float mundoX, float mundoY);
    void realizar_acao();
};

#endif
#ifndef BOTAO_H
#define BOTAO_H

#include <GL/glut.h>
#include <string>
#include "Ferramenta.h"

extern Ferramenta* ferramentaAtiva;

class Botao {
public:
    float x, y, largura, altura;
    std::string texto;
    Ferramenta* ferramenta;

    bool ehBotaoAcao;
    bool visivel;
    
    Botao(float x, float y, float w, float h, std::string texto, Ferramenta* ferramenta, bool ehAcao = false);
    void desenhar();
    bool clicado(float mundoX, float mundoY);
    void realizar_acao();
};

#endif
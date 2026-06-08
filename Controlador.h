#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <vector>
#include "Botao.h"
#include "Forma.h"

class Controlador {
private:
    std::vector<Botao>& botoes;
    std::vector<Forma*>& desenhos;
    Ferramenta*& ferramentaAtiva;
    bool& desenhando;

public:
    Controlador(std::vector<Botao>& b, std::vector<Forma*>& d, Ferramenta*& f, bool& des);

    bool processarCliqueBotao(float mundoX, float mundoY);
    void processarDesenho(float mundoX, float mundoY);
    void processarMouse(int button, int state, float mundoX, float mundoY);
    void processarMotion(float mundoX, float mundoY);
};

#endif
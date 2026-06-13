#ifndef FERRAMENTASELECAO_H
#define FERRAMENTASELECAO_H

#include "Ferramenta.h"
#include <vector>

extern std::vector<Forma*> desenhosNaTela;

class FerramentaSelecao : public Ferramenta {
public:
    Forma* usar_ferramenta(float mx, float my) override {
        float tolerancia = 3.0f; 

        // Deseleciona todo mundo 
        for (Forma* f : desenhosNaTela) {
            f->selecionada = false;
        }

        // Varre o vetor de trás para frente, selecionando o desenho que está mais acima
        for (int i = desenhosNaTela.size() - 1; i >= 0; i--) {
            if (desenhosNaTela[i]->clicado(mx, my, tolerancia)) {
                desenhosNaTela[i]->selecionada = true;
                break; 
            }
        }
        
        return nullptr; 
    }
};

#endif
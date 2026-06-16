#ifndef FERRAMENTASELECAO_H
#define FERRAMENTASELECAO_H

#include "Ferramenta.h"
#include <vector>

extern std::vector<Forma*> desenhosNaTela;

class FerramentaSelecao : public Ferramenta {
private:
    Forma* formaArrastada = nullptr;
    float ultimoX, ultimoY;

public:
    Forma* usar_ferramenta(float mx, float my) override {
        float tolerancia = 3.0f; 
        formaArrastada = nullptr;

        // Deseleciona todo mundo 
        for (Forma* f : desenhosNaTela) {
            f->selecionada = false;
        }

        // Varre o vetor de trás para frente, selecionando o desenho que está mais acima
        for (int i = desenhosNaTela.size() - 1; i >= 0; i--) {
            if (desenhosNaTela[i]->clicado(mx, my, tolerancia)) {
                desenhosNaTela[i]->selecionada = true;
                formaArrastada = desenhosNaTela[i]; // Agarra na hora que seleciona
                ultimoX = mx;
                ultimoY = my;
                break; 
            }
        }
        
        return nullptr; 
    }

    void arrastar(float mx, float my) override {
        if (formaArrastada != nullptr) {
            // Calcula quanto o mouse se moveu
            formaArrastada->novox += (mx - ultimoX);
            formaArrastada->novoy += (my - ultimoY);
            
            // Atualiza a memória
            ultimoX = mx;
            ultimoY = my;
        }
    }

    void soltar() override {
        formaArrastada = nullptr;
    }
    
};

#endif
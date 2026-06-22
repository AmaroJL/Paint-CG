#ifndef FERRAMENTAPOLIGONO_H
#define FERRAMENTAPOLIGONO_H

#include "Ferramenta.h"
#include "../formas/PoligonoForma.h"

class FerramentaPoligono : public Ferramenta {
private:
    PoligonoForma* poligonoAtual = nullptr;

public:
    Forma* usar_ferramenta(float x, float y) override {
        if (poligonoAtual == nullptr) {
            poligonoAtual = new PoligonoForma(x, y);
            return poligonoAtual;
        } else {
            poligonoAtual->addVertice(x, y);
            return nullptr; 
        }
    }
    
    // Solta o polígono atual para permitir iniciar o próximo
    void finalizar_acao() override {
        poligonoAtual = nullptr; 
    }
};

#endif
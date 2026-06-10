#ifndef FERRAMENTAPOLIGONO_H
#define FERRAMENTAPOLIGONO_H

#include "Ferramenta.h"
#include "PoligonoForma.h"

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
    
    void finalizar_acao() override {
        poligonoAtual = nullptr; // Solta o polígono atual para permitir iniciar o próximo
    }
};

#endif
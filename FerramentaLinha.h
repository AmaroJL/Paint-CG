#ifndef FERRAMENTALINHA_H
#define FERRAMENTALINHA_H

#include "Ferramenta.h"
#include "LinhaForma.h"

class FerramentaLinha : public Ferramenta {
private:
    LinhaForma* linhaAtual = nullptr;

public:
    Forma* usar_ferramenta(float x, float y) override {
        if (linhaAtual == nullptr) {
            linhaAtual = new LinhaForma(x, y);
            return linhaAtual; 
        } else {
            linhaAtual->setFim(x, y);
            linhaAtual = nullptr; 
            return nullptr; 
        }
    }
};

#endif
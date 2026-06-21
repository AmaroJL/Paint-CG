#ifndef FERRAMENTAPONTO_H
#define FERRAMENTAPONTO_H

#include "Ferramenta.h"
#include "../formas/PontoForma.h"

class FerramentaPonto : public Ferramenta {
public:
    Forma* usar_ferramenta(float x, float y) override {
        return new PontoForma(x, y);
    }
    
    bool ehContinua() override { 
        return false; 
    }
};

#endif
#ifndef FERRAMENTAPINCEL_H
#define FERRAMENTAPINCEL_H

#include "Ferramenta.h"
#include "../formas/PontoForma.h"

class FerramentaPincel : public Ferramenta {
public:
    Forma* usar_ferramenta(float x, float y) override {
        return new PontoForma(x, y);
    }
    
    // O pincel avisa que ele permite arrastar
    bool ehContinua() override { 
        return true; 
    }
};

#endif
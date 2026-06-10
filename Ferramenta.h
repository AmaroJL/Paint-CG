#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "Forma.h"

class Ferramenta {
public:
    virtual Forma* usar_ferramenta(float x, float y) = 0;
    
    virtual bool ehContinua() { 
        return false; 
    }
    virtual void finalizar_acao() {}
    
    virtual ~Ferramenta() {}
};

#endif
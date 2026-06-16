#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "../formas/Forma.h"

class Ferramenta {
public:
    virtual Forma* usar_ferramenta(float x, float y) = 0;
    
    virtual bool ehContinua() { 
        return false; 
    }
    virtual void finalizar_acao() {}

    virtual void arrastar(float mx, float my) {}
    virtual void soltar() {}
    
    virtual ~Ferramenta() {}
};

#endif
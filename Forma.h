#ifndef FORMA_H
#define FORMA_H

class Forma {
public:
    virtual void desenhar() = 0;

    bool selecionada = false;

    virtual bool clicado(float mx, float my, float tolerancia) = 0; 

    virtual ~Forma() {}
};

#endif
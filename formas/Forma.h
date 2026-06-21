#ifndef FORMA_H
#define FORMA_H

class Forma {
public:
    virtual void desenhar() = 0;

    bool selecionada = false;

    float novox = 0.0f;
    float novoy = 0.0f;

    virtual bool clicado(float mx, float my, float tolerancia) = 0; 

    virtual ~Forma() {} 

    virtual void aplicarTransformacao(float m[3][3]) = 0;
    virtual void obterCentro(float &cx, float &cy) = 0;
};

#endif
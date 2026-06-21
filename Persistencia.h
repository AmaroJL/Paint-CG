#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <vector>
#include <string>
#include <sstream>
#include "formas/Forma.h"

class Persistencia {
private:
    static Forma* lerPonto(std::stringstream& leitorDeLinha);
    static Forma* lerLinha(std::stringstream& leitorDeLinha);
    static Forma* lerPoligono(std::stringstream& leitorDeLinha);

public:
    static void salvar(const std::vector<Forma*>& desenhos, const std::string& caminho);
    static void carregar(std::vector<Forma*>& desenhos, const std::string& caminho);
};

#endif
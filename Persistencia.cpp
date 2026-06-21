#include "Persistencia.h"
#include "formas/PontoForma.h"
#include "formas/LinhaForma.h"
#include "formas/PoligonoForma.h"
#include <fstream>
#include <iostream>

Forma* Persistencia::lerPonto(std::stringstream& leitorDeLinha) {
    float x, y, translacaoX, translacaoY;
    leitorDeLinha >> x >> y >> translacaoX >> translacaoY;
    
    PontoForma* ponto = new PontoForma(x, y);
    ponto->novox = translacaoX;
    ponto->novoy = translacaoY;
    
    return ponto;
}

Forma* Persistencia::lerLinha(std::stringstream& leitorDeLinha) {
    float x1, y1, x2, y2, translacaoX, translacaoY;
    leitorDeLinha >> x1 >> y1 >> x2 >> y2 >> translacaoX >> translacaoY;
    
    LinhaForma* linha = new LinhaForma(x1, y1);
    linha->setFim(x2, y2);
    linha->novox = translacaoX;
    linha->novoy = translacaoY;
    
    return linha;
}

Forma* Persistencia::lerPoligono(std::stringstream& leitorDeLinha) {
    float translacaoX, translacaoY;
    int quantidadeVertices;
    
    leitorDeLinha >> translacaoX >> translacaoY >> quantidadeVertices;
    
    if (quantidadeVertices <= 0) return nullptr;

    float pontoX, pontoY;
    leitorDeLinha >> pontoX >> pontoY;
    PoligonoForma* poligono = new PoligonoForma(pontoX, pontoY);
    
    for (int i = 1; i < quantidadeVertices; ++i) {
        leitorDeLinha >> pontoX >> pontoY;
        poligono->addVertice(pontoX, pontoY);
    }
    
    poligono->novox = translacaoX;
    poligono->novoy = translacaoY;
    
    return poligono;
}

void Persistencia::salvar(const std::vector<Forma*>& desenhos, const std::string& caminho) {
    std::ofstream arquivo(caminho);
    if (!arquivo.is_open()) return;

    for (Forma* f : desenhos) {
        arquivo << f->exportar() << "\n";
    }
    arquivo.close();
    std::cout << "Desenho salvo com sucesso!\n";
}

void Persistencia::carregar(std::vector<Forma*>& desenhos, const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cout << "Arquivo nao encontrado!\n";
        return;
    }

    for (Forma* f : desenhos) {
        delete f;
    }
    desenhos.clear();

    std::string linhaAtual;
    while (std::getline(arquivo, linhaAtual)) {
        if (linhaAtual.empty()) continue;
        
        std::stringstream leitorDeLinha(linhaAtual);
        
        std::string tipoDaForma;
        leitorDeLinha >> tipoDaForma;

        Forma* novaForma = nullptr;

        if (tipoDaForma == "PONTO") {
            novaForma = lerPonto(leitorDeLinha);
        } 
        else if (tipoDaForma == "LINHA") {
            novaForma = lerLinha(leitorDeLinha);
        }
        else if (tipoDaForma == "POLIGONO") {
            novaForma = lerPoligono(leitorDeLinha);
        }

        if (novaForma != nullptr) {
            desenhos.push_back(novaForma);
        }
    }
    arquivo.close();
    std::cout << "Desenho carregado com sucesso!\n";
}
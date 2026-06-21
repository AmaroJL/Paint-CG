#include "Controlador.h"
#include <GL/glut.h>

Controlador::Controlador(std::vector<Botao>& b, std::vector<Forma*>& d, Ferramenta*& f, bool& des) 
    : botoes(b), desenhos(d), ferramentaAtiva(f), desenhando(des) {}

bool Controlador::processarCliqueBotao(float mundoX, float mundoY) {
    for (Botao& b : botoes) {
        if (b.clicado(mundoX, mundoY)) {
            if (ferramentaAtiva != nullptr) {
                ferramentaAtiva->finalizar_acao();
            }

            for (Forma* f : desenhos) {
                f->selecionada = false;
            }

            b.realizar_acao();
            return true;
        }
    }
    return false;
}

void Controlador::processarDesenho(float mundoX, float mundoY) {
    if (mundoY > 130.0f) {
        desenhando = false;
        return;
    }
    
    if (ferramentaAtiva != nullptr) {
        desenhando = true;
        Forma* novaForma = ferramentaAtiva->usar_ferramenta(mundoX, mundoY);
        if (novaForma != nullptr) { 
            desenhos.push_back(novaForma);
        }
    } else {
        desenhando = false;
    }
}

void Controlador::processarMouse(int button, int state, float mundoX, float mundoY) {
    if (button != GLUT_LEFT_BUTTON) return;

    if (state == GLUT_DOWN) {
        if (processarCliqueBotao(mundoX, mundoY)) return; 
        processarDesenho(mundoX, mundoY);
    } 
    else if (state == GLUT_UP) {
        desenhando = false;
        if (ferramentaAtiva != nullptr) {
            ferramentaAtiva->soltar();
        }
    }
}

void Controlador::processarMotion(float mundoX, float mundoY) {
    if (mundoY > 130.0f) return;

    if (ferramentaAtiva != nullptr) {
        ferramentaAtiva->arrastar(mundoX, mundoY); // Repassa o movimeto do mouse para a ferramenta arrastar

        if (desenhando && ferramentaAtiva->ehContinua()) {
                Forma* novaForma = ferramentaAtiva->usar_ferramenta(mundoX, mundoY);
                desenhos.push_back(novaForma);
            }
    }
    
    
}
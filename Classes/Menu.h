
#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include "Estudante.h"
#include "Gestao.h"

class Menu {
public:
    Menu();
    void init();

    void show_uc(std::vector<Turma*> uc, int ordem);
    void show_ano(char ano, int ordem);
    void show_estudantes_mais_que_n_ucs(int n, int ordem);
    void show_pedidos();

    std::string validar_codigo_uc();
    std::string validar_codigo_turma(std::string cod_uc);
    std::string validar_numero_estudante(std::string mensagem);
    char validar_numero(std::string mensagem);
private:
    Gestao* g;
    void ver_estatisticas();
    void ver_conteudos();
    void ver_horarios();
    void ver_estudantes(int ordem);
    void ver_pedidos();
    void fazer_pedido();
    void fim();
};


#endif //PROJ_MENU_H

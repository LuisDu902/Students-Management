//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include "Estudante.h"
#include "Gestao.h"

class Menu {
public:
    Menu();
    void init();

    void show_uc(std::vector<Turma*> uc);
    void show_ano(std::string ano, std::set<Estudante *, Turma::cmp_nome> estudantes);
    void show_estudantes_mais_que_n_ucs(int n,std::set<Estudante *, Turma::cmp_nome> estudantes, std::string modo_de_ordenacao);
private:
    Gestao* g;
    void ver_estatisticas();
    void ver_conteudos();
    void fazer_pedido();
    void fim();
};


#endif //PROJ_MENU_H

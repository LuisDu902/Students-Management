//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_PEDIDO_H
#define PROJ_PEDIDO_H

#include "Estudante.h"

class Pedido {
public:
// construtores
    Pedido(std::string tipo, Turma* turma, Estudante* estudante1, Estudante* estudante2 = nullptr);

    static bool cmp(Pedido* pedido1, Pedido* pedido2);

    std::string get_tipo();
    Estudante* get_estudante1();
    Estudante* get_estudante2();
    Turma* get_turma();

private:
    Estudante* estudante1;
    Estudante* estudante2;
    Turma* turma1;
    std::string tipo;
};
#endif
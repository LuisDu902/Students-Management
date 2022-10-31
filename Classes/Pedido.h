//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_PEDIDO_H
#define PROJ_PEDIDO_H

#include "Estudante.h"

class Pedido {
public:
// construtores
    Pedido(Turma* turma, Estudante* estudante1, Estudante* estudante2 = nullptr);

private:
    Estudante* estudante1;
    Estudante* estudante2;
    Turma* turma1;
    std::string tipo;
};
#endif
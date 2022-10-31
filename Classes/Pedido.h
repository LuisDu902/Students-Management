//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_PEDIDO_H
#define PROJ_PEDIDO_H

#include "Estudante.h"

class Pedido {
public:
// construtores
    Pedido(Estudante* estudante1,Turma* turma1);
    Pedido(Estudante* estudante1,Estudante* estudante2,Turma* turma1);



private:
    Estudante* estudante1;
    Estudante* estudante2 = nullptr;
    Turma* turma1;
};


#endif //PROJ_PEDIDO_H

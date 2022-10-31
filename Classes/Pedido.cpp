//
// Created by athos on 31/10/2022.
//

#include "Pedido.h"

Pedido::Pedido(Turma* turma, Estudante* estudante1, Estudante* estudante2){
    this->estudante1 = estudante1;
    this->estudante2 = estudante2;
    this->turma1 = turma;
}

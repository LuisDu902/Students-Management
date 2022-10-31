//
// Created by athos on 31/10/2022.
//

#include "Pedido.h"

Pedido::Pedido(Estudante* estudante1,Turma* turma1){
    this->estudante1 = estudante1;
    this->turma1 = turma1;
}

Pedido::Pedido(Estudante* estudante1,Estudante* estudante2,Turma* turma1){
    this->estudante1 = estudante1;
    this->estudante2 = estudante2;
    this->turma1 = turma1;
}


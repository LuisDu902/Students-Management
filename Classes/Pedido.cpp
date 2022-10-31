//
// Created by athos on 31/10/2022.
//

#include "Pedido.h"

Pedido::Pedido(std::string tipo, Turma* turma, Estudante* estudante1, Estudante* estudante2){
    this->estudante1 = estudante1;
    this->estudante2 = estudante2;
    this->turma1 = turma;
    this->tipo = tipo;
}

std::string Pedido::get_tipo() {return tipo; }
Estudante* Pedido::get_estudante1() {return estudante1; }
Estudante* Pedido::get_estudante2() {return estudante2; }
Turma* Pedido::get_turma() {return turma1; }

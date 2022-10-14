//
// Created by athos on 13/10/2022.
//

#include "Turma.h"


Turma::Turma(std::string codigo, Horario horario){
    this->codigo = codigo;
    this->horario = horario;
}

std::string Turma::getCodigo(){
    return codigo;
}

Horario Turma::getHorario(){
    return horario;
}

void Turma::setCodigo(std::string codigo){
    this->codigo = codigo;
}

void Turma::setHorario(Horario horario){
    this->horario = horario;
}

int Turma::get_ano(){
    return int(this->codigo[0]);
}
int Turma::get_turma(){
    return (int(this->codigo[5])-48)*10 + int(this->codigo[6])-48;
}
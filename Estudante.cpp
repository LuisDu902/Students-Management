//
// Created by Sofia Pinto on 13/10/2022.
//

#include "Estudante.h"

Estudante::Estudante(std::string nome, int numero, Horario &horario) {
    this->nome = nome;
    this-> numero = numero;
    *this->horario = horario;
}

void Estudante::set_horario(Horario &horario) {
    *this->horario = horario;
}

std::string Estudante::get_nome(){return this->nome;}
int Estudante::get_numero(){return this->numero;}
Horario* Estudante::get_horario(){return this->horario;}
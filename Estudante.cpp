//
// Created by Sofia Pinto on 13/10/2022.
//

#include "Estudante.h"

Estudante::Estudante(std::string codigo, std::string nome) {
    this->codigo = codigo;
    this-> nome = nome;
}
void Estudante::adicionar_turma(Turma turma){

    for (auto a: turmas){
        if (a.get_codigo_uc() == turma.get_codigo_uc() && a.get_codigo_turma() == turma.get_codigo_turma()) {
            return;
        }
    }
    turmas.push_back(turma);
}

std::string Estudante::get_codigo(){return codigo;}

void Estudante::show(){
    std::cout << nome << " está nas turmas: \n";
    for (auto turma: turmas){
        std::cout << "\t";
        turma.show();
    }
    std::cout << "-------------" << std::endl;
}
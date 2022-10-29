//
// Created by athos on 13/10/2022.
//

#include "Turma.h"


Turma::Turma(std::string codigo_uc,std::string codigo_turma){
    this->codigo_turma = codigo_turma;
    this->codigo_uc = codigo_uc;
    capacidade_atual = 0;
}

int Turma::get_capacidade_atual(){return capacidade_atual;}

void Turma::show() {
    std::cout << codigo_uc << " | " << codigo_turma << " | nº_alunos: " << capacidade_atual << std::endl;
}

void Turma::add_capacidade() {
    capacidade_atual++;
}
void Turma::sub_capacidade() {
    capacidade_atual--;
}
std::string Turma::get_codigo_uc() const {return codigo_uc;}
std::string Turma::get_codigo_turma() const {return codigo_turma;}
std::vector<Aula*> Turma::get_aulas() const{return aulas;}
void Turma::adicionar_aula(Aula* aula){
    aulas.push_back(aula);
}

void Turma::show_horario_turma(){
    for (auto aula: aulas){
        aula->show_horario_turma();
    }
}

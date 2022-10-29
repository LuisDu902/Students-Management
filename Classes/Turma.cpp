//
// Created by athos on 13/10/2022.
//

#include "Turma.h"

//construtor
Turma::Turma(std::string codigo_uc,std::string codigo_turma){
    this->codigo_turma = codigo_turma;
    this->codigo_uc = codigo_uc;
    capacidade_atual = 0;
}

//getters
std::string Turma::get_codigo_uc() const {return codigo_uc;}
std::string Turma::get_codigo_turma() const {return codigo_turma;}
std::vector<Aula*> Turma::get_aulas() const{return aulas;}
int Turma::get_capacidade_atual() const{return capacidade_atual;}

//operators
void Turma::set_capacidade(int capacidade) {capacidade_atual=capacidade;}
void Turma::adicionar_aula(Aula* aula){aulas.push_back(aula);}

//show
void Turma::show() {
    std::cout << codigo_uc << " | " << codigo_turma << " | nº_alunos: " << capacidade_atual << std::endl;
}

void Turma::show_horario_turma(){
    for (auto aula: aulas){
        aula->show_horario_turma();
    }
}




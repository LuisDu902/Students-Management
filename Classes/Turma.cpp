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
std::set<Estudante*,Turma::cmp_nome> Turma::get_estudantes() const{return estudantes;}
int Turma::get_capacidade_atual() const{return capacidade_atual;}

//operators
void Turma::set_capacidade(int capacidade) {capacidade_atual=capacidade;}
void Turma::adicionar_aula(Aula* aula){aulas.push_back(aula);}
void Turma::adicionar_estudante(Estudante* estudante){estudantes.insert(estudante);}
void Turma::remover_estudante(Estudante* estudante){estudantes.erase(estudantes.find(estudante));}

//compare
bool Turma::cmp_nome::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_nome() < rhs->get_nome();}
bool Turma::cmp_codigo::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_codigo() < rhs->get_codigo();}
bool Turma::cmp_nr_uc::operator()(const Estudante* lhs, const Estudante* rhs) const  {
    if (lhs->get_turmas().size() != rhs->get_turmas().size()) return lhs->get_turmas().size() < rhs->get_turmas().size();
    return lhs->get_nome() < rhs->get_nome();}

//show
void Turma::show() {
    std::cout << codigo_uc << " | " << codigo_turma << " | numero de alunos: " << capacidade_atual << std::endl;
}
void Turma::show_estudantes(){
    for (auto estudante: estudantes){
        std::cout << estudante->get_nome() << std::endl;
    }
}
void Turma::show_horario_turma(){

    sort(aulas.begin(),aulas.end(),Aula::cmp);
    for (auto aula: aulas){
        aula->show_horario_turma();
    }
}




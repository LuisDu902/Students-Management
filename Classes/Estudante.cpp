//
// Created by Sofia Pinto on 13/10/2022.
//

#include "Estudante.h"

//construtor
Estudante::Estudante(std::string codigo, std::string nome) {
    this->codigo = codigo;
    this-> nome = nome;
}

//getters
std::string Estudante::get_nome() const{return nome;}
std::string Estudante::get_codigo() const {return codigo;}
std::vector<Turma *> Estudante::get_turmas() const{return turmas;}

//operators
void Estudante::adicionar_turma(Turma* turma){

    for (auto a: turmas){
        if (a->get_codigo_uc() == turma->get_codigo_uc() && a->get_codigo_turma() == turma->get_codigo_turma()) {
            return;
        }
    }
    turma->set_capacidade(turma->get_capacidade_atual()+1);
    turmas.push_back(turma);
}

void Estudante::remover_da_turma(Turma* turma){

    for (auto it = turmas.begin();it != turmas.end();it++){
        if ((*it)->get_codigo_turma() == turma->get_codigo_turma() && (*it)->get_codigo_uc() == turma->get_codigo_uc()){
            turmas.erase(it);
            turma->set_capacidade(turma->get_capacidade_atual()-1);
            return;
        }
    }
}


std::set<Aula*,Aula::APtrComp> Estudante::horario(){
    std::set<Aula*,Aula::APtrComp> a;
    for (auto turma: turmas){
        for (auto aula : turma->get_aulas()){
            a.insert(aula);
        }
    }
    return a;
}

//compare
bool Estudante::cmp::operator()(const Estudante* lhs, const Estudante* rhs) const  {

    return lhs->nome < rhs->nome;
}

//show
void Estudante::show_horario(){
    std::set<Aula*,Aula::APtrComp> horario = Estudante::horario();
    for (auto x: horario){
        x->show_horario_turma();
    }
}

void Estudante::show_turmas(){
    std::cout << nome << " está nas turmas: \n";
    for (auto turma: turmas){
        std::cout << "\t";
        turma->show();
    }
    std::cout << "-------------" << std::endl;
}
//
// Created by Sofia Pinto on 13/10/2022.
//

#include "Estudante.h"
#include "Aula.h"
Estudante::Estudante(std::string codigo, std::string nome) {
    this->codigo = codigo;
    this-> nome = nome;
}
void Estudante::adicionar_turma(Turma* turma){

    for (auto a: turmas){
        if (a->get_codigo_uc() == turma->get_codigo_uc() && a->get_codigo_turma() == turma->get_codigo_turma()) {
            return;
        }
    }
    turma->add_capacidade();
    turmas.push_back(turma);
}

std::string Estudante::get_codigo(){return codigo;}

void Estudante::show(){
    std::cout << nome << " está nas turmas: \n";
    for (auto turma: turmas){
        std::cout << "\t";
        turma->show();
    }
    std::cout << "-------------" << std::endl;
}

void Estudante::remover_da_turma(Turma* turma){

    for (auto it = turmas.begin();it != turmas.end();it++){
        if ((*it)->get_codigo_turma() == turma->get_codigo_turma() && (*it)->get_codigo_uc() == turma->get_codigo_uc()){
            turmas.erase(it);
            turma->sub_capacidade();
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

std::vector<Turma *> Estudante::get_turmas() const{
    return turmas;
}

void Estudante::show_horario(){
    std::set<Aula*,Aula::APtrComp> horario = Estudante::horario();
    for (auto x: horario){
        x->show_horario_turma();
    }
}

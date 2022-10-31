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


void Estudante::remover_da_turma(Turma* turma){

    for (auto it = turmas.begin();it != turmas.end();it++){
        if ((*it)->get_codigo_turma() == turma->get_codigo_turma() && (*it)->get_codigo_uc() == turma->get_codigo_uc()){
            turmas.erase(it);
            (*it)->remover_estudante(this);
            turma->set_capacidade(turma->get_capacidade_atual()-1);
            return;
        }
    }
}


std::vector<Aula*> Estudante::horario(){
    std::vector<Aula*> a;
    for (auto turma: turmas){
        for (auto aula : turma->get_aulas()){
            a.push_back(aula);
        }
    }
    return a;
}
bool Estudante::compativel(Turma* turma){
    std::vector<Aula*> h = horario();
    for (auto aula_turma : turma->get_aulas()){
        for (auto aula_estudante: h){
            if (aula_turma->overload(aula_estudante)) return false;
        }
    }
    return true;
}
void Estudante::adicionar_turma(Turma* turma){
    if (!compativel(turma)) return;
    for (auto a: turmas){
        if (a->get_codigo_uc() == turma->get_codigo_uc() && a->get_codigo_turma() == turma->get_codigo_turma()) {
            return;
        }
    }
    turma->set_capacidade(turma->get_capacidade_atual()+1);
    turma->adicionar_estudante(this);
    turmas.push_back(turma);
}
void Estudante::alterar_turma(Turma* turma){
    turmas.push_back(turma);
    for (auto t=turmas.begin();t!=turmas.end();t++){
        if ((*t)->get_codigo_uc() == turma->get_codigo_uc()){
            turmas.erase(t);
        }
    }
}


void Estudante::trocar_turma_com_estudante(Turma *turma, Estudante *estudante_troca) {

}


//show
void Estudante::show(){
    std::cout << nome << " - up" << codigo;
}

void Estudante::show_horario(){
    std::vector<Aula*> horario = Estudante::horario();
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
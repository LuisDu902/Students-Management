//
// Created by Sofia Pinto on 13/10/2022.
//

#include "Estudante.h"

//construtor
/**
 * Construtor da classe Estudante(), recebe o código e o nome de um estudante (sendo o vetor de aulas corresponde inicialmente a um vetor vazio)
 * @param codigo
 * @param nome
 */
Estudante::Estudante(std::string codigo, std::string nome) {
    this->codigo = codigo;
    this-> nome = nome;
}

Estudante::Estudante(std::string codigo) {
    this->codigo = codigo;
}
//getters
/**
 * Retorna o nome do estudante
 * @return
 */
std::string Estudante::get_nome() const{return nome;}
/**
 * Retorna o codigo do estudante
 * @return
 */
std::string Estudante::get_codigo() const {return codigo;}
/**
 * Retorna o vetor de todas as turmas do estudante
 * @return
 */
std::vector<Turma *> Estudante::get_turmas() const{return turmas;}

//operators

/**
 * Remove o estudante da turma, retirando a turma do vetor de turmas do estudantes, e decrementando a capacidade atual da turma
 * @param turma
 */
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

/**
 * Retorna o horário do estudante, isto é, uma BST de todas as aulas do estudante
 * @return
 */
std::vector<Aula*> Estudante::horario(){
    std::vector<Aula*> a;
    for (auto turma: turmas){
        for (auto aula : turma->get_aulas()){
            a.push_back(aula);
        }
    }
    return a;
}
/**
 * Verifica se o horário da turma é compatível com o horário do estudante
 * @param turma
 * @return
 */
bool Estudante::compativel(Turma* turma){
    std::vector<Aula*> h = horario();
    for (auto aula_turma : turma->get_aulas()){
        for (auto aula_estudante: h){
            if (aula_turma->overload(aula_estudante)) {
                return false;
            }
        }
    }
    return true;
}
/**
 * Adicionar a turma no fim do vetor de turmas do estudante
 * @param turma
 */
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
/**
 * Remove o estudante da turma, adicionando a turma no fim do vetor de turma do estudante
 * @param turma
 */
void Estudante::alterar_turma(Turma* turma){
    turmas.push_back(turma);
    for (auto t=turmas.begin();t!=turmas.end();t++){
        if ((*t)->get_codigo_uc() == turma->get_codigo_uc()){
            turmas.erase(t);
        }
    }
}

/**
 * ???
 * @param turma
 * @param estudante_troca
 */
void Estudante::trocar_turma_com_estudante(Turma *turma, Estudante *estudante_troca) {
if (!estudante_troca->compativel(turma)) return;
    estudante_troca->get_turmas().push_back(turma);
    for (auto t=estudante_troca->get_turmas().begin();t!=estudante_troca->get_turmas().end();t++){
        if ((*t)->get_codigo_uc() == turma->get_codigo_uc()){
            if (!this->compativel(*t)) {
                estudante_troca->get_turmas().pop_back();
            }
            else {
                this->alterar_turma(*t);
                estudante_troca->get_turmas().erase(t);}}}}


//show
/**
 * Mostra o nome e o código do estudante
 */
void Estudante::show(int ordem){
    if (ordem == 2) std::cout << "up" << codigo << " - " << nome;
    else std::cout << nome << " - up" << codigo;
}
/**
 * Mostra o horário do estudante
 */
void Estudante::show_horario(){
    std::vector<Aula*> aulas = Estudante::horario();

    std::map<std::string,int> days = {
            std::pair<std::string,int> ("Monday",1),
            std::pair<std::string,int> ("Tuesday",2),
            std::pair<std::string,int> ("Wednesday",3),
            std::pair<std::string,int> ("Thursday",4),
            std::pair<std::string,int> ("Friday",5),
    };
    sort(aulas.begin(),aulas.end(),Aula::cmp);
    auto it = aulas.begin();
    int dia_atual = days[(*it)->get_dia_semana()];
    std::cout << (*it)->get_dia_semana() << ":\n";
    while (it != aulas.end()){
        if (days[(*it)->get_dia_semana()] == dia_atual){
            (*it)->show_horario_turma();
            it++;
        }
        else {
            dia_atual = days[(*it)->get_dia_semana()];
            std::cout << (*it)->get_dia_semana() << ":\n";
            (*it)->show_horario_turma();
            it++;
        }
    }
}
/**
 * Mostra todas as turmas do estudante
 */
void Estudante::show_turmas(){
    std::cout << nome << " está nas turmas: \n";
    for (auto turma: turmas){
        std::cout << "\t";
        turma->show();
    }
    std::cout << "-------------" << std::endl;
}
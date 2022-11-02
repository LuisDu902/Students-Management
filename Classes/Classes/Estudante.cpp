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
    turma->set_capacidade(turma->get_capacidade_atual()+1);
    turma->adicionar_estudante(this);
    turmas.push_back(turma);
}
/**
 * Remove o estudante da turma, adicionando a turma no fim do vetor de turma do estudante
 * @param turma
 */
void Estudante::alterar_turma(Turma* turma){
    for (auto t1: turmas){
        if ((t1)->get_codigo_uc() == turma->get_codigo_uc()){
            remover_da_turma(t1);
        }
    }
    adicionar_turma(turma);
}

/**
 * ???
 * @param turma
 * @param estudante_troca
 */
void Estudante::trocar_turma_com_estudante(Turma *turma1, Estudante *estudante_troca) {

    Turma* turma2;
    for (auto t: estudante_troca->get_turmas()){
        if (t->get_codigo_uc() == turma1->get_codigo_uc() && t != turma1){
            turma2 = t;
            break;
        }
    }

    remover_da_turma(turma1);
    estudante_troca->remover_da_turma(turma2);

    adicionar_turma(turma2);
    estudante_troca->adicionar_turma(turma1);}
//show
/**
 * Mostra o nome e o código do estudante
 */
void Estudante::show(int ordem) const{
    if (ordem == 2) std::cout << "up" << codigo << " - " << nome;
    else std::cout << nome << " - up" << codigo;
}
/**
 * Mostra o horário do estudante
 */
void Estudante::show_horario(){
    std::vector<Aula*> aulas = Estudante::horario();

    std::map<std::string,int> dias = Aula::dias;
    std::map<std::string,std::string> pt = Aula::pt;

    sort(aulas.begin(),aulas.end(),Aula::cmp);

    int dia_atual = 0;

    for (Aula* aula: aulas){
        if (dias[aula->get_dia_semana()] != dia_atual){
            dia_atual = dias[aula->get_dia_semana()];
            std::cout << pt[aula->get_dia_semana()] << ":\n";
        }
        aula->show();
        std::cout << '\n';
    }
}

/**
 * Mostra todas as turmas do estudante
 */
void Estudante::show_turmas() const{
    std::cout << nome << " está nas turmas: \n";
    for (auto turma: turmas){
        std::cout << "\t";
        turma->show();
    }
}

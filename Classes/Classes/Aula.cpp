//
// Created by du on 13-10-2022.
//

#include "Aula.h"

//construtor
/**
 * Construtor da classe Aula
 * @param codigo_turma
 * @param codigo_uc
 * @param dia_semana
 * @param hora_inicio
 * @param duracao
 * @param tipo
 */
Aula::Aula(std::string codigo_turma, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo){
    this->codigo_turma = codigo_turma;
    this->codigo_uc = codigo_uc;
    this->dia_semana = dia_semana;
    this->hora_inicio = hora_inicio;
    this->duracao = duracao;
    this->tipo = tipo;
}

//getters

/**
 * Retorna o código_turma da aula
 * @return
 */
std::string Aula::get_codigo_turma() const {return codigo_turma;}
/**
 * Obter o código_uc da aula
 * @return
 */
std::string Aula::get_codigo_uc() const {return codigo_uc;}
/**
 * Obter o dia da semana da aula
 * @return
 */
std::string Aula::get_dia_semana() const { return dia_semana; }
/**
 * Obter a hora de início da aula
 * @return
 */
double Aula::get_hora_inicio() const {return hora_inicio;}
/**
 * Obter a duração da aula
 * @return
 */
double Aula::get_duracao() const {return duracao;}
/**
 * Obter o tipo da aula (T - teórica, TP - teórico-prática, PL - prática-laboratorial)
 * @return
 */
std::string Aula::get_tipo() const {return tipo;}

//compare
/**
 * Método de ordenação entre duas aulas de acordo com o dia da semana. Se as aulas forem no mesmo dia, a ordenação é feita tendo em conta a hora de início
 * @param lhs
 * @param rhs
 * @return
 */
bool Aula::cmp(Aula* lhs, Aula* rhs){
    return (dias[lhs->dia_semana] < dias[rhs->dia_semana]) ||
    ((dias[lhs->dia_semana] == dias[rhs->dia_semana]) && (lhs->hora_inicio < rhs->hora_inicio));
}
//show
/**
 * Mostra a hora de início, a duração e o tipo da aula
 */
void Aula::show() const{
    std::cout << "   " << hora_inicio << " - " << hora_inicio+duracao << " | " << tipo;
}

/**
 * Verifica se duas aulas ocorrem em simultâneo
 * @param aula
 * @return
 */
bool Aula::overload(Aula* aula) const{
    return (dia_semana == aula->dia_semana) &&
            (((hora_inicio < aula->hora_inicio) && (duracao+hora_inicio > aula->hora_inicio)) ||
            ((aula->hora_inicio < hora_inicio) && (aula->duracao+aula->hora_inicio > hora_inicio)));
}
/**
 * Overload do operador () ??
 * @param lhs
 * @param rhs
 * @return
 */
bool Aula::cmp_nome::operator()(Aula* lhs, Aula* rhs) const{
    return (dias[lhs->dia_semana] < dias[rhs->dia_semana]) ||
    ((dias[lhs->dia_semana] == dias[rhs->dia_semana]) && (lhs->hora_inicio < rhs->hora_inicio));
}
/**
 *
 */
Aula::OpMap Aula::dias = init_map();
Aula::OpMap1 Aula::pt= init_map1();
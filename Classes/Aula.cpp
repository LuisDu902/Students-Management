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
 * Obter o código_turma da aula
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
 * Método de ordenação entre duas aulas;
 * @param lhs
 * @param rhs
 * @return
 */
bool Aula::cmp_dia_semana::operator()(const Aula* lhs, const Aula* rhs) const  {
    std::map<std::string,int> days = {
            std::pair<std::string,int> ("Monday",1),
            std::pair<std::string,int> ("Tuesday",2),
            std::pair<std::string,int> ("Wednesday",3),
            std::pair<std::string,int> ("Thursday",4),
            std::pair<std::string,int> ("Friday",5),
    };
    if (lhs->dia_semana != rhs->dia_semana){
        return days[lhs->dia_semana] < days[rhs->dia_semana];
    }
    return lhs->hora_inicio < rhs->hora_inicio;
}

bool Aula::cmp_tipo::operator()(const Aula* lhs, const Aula* rhs) const  {
    std::map<std::string,int> days = {
            std::pair<std::string,int> ("Monday",1),
            std::pair<std::string,int> ("Tuesday",2),
            std::pair<std::string,int> ("Wednesday",3),
            std::pair<std::string,int> ("Thursday",4),
            std::pair<std::string,int> ("Friday",5),
    };
    if (lhs->tipo != rhs->tipo) return lhs->tipo < rhs->tipo;
    if (lhs->dia_semana != rhs->dia_semana){
        return days[lhs->dia_semana] < days[rhs->dia_semana];
    }
    return lhs->hora_inicio < rhs->hora_inicio;
}
bool Aula::cmp(Aula* lhs, Aula* rhs){
    std::map<std::string,int> days = {
            std::pair<std::string,int> ("Monday",1),
            std::pair<std::string,int> ("Tuesday",2),
            std::pair<std::string,int> ("Wednesday",3),
            std::pair<std::string,int> ("Thursday",4),
            std::pair<std::string,int> ("Friday",5),
    };
    if (lhs->dia_semana != rhs->dia_semana){
        return days[lhs->dia_semana] < days[rhs->dia_semana];
    }
    return lhs->hora_inicio < rhs->hora_inicio;
}
//show
void Aula::show() {
    std::cout << codigo_turma << " | " << codigo_uc << " | " << dia_semana << " | " << hora_inicio << " | " << duracao << " | " << tipo << std::endl;
}

void Aula::show_horario_turma() {
    std::cout << dia_semana << " | " << hora_inicio << " | " << duracao << " | " << tipo << std::endl;
}
bool Aula::overload(Aula* aula){
    if (dia_semana == aula->dia_semana){
        if (hora_inicio < aula->hora_inicio){
            if (duracao+hora_inicio > aula->hora_inicio) return true;
        }
        else if (aula->hora_inicio < hora_inicio){
            if (aula->duracao+aula->hora_inicio > hora_inicio) return true;
        }
    }
    return false;
}
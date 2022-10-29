//
// Created by du on 13-10-2022.
//

#include "Aula.h"
Aula::Aula(std::string codigo_class, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo){
    this->codigo_class = codigo_class;
    this->codigo_uc = codigo_uc;
    this->dia_semana = dia_semana;
    this->hora_inicio = hora_inicio;
    this->duracao = duracao;
    this->tipo = tipo;
}

void Aula::show() {
    std::cout << codigo_class << " | " << codigo_uc << " | " << dia_semana << " | " << hora_inicio << " | " << duracao << " | " << tipo << std::endl;
}
void Aula::show_horario_turma() {
    std::cout << dia_semana << " | " << hora_inicio << " | " << duracao << " | " << tipo << std::endl;
}
double Aula::get_hora_inicio() {
    return hora_inicio;
}

std::string Aula::get_codigo_class(){return codigo_class;}
std::string Aula::get_codigo_uc(){return codigo_uc;}

bool Aula::APtrComp::operator()(const Aula* lhs, const Aula* rhs) const  {
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
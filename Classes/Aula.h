//
// Created by du on 13-10-2022.
//

#ifndef PROJ_AULA_H
#define PROJ_AULA_H
#include <string>
#include <iostream>
#include <map>
class Aula {
public:
    //construtor
    Aula(std::string codigo_turma, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo);

    //getters
    std::string get_codigo_turma() const;
    std::string get_codigo_uc() const;
    std::string get_dia_semana() const;
    double get_hora_inicio() const;
    double get_duracao() const;
    std::string get_tipo() const;

    //compare
    struct APtrComp{bool operator()(const Aula* lhs, const Aula* rhs) const;};

    //show
    void show_horario_turma();
    void show();

private:
    std::string codigo_turma;
    std::string codigo_uc;
    std::string dia_semana;
    double hora_inicio;
    double duracao;
    std::string tipo;
    //Lista de turmas a que a aula pertence???
};



#endif //PROJ_AULA_H

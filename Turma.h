//
// Created by athos on 13/10/2022.
//

#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include <string>
#include "horario.cpp"



class Turma {
private:
    std::string codigo;
    Horario horario;

public:
    Turma(std::string codigo, Horario horario);
    std::string getCodigo();
    Horario getHorario();
    void setCodigo(std::string codigo);
    void setHorario(Horario horario);
    int get_ano();
    int get_turma();
};


#endif //TRABALHO1_TURMA_H

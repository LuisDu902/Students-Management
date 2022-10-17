//
// Created by athos on 13/10/2022.
//

#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include <string>
#include "Horario.cpp"
#include <vector>


class Turma {
private:
    std::string codigo_turma;
    std::string codigo_uc;
    std::vector<Aula*> aulas;
    int cap;

public:
    Turma(std::string codigo_uc,std::string codigo_turma);
    void show();
    std::string get_codigo_uc();
    std::string get_codigo_turma();
};


#endif //TRABALHO1_TURMA_H

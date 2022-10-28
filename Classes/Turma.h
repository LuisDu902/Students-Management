//
// Created by athos on 13/10/2022.
//

#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include "../../../../../usr/include/c++/11/string"
#include "../../../../../usr/include/c++/11/vector"
#include "Aula.h"

class Turma {
    static const int capacidade_maxima = 25;

private:
    std::string codigo_uc;
    std::string codigo_turma;
    std::vector<Aula*> aulas;
    int capacidade_atual;

public:

    Turma(std::string codigo_uc,std::string codigo_turma);
    void add_capacidade();
    void sub_capacidade();
    void adicionar_aula(Aula* aula);
    void show_horario_turma();
    void show();
    std::string get_codigo_uc() const;
    std::string get_codigo_turma() const;
    int get_capacidade_atual();


};


#endif //TRABALHO1_TURMA_H

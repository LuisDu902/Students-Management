//
// Created by athos on 13/10/2022.
//

#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include <string>
#include <vector>
#include "Aula.h"

class Turma {
    static const int capacidade_maxima = 25;

public:
    //construtor
    Turma(std::string codigo_uc,std::string codigo_turma);

    //getters
    std::vector<Aula*> get_aulas() const;
    std::string get_codigo_uc() const;
    std::string get_codigo_turma() const;
    int get_capacidade_atual() const;

    //operators
    void set_capacidade(int capacidade);
    void adicionar_aula(Aula* aula);

    //show
    void show_horario_turma();
    void show();

private:
    std::string codigo_uc;
    std::string codigo_turma;
    std::vector<Aula*> aulas;
    int capacidade_atual;
};


#endif //TRABALHO1_TURMA_H

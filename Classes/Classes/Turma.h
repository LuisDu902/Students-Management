//
// Created by athos on 13/10/2022.
//

#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include <string>
#include <vector>
#include <algorithm>
#include "Aula.h"
#include "Estudante.h"

class Estudante;
class Turma {


public:
    static const int capacidade_maxima = 30;
    //construtor
    Turma(std::string codigo_uc,std::string codigo_turma);

    //compare
    struct cmp_nome{bool operator()(const Estudante* lhs, const Estudante* rhs) const;};
    struct cmp_codigo{bool operator()(const Estudante* lhs, const Estudante* rhs) const;};
    struct cmp_nr_uc{bool operator()(const Estudante* lhs, const Estudante* rhs) const;};

    //getters
    std::vector<Aula*> get_aulas() const;
    std::string get_codigo_uc() const;
    std::string get_codigo_turma() const;
    std::set<Estudante*,cmp_nome> get_estudantes() const;
    int get_capacidade_atual() const;


    //operators
    void set_capacidade(int capacidade);
    void adicionar_aula(Aula* aula);
    void remover_estudante(Estudante* estudante);
    void adicionar_estudante(Estudante* estudante);

    //show
    void show() const;
    void show_estudantes(int ordem, int ordem_c) const;
    void show_horario_turma();

private:
    std::string codigo_uc;
    std::string codigo_turma;
    std::vector<Aula*> aulas;
    std::set<Estudante*,cmp_nome> estudantes;
    int capacidade_atual;
};


#endif //TRABALHO1_TURMA_H

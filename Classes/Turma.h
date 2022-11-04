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
    static int const capacidade_maxima = 30;
    Turma(std::string codigo_uc,std::string codigo_turma);

    struct cmp_nome{bool operator()(const Estudante*, const Estudante*) const;};
    struct cmp_codigo{bool operator()(const Estudante*, const Estudante*) const;};
    struct cmp_nr_uc{bool operator()(const Estudante*, const Estudante*) const;};

    std::vector<Aula*> get_aulas() const;
    std::string get_codigo_uc() const;
    std::string get_codigo_turma() const;
    std::set<Estudante*,cmp_nome> get_estudantes() const;

    void adicionar_aula(Aula*);
    void remover_estudante(Estudante*);
    void adicionar_estudante(Estudante*);

    void show() const;
    void show_estudantes(int, int) const;
    void show_horario_turma();

private:
    std::string codigo_uc;
    std::string codigo_turma;
    std::vector<Aula*> aulas;
    std::set<Estudante*,cmp_nome> estudantes;
};

#endif //TRABALHO1_TURMA_H

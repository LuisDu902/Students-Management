#ifndef TRABALHO1_TURMA_H
#define TRABALHO1_TURMA_H

#include <vector>
#include <algorithm>
#include "Aula.h"
#include "Estudante.h"

class Estudante;
class Turma {
public:
    Turma(std::string,std::string="-");

    std::string get_codigo_uc() const;
    std::string get_codigo_turma() const;
    std::vector<Aula*> get_aulas() const;
    std::set<Estudante*> get_estudantes() const;

    static int capacidade_maxima;
    static void set_capacidade_maxima(int);

    void adicionar_aula(Aula*);
    void adicionar_estudante(Estudante*);
    void remover_estudante(Estudante*);

    void show() const;
    void show_estudantes(int, int) const;
    void show_horario_turma();

private:
    std::string codigo_uc;
    std::string codigo_turma;
    std::vector<Aula*> aulas;
    std::set<Estudante*> estudantes;
};

#endif //TRABALHO1_TURMA_H

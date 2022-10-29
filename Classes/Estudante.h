//
// Created by Sofia Pinto on 13/10/2022.
//

#ifndef PROJETO_AED_ESTUDANTE_H
#define PROJETO_AED_ESTUDANTE_H
#include <string>
#include <set>
#include "Turma.h"

class Estudante {
    public:
        Estudante(std::string codigo, std::string nome);
        void adicionar_turma(Turma* turma);
        void remover_da_turma(Turma* turma);
        bool compativel();
        std::set<Aula*,Aula::APtrComp> horario();

        void show_horario();
        std::string get_codigo();
        void show();
        std::vector<Turma *> get_turmas() const;
    private:
        std::string nome;
        std::string codigo;
        std::vector<Turma *> turmas;
};


#endif //PROJETO_AED_ESTUDANTE_H

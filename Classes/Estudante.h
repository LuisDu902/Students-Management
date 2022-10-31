//
// Created by Sofia Pinto on 13/10/2022.
//

#ifndef PROJETO_AED_ESTUDANTE_H
#define PROJETO_AED_ESTUDANTE_H
#include <string>
#include <set>
#include "Turma.h"
class Turma;
class Estudante {
    public:
        //construtor
        Estudante(std::string codigo, std::string nome);

        //getters
        std::string get_nome() const;
        std::string get_codigo() const;
        std::vector<Turma *> get_turmas() const;

        //operators
        void adicionar_turma(Turma* turma);
        void remover_da_turma(Turma* turma);
        void alterar_turma(Turma* turma);

        bool compativel(Turma* turma);
        std::set<Aula*,Aula::cmp_dia_semana> horario();

        //show
        void show_horario();
        void show_turmas();

    private:
        std::string nome;
        std::string codigo;
        std::vector<Turma*> turmas;
};


#endif //PROJETO_AED_ESTUDANTE_H

#ifndef PROJETO_AED_ESTUDANTE_H
#define PROJETO_AED_ESTUDANTE_H

#include <string>
#include <utility>
#include <set>
#include "Turma.h"

class Turma;
class Estudante {
public:
    Estudante(std::string , std::string = "");

    std::string get_nome() const;
    std::string get_codigo() const;
    std::vector<Turma*> get_turmas() const;

    void adicionar_turma(Turma*);
    void remover_da_turma(Turma*);
    void alterar_turma(Turma*);
    void trocar_turma_com_estudante(Turma*, Estudante*);
    Turma* procura_turma(const std::string& codigo_uc);
    bool compativel(Turma*);
    std::vector<Aula*> horario();

    void show(int ordem = 1) const;
    void show_horario();
    void show_turmas() const;

private:
    std::string nome;
    std::string codigo;
    std::vector<Turma*> turmas;
};

#endif //PROJETO_AED_ESTUDANTE_H

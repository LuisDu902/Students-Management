//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_GESTAO_H
#define PROJ_GESTAO_H

#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include "Aula.h"
#include "Turma.h"
#include "Estudante.h"
#include "Pedido.h"

class Gestao {
public:
    Gestao();
    std::vector<Aula*> criacao_aulas();
    std::vector<Turma*> criacao_turmas();
    std::set<Estudante*,Turma::cmp_nome> criacao_estudantes();
    std::vector<std::vector<Turma*>> criacao_uc();

    Turma* pesquisa_turma(std::vector<Turma*> turmas, std::string codigo_uc, std::string codigo_turma);
    std::vector<Turma*> pesquisa_uc(std::string codigo_uc);

    bool pode_adicionar_turma(Estudante* es, Turma* t);
    bool pode_alterar_turma(Estudante* es, Turma* turma);

    int max_diferenca(std::vector<Turma*> uc);

    std::vector<Aula*> get_aulas() const;
    std::vector<Turma*> get_turmas() const;
    std::set<Estudante*,Turma::cmp_nome> get_estudantes() const;
    std::vector<std::vector<Turma*>> get_ucs() const;
    std::queue<Pedido*> get_pedidos() const;
    std::list<Pedido*> get_pedidos_falhados() const;

private:
    std::vector<Aula*> aulas;
    std::vector<Turma*> turmas;
    std::set<Estudante*,Turma::cmp_nome> estudantes;
    std::vector<std::vector<Turma*>> ucs;
    std::queue<Pedido*> pedidos;
    std::list<Pedido*> pedidos_falhados;
};


#endif //PROJ_GESTAO_H

//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_GESTAO_H
#define PROJ_GESTAO_H

#include <stack>
#include <set>
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

    Turma* pesquisa_turma(std::string codigo_uc, std::string codigo_turma) const;
    std::vector<Turma*> pesquisa_uc(std::string codigo_uc) ;
    Estudante* pesquisa_estudante(std::string numero) ;

    bool pode_adicionar_turma(Estudante* es, Turma* t);
    bool pode_alterar_turma(Estudante* es, Turma* turma);
    bool pode_remover_turma(Estudante* es, Turma* turma);
    bool pode_trocar_turma(Estudante* es1, Turma* turma1, Estudante* es2);
    bool verifica_mesma_uc(Estudante* es1, Estudante* es2, std::vector<Turma*> uc);

    int max_diferenca(std::vector<Turma*> uc);

    std::vector<Aula*> get_aulas() const;
    std::vector<Turma*> get_turmas() const;
    std::set<Estudante*,Turma::cmp_codigo> get_estudantes() const;
    std::vector<std::vector<Turma*>> get_ucs() const;
    std::queue<Pedido*> get_pedidos() const;
    std::list<Pedido*> get_pedidos_falhados() const;

    void set_pedidos(std::queue<Pedido*> pedidos);
    void show_pedidos();
    void adicionar_pedido(Pedido* pedido);
    void arquivo_pedidos();
    void atualiza_estudantes();

//gestão de pedidos
    void cancelar_pedido(int n);
    void gerir_pedidos();
    void processar_pedido(Pedido*);


private:
    void gerir_pedidos_falhados();
    void criacao_aulas();
    void criacao_turmas();
    void criacao_estudantes();
    void criacao_uc();

    std::vector<Aula*> aulas;
    std::vector<Turma*> turmas;
    std::set<Estudante*,Turma::cmp_codigo> estudantes;
    std::vector<std::vector<Turma*>> ucs;
    std::queue<Pedido*> pedidos;
    std::list<Pedido*> pedidos_falhados;
};


#endif //PROJ_GESTAO_H

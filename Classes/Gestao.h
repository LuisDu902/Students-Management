#ifndef PROJ_GESTAO_H
#define PROJ_GESTAO_H

#include <utility>
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
    Gestao(int);

    Turma* pesquisa_turma(const std::string&, const std::string&) const;
    std::vector<Turma*> pesquisa_uc(const std::string&);
    Estudante* pesquisa_estudante(std::string);

    bool pode_adicionar_turma(Estudante*, Turma*);
    bool pode_remover_turma(Estudante*, Turma*);
    bool pode_alterar_turma(Estudante*, Turma*);
    bool pode_trocar_turma(Estudante*, Turma*, Estudante*);
    bool verifica_mesma_uc(Estudante*, Estudante*, std::vector<Turma*>);

    size_t max_diferenca(std::vector<Turma*>);

    std::set<Estudante*,Turma::cmp_codigo> get_estudantes() const;
    std::vector<std::vector<Turma*>> get_ucs() const;
    std::queue<Pedido*> get_pedidos() const;
    std::list<Pedido*> get_pedidos_falhados() const;

    void adicionar_pedido(Pedido*);
    void arquivo_pedidos();
    void atualiza_estudantes();

    void cancelar_pedido(int);
    void gerir_pedidos();
    void processar_pedido(Pedido*);

private:
    void criacao_aulas();
    void criacao_turmas();
    void criacao_estudantes(int);
    void criacao_uc();
    void gerir_pedidos_falhados();

    std::vector<Aula*> aulas;
    std::vector<Turma*> turmas;
    std::set<Estudante*,Turma::cmp_codigo> estudantes;
    std::vector<std::vector<Turma*>> ucs;
    std::queue<Pedido*> pedidos;
    std::list<Pedido*> pedidos_falhados;
};


#endif //PROJ_GESTAO_H

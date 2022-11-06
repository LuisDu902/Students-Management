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
    Gestao(int,int);

    std::set<Estudante*,Estudante::cmp_codigo> get_estudantes() const;
    std::vector<std::vector<Turma*>> get_ucs() const;
    std::queue<Pedido*> get_pedidos() const;
    std::list<Pedido*> get_pedidos_falhados() const;

    Turma* pesquisa_turma(const std::string&, const std::string&) const;
    std::vector<Turma*> pesquisa_uc(const std::string&);
    Estudante* pesquisa_estudante(std::string);

    bool pode_adicionar_turma(Estudante*, Turma*);
    bool pode_remover_turma(Estudante*, Turma*);
    bool pode_alterar_turma(Estudante*, Turma*);
    bool pode_trocar_turma(Estudante*, Turma*, Estudante*);

    size_t max_diferenca(std::vector<Turma*>);

    static int desequilibrio;
    static void set_desequilibrio(int);
    bool erro_desequilibrio(Pedido*);

    void gerir_pedidos();
    void processar_pedido(Pedido*);
    void adicionar_pedido(Pedido*);
    void cancelar_pedido(int);
    void remover_pedido_falhado(Pedido*);
    void set_pedidos_falhados(std::list<Pedido*>);

    void atualiza_estudantes();
    void arquivo_pedidos();

private:
    void criacao_aulas();
    void criacao_turmas();
    void criacao_estudantes(int);
    void criacao_uc();
    void leitura_pedidos();
    void gerir_pedidos_falhados();

    std::vector<Aula*> aulas;
    std::vector<Turma*> turmas;
    std::set<Estudante*,Estudante::cmp_codigo> estudantes;
    std::vector<std::vector<Turma*>> ucs;
    std::queue<Pedido*> pedidos;
    std::list<Pedido*> pedidos_falhados;
};


#endif //PROJ_GESTAO_H

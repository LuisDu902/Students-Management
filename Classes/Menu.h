
#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include <climits>
#include "Gestao.h"

class Menu {
public:
    Menu();
    void init();
private:
    Gestao* g;
    void ver_estatisticas();
    void ver_conteudos();
    void ver_horarios();
    void ver_estudantes();
    void ver_turmas();
    void fazer_pedido();
    void cancelar_pedido();
    void configuracoes();
    void fim();
    void oportunidade();

    void show_uc(const std::vector<Turma*>&, int, int);
    void show_ano(char, int, int);
    void show_estudantes_mais_de_n_ucs(int, int, int);
    void show_horario_uc(const std::vector<Turma*>&);
    void show_pedidos(int);
    template <typename T> void show_ordem_c(T, int, int, int=0);

    std::string validar_codigo_uc();
    std::string validar_codigo_turma(const std::string&);
    std::string validar_numero_estudante(const std::string&);
    int validar_numero(const std::string&);
    int validar_opcao(const std::string&);
};


#endif //PROJ_MENU_H

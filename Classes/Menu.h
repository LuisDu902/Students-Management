
#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include "Estudante.h"
#include "Gestao.h"

class Menu {
public:
    Menu();
    void init();
    template <typename T>
    static void show_ordem_c(T es, int ordem, int ordem_c);
private:
    Gestao* g;
    void ver_estatisticas();
    void ver_conteudos();
    void ver_horarios();
    void ver_estudantes();
    void ver_turmas();
    void fazer_pedido();
    void cancelar_pedido();
    void fim();
    void extra();
    void show_uc(const std::vector<Turma*>& uc, int ordem, int ordem_c);
    void show_ano(char ano, int ordem, int ordem_c);
    void show_estudantes_mais_que_n_ucs(int n, int ordem, int ordem_c);
    void show_horario_uc(const std::vector<Turma*>& uc);
    void show_pedidos(int ordem);


    std::string validar_codigo_uc();
    std::string validar_codigo_turma(const std::string& cod_uc);
    std::string validar_numero_estudante(const std::string& mensagem);
    int validar_numero(const std::string& mensagem);
    int validar_opcao(const std::string& mensagem);
};


#endif //PROJ_MENU_H

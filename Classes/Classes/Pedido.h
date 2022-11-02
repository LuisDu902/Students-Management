//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_PEDIDO_H
#define PROJ_PEDIDO_H

#include "Estudante.h"

class Pedido {
public:
// construtores
    Pedido(int tipo, Turma* turma, Estudante* estudante1, Estudante* estudante2 = nullptr);

    static bool cmp(Pedido* pedido1, Pedido* pedido2);
    typedef std::map<int, std::string> OpMap;
    static OpMap tipos;
    int get_tipo() const;
    Estudante* get_estudante1() const;
    Estudante* get_estudante2() const;
    Turma* get_turma() const;

private:
    static OpMap init_map(){
        std::map<int, std::string> tipos = {
                std::pair<int, std::string> (1,"Adicionar"),
                std::pair<int, std::string> (2,"Remover"),
                std::pair<int, std::string> (3,"Alterar"),
                std::pair<int, std::string> (4,"Trocar"),
        };
        return tipos;
    }

    Estudante* estudante1;
    Estudante* estudante2;
    Turma* turma1;
    int tipo;
};
#endif
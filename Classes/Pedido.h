#ifndef PROJ_PEDIDO_H
#define PROJ_PEDIDO_H

#include "Estudante.h"

class Pedido {
public:
    Pedido(int, Turma*, Estudante*, Estudante* = nullptr);

    typedef std::map<int, std::string> OpMap;
    static OpMap tipos;

    static bool cmp(Pedido*, Pedido*);

    int get_tipo() const;
    Estudante* get_estudante1() const;
    Estudante* get_estudante2() const;
    Turma* get_turma() const;

private:
    Estudante* estudante1;
    Estudante* estudante2;
    Turma* turma1;
    int tipo;

    static OpMap init_map(){
        std::map<int, std::string> tipo = {
                std::pair<int, std::string> (1,"Adicionar"),
                std::pair<int, std::string> (2,"Remover"),
                std::pair<int, std::string> (3,"Alterar"),
                std::pair<int, std::string> (4,"Trocar"),
        };
        return tipo;
    }


};
#endif
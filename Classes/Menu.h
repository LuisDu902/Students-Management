//
// Created by athos on 31/10/2022.
//

#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <iostream>
#include "Estudante.h"
#include "Gestao.h"

class Menu {
public:
    Menu();
    void init();

private:
    Gestao* g;
    void ver_conteudos();
    void fazer_pedido();
    void fim();
};


#endif //PROJ_MENU_H

//
// Created by Sofia Pinto on 13/10/2022.
//

#ifndef PROJETO_AED_HORARIO_H
#define PROJETO_AED_HORARIO_H
#include <list>
#include "Aula.h"

class Horario {
    Horario(std::list<Aula*> aulas);

    private:
        //lista ou vetor???
        std::list<Aula*> aulas;
};


#endif //PROJETO_AED_HORARIO_H

//
// Created by Sofia Pinto on 13/10/2022.
//

#ifndef PROJETO_AED_ESTUDANTE_H
#define PROJETO_AED_ESTUDANTE_H
#include <string>
#include "Horario.h"


class Estudante {
    public:
        Estudante(std::string nome, int numero, Horario &horario);
        void set_horario(Horario &horario);
        std::string get_nome();
        int get_numero();
        Horario* get_horario();

    private:
        std::string nome;
        int numero;
        Horario* horario;
};


#endif //PROJETO_AED_ESTUDANTE_H

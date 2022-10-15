//
// Created by du on 13-10-2022.
//

#ifndef PROJ_AULA_H
#define PROJ_AULA_H
#include <string>
#include <iostream>
class Aula {
public:
    Aula(std::string codigo_class, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo);
    void show();
    double get_hora_inicio();
private:
    std::string codigo_class;
    std::string codigo_uc;
    std::string dia_semana;
    double hora_inicio;
    double duracao;
    std::string tipo;
    //Lista de turmas a que a aula pertence???
};



#endif //PROJ_AULA_H

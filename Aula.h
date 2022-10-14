//
// Created by du on 13-10-2022.
//

#ifndef PROJ_AULA_H
#define PROJ_AULA_H
#include <string>

class Aula {
public:
    Aula(int codigo_uc,int dia_semana,int hora_inicio,int duracao,std::string tipo);
private:
    int codigo_uc;
    int dia_semana;
    int hora_inicio;
    int duracao;
    std::string tipo;
    //Lista de turmas a que a aula pertence???
};



#endif //PROJ_AULA_H

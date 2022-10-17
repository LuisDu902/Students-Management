//
// Created by athos on 13/10/2022.
//

#include "Turma.h"


Turma::Turma(std::string codigo_uc,std::string codigo_turma){
    this->codigo_turma = codigo_turma;
    this->codigo_uc = codigo_uc;
}

void Turma::show() {
    std::cout << codigo_uc << " | " << codigo_turma << std::endl;
}

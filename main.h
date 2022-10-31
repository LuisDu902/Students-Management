//
// Created by du on 27-10-2022.
//

#ifndef PROJ_MAIN_H
#define PROJ_MAIN_H

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include "Classes/Aula.h"
#include "Classes/Turma.h"
#include "Classes/Estudante.h"


void show_uc(std::vector<Turma*> uc);
void show_ano(std::string ano, std::set<Estudante *, Turma::cmp_nome> estudantes);
void show_estudantes_mais_que_n_ucs(int n,std::set<Estudante *, Turma::cmp_nome> estudantes, std::string modo_de_ordenacao);
#endif //PROJ_MAIN_H

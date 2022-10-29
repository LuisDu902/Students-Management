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

Turma* pesquisa_turma( std::vector<Turma*> turmas, std::string codigo_uc, std::string codigo_turma);
std::vector<Aula*> criacao_aulas();
std::vector<Turma*> criacao_turmas(std::vector<Aula*> vetor_aulas);
std::set<Estudante*,Estudante::cmp>  criacao_estudantes(std::vector<Turma *> turmas);


#endif //PROJ_MAIN_H

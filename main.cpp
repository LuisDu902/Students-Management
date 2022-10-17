
#include <iostream>
#include <fstream>
#include "Aula.cpp"
#include <istream>
#include <sstream>
#include <vector>
#include "Turma.cpp"
std::vector<Aula>  criacao_aulas(){
    std::ifstream myFile;
    std::string CurrentLine;
    myFile.open("/home/du/CLionProjects/Projeto_AED-master/classes.csv");
    getline(myFile,CurrentLine);
    std::vector<Aula> v_global;
    while(getline(myFile,CurrentLine)){
        std::string x;
        std::istringstream iss(CurrentLine);
        std::string codigo_class, codigo_uc, dia_semana,tipo;
        double hora_inicio, duracao;
        (getline(iss,x,',')) ;
        codigo_class = x;
        (getline(iss,x,',')) ;
        codigo_uc = x;
        (getline(iss,x,',')) ;
        dia_semana = x;
        (getline(iss,x,',')) ;
        hora_inicio = stod(x);

        (getline(iss,x,',')) ;
        duracao = stod(x);
        (getline(iss,x,',')) ;
        tipo = x;

        Aula Aula1(codigo_class,codigo_uc,dia_semana,hora_inicio,duracao,tipo);
        v_global.push_back(Aula1);

    }
    return v_global;
}


std::vector<Turma>  criacao_turmas(){
    std::ifstream myFile;
    std::string CurrentLine;
    myFile.open("/home/du/CLionProjects/Projeto_AED-master/classes_per_uc.csv");
    getline(myFile,CurrentLine);
    std::vector<Turma> v_global;
    while(getline(myFile,CurrentLine)){
        std::string x, codigo_uc, codigo_turma;
        std::istringstream iss(CurrentLine);
        (getline(iss,x,',')) ;
        codigo_uc = x;
        (getline(iss,x,',')) ;
        codigo_turma = x;

        Turma Turma1(codigo_uc,codigo_turma);
        v_global.push_back(Turma1);

    }
    return v_global;
}
int main() {
    std::vector<Aula>  vetor_aulas = criacao_aulas();
    for (auto aula: vetor_aulas){
        aula.show();
    }
    std::vector<Turma>  vetor_turmas = criacao_turmas();
    for (auto turma: vetor_turmas){
        turma.show();
    }
    return 0;
}

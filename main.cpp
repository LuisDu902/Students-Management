#include <iostream>
#include <fstream>
#include "Aula.cpp"
#include <istream>
#include <sstream>
#include <vector>

int main() {
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
    for (auto aula: v_global){
        aula.show();
    }
    return 0;
}

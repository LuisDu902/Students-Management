
#include "main.h"
std::vector<Aula*>  criacao_aulas(){
    std::ifstream myFile;
    std::string CurrentLine;
    myFile.open("../CSV files/classes.csv");
    getline(myFile,CurrentLine);
    std::vector<Aula*>  v_global;
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
        tipo.pop_back();
        Aula* ptr = new Aula(codigo_class,codigo_uc,dia_semana,hora_inicio,duracao,tipo);
        v_global.push_back(ptr);

    }
    return v_global;
}

std::vector<Turma*>  criacao_turmas(std::vector<Aula*> vetor_aulas){
    std::ifstream myFile;
    std::string CurrentLine;
    myFile.open("../CSV files/classes_per_uc.csv");
    getline(myFile,CurrentLine);
    std::vector<Turma*> v_global;
    while(getline(myFile,CurrentLine)){
        std::string x, codigo_uc, codigo_turma;
        std::istringstream iss(CurrentLine);
        (getline(iss,x,',')) ;
        codigo_uc = x;
        (getline(iss,x,',')) ;
        codigo_turma = x;
        codigo_turma.pop_back();
        Turma* ptr = new Turma(codigo_uc,codigo_turma);
        v_global.push_back(ptr);
    }
    for (Aula* aula : vetor_aulas){
        Turma* turma = pesquisa_turma(v_global,aula->get_codigo_uc(),aula->get_codigo_class());
        turma->adicionar_aula(aula);
    }
    return v_global;
}

Turma* pesquisa_turma( std::vector<Turma*> turmas, std::string codigo_uc, std::string codigo_turma){
    for (auto turma : turmas){
        if (turma->get_codigo_turma() == codigo_turma && turma->get_codigo_uc() == codigo_uc){
            return turma;
        }
    }

}
//std::set<Estudante> estudantes

std::vector<Estudante*>  criacao_estudantes(std::vector<Turma *> turmas){
    std::ifstream myFile;
    std::string CurrentLine;
    myFile.open("../CSV files/students_classes.csv");
    getline(myFile,CurrentLine);
    std::vector<Estudante*> v_global;
    Estudante* ultimo_estudante = new Estudante("0","0");
    bool first = true;
    while(getline(myFile,CurrentLine)){
        std::string x, codigo,nome,codigo_uc,codigo_turma;
        std::istringstream iss(CurrentLine);
        (getline(iss,x,',')) ;
        codigo = x;
        (getline(iss,x,',')) ;
        nome = x;
        (getline(iss,x,',')) ;
        codigo_uc = x;
        (getline(iss,x,',')) ;
        codigo_turma = x;
        codigo_turma.pop_back();
        if (first) {
            first = false;
            Estudante* ptr = new Estudante(codigo,nome);
            Turma * ptr_turma = pesquisa_turma(turmas, codigo_uc,codigo_turma);
            ptr->adicionar_turma(ptr_turma);
            ultimo_estudante = ptr;
        }
        else if (codigo == ultimo_estudante->get_codigo()){
            Turma * ptr_turma = pesquisa_turma(turmas, codigo_uc,codigo_turma);
            ultimo_estudante->adicionar_turma(ptr_turma);
        }
        else{
            v_global.push_back(ultimo_estudante);
            Estudante* ptr = new Estudante(codigo,nome);
            Turma * ptr_turma = pesquisa_turma(turmas, codigo_uc,codigo_turma);
            ptr->adicionar_turma(ptr_turma);
            ultimo_estudante = ptr;
        }

    }
    return v_global;
}

int main() {
    std::vector<Aula*>  vetor_aulas =  criacao_aulas();
    /*for (auto aula: vetor_aulas){
        aula->show();
    }*/
    std::vector<Turma*>  vetor_turmas = criacao_turmas(vetor_aulas);


    std::vector<Estudante*> vetor_estudantes = criacao_estudantes(vetor_turmas);

    vetor_turmas.at(56)->show_horario_turma();

    Estudante * es = vetor_estudantes.at(3);
    Turma* t = vetor_turmas.at(56);

    //t->show_horario_turma();

    return 0;
}
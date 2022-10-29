
#include "main.h"
std::vector<Aula*>  criacao_aulas(){

    std::vector<Aula*> aulas;
    std::string CurrentLine, x, codigo_turma, codigo_uc, dia_semana, tipo;
    double hora_inicio, duracao;
    std::ifstream myFile;

    myFile.open("../CSV files/classes.csv");
    getline(myFile,CurrentLine);

    while(getline(myFile,CurrentLine)){

        std::istringstream iss(CurrentLine);

        getline(iss,codigo_turma,',');
        getline(iss,codigo_uc,',');
        getline(iss,dia_semana,',');
        getline(iss,x,',');     hora_inicio = stod(x);
        getline(iss,x,',');     duracao = stod(x);
        getline(iss,tipo,',');  if (tipo.back() == '\r') tipo.pop_back();

        Aula* ptr = new Aula(codigo_turma,codigo_uc,dia_semana,hora_inicio,duracao,tipo);
        aulas.push_back(ptr);
    }

    return aulas;
}

std::vector<Turma*> criacao_turmas(std::vector<Aula*> vetor_aulas){

    std::vector<Turma*> turmas;
    std::string CurrentLine, codigo_uc, codigo_turma;
    std::ifstream myFile;

    myFile.open("../CSV files/classes_per_uc.csv");
    getline(myFile,CurrentLine);

    while(getline(myFile,CurrentLine)){

        std::istringstream iss(CurrentLine);

        getline(iss,codigo_uc,',');
        getline(iss,codigo_turma,',');  if (codigo_turma.back() == '\r') codigo_turma.pop_back();

        Turma* ptr = new Turma(codigo_uc,codigo_turma);
        turmas.push_back(ptr);
    }

    for (Aula* aula : vetor_aulas){
        Turma* turma = pesquisa_turma(turmas,aula->get_codigo_uc(),aula->get_codigo_turma());
        turma->adicionar_aula(aula);
    }

    return turmas;
}

Turma* pesquisa_turma( std::vector<Turma*> turmas, std::string codigo_uc, std::string codigo_turma){

    for (auto turma : turmas){
        if (turma->get_codigo_turma() == codigo_turma && turma->get_codigo_uc() == codigo_uc){
            return turma;
        }
    }

}

std::set<Estudante*,Estudante::cmp> criacao_estudantes(std::vector<Turma *> turmas){

    std::set<Estudante*,Estudante::cmp> estudantes;
    std::ifstream myFile;
    std::string CurrentLine, codigo, nome, codigo_uc, codigo_turma;;

    myFile.open("../CSV files/students_classes.csv");
    getline(myFile,CurrentLine);

    Estudante* estudante_atual = new Estudante("0","0");
    bool first = true;

    while(getline(myFile,CurrentLine)){

        std::istringstream iss(CurrentLine);

        getline(iss,codigo,',');
        getline(iss,nome,',');
        getline(iss,codigo_uc,',');
        getline(iss,codigo_turma,',');  if (codigo_turma.back() == '\r') codigo_turma.pop_back();

        if (first) {
            first = false;

            Estudante* estudante_novo = new Estudante(codigo,nome);
            estudante_atual = estudante_novo;

            Turma * turma = pesquisa_turma(turmas, codigo_uc,codigo_turma);
            estudante_novo->adicionar_turma(turma);
        }

        else if (codigo == estudante_atual->get_codigo()){
            Turma * turma = pesquisa_turma(turmas, codigo_uc,codigo_turma);
            estudante_atual->adicionar_turma(turma);
        }

        else{
            estudantes.insert(estudante_atual);

            Estudante* estudante_novo = new Estudante(codigo,nome);
            estudante_atual = estudante_novo;

            Turma * turma = pesquisa_turma(turmas, codigo_uc, codigo_turma);
            estudante_novo->adicionar_turma(turma);
        }

    }
    return estudantes;
}

int main() {
    std::vector<Aula*>  aulas =  criacao_aulas();
    std::vector<Turma*>  turmas = criacao_turmas(aulas);
    std::set<Estudante*,Estudante::cmp>  estudantes = criacao_estudantes(turmas);


    /*for (auto aula: vetor_aulas){
        aula->show();
    }*/


    Estudante * es = *estudantes.begin();
    Turma* t = turmas.at(56);
    for (auto it = estudantes.begin(); it!= estudantes.end(); it++){
        (*it)->show_turmas();
    }
   /* std::set<Aula*,Aula::cmp_dia_semana> a = es->horario();
    es->show_horario();
*/
    return 0;
}
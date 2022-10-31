
#include "main.h"
#include "Classes/Menu.h"

void show_uc(std::vector<Turma*> uc){
    std::set<Estudante*,Turma::cmp_nome> estudantes;

    for (auto turma: uc){
        for (auto es:turma->get_estudantes()) estudantes.insert(es);}

    std::cout << estudantes.size();
    for (auto x: estudantes){
        std::cout << x->get_nome() << std::endl;
}}
void show_ano(std::string ano, std::set<Estudante *, Turma::cmp_nome> estudantes){
    std::set<Estudante*,Turma::cmp_nome> es;
    int count = 0;
    for (Estudante* estudante: estudantes){
        if (estudante->get_codigo().substr(0,4) == ano){
            count++;
            es.insert(estudante);
        }
    }
    for (auto estudante: es){
        std::cout << estudante->get_nome() << std::endl;
    }
    std::cout << count;
}
void show_estudantes_mais_que_n_ucs(int n,std::set<Estudante *, Turma::cmp_nome> estudantes, std::string modo_de_ordenacao = "ordem alfabética"){
    int count = 0;
    if (modo_de_ordenacao == "numero de ucs") {
        std::set<Estudante*, Turma::cmp_nr_uc> es;
        for (Estudante* estudante: estudantes) {
            if (estudante->get_turmas().size() >= n) {
                count++;
                es.insert(estudante);
                std::cout << estudante->get_nome() << std::endl;
            }
        }
        for (auto estudante: es) {
            std::cout << estudante->get_nome() << std::endl;
        }
        std::cout << count;
    }

    else if (modo_de_ordenacao == "codigo") {
        std::set<Estudante*, Turma::cmp_codigo> es1;
        for (Estudante* estudante: estudantes) {
            if (estudante->get_turmas().size() >= n) {
                count++;
                es1.insert(estudante);
            }
        }
        for (auto estudante: es1) {
            std::cout << estudante->get_nome() << std::endl;
        }
        std::cout << count;
    }

    else {
        std::set<Estudante*, Turma::cmp_nome> es1;
        for (Estudante* estudante: estudantes) {
            if (estudante->get_turmas().size() >= n) {
                count++;
                es1.insert(estudante);
            }
        }
        for (auto estudante: es1) {
            std::cout << estudante->get_nome() << std::endl;
        }
        std::cout << count;
    }
    }

int main() {
    Menu menu1;
    menu1.init();
    //std::vector<Turma*> uc = pesquisa_uc("L.EIC001",ucs);
    //show_uc(uc);
    //int max = max_diferenca(uc);
    //for (auto t: turmas) t->show();
    //for (auto t: uc){
    //    t->show();
    //}
    //for (auto t: ucs){std::cout << t.back()->get_codigo_uc() << " : " << max_diferenca(t) << std::endl;}

    /*for (auto aula: vetor_aulas){
        aula->show();
    }*/

    //Estudante * es = *estudantes.begin();
    //es->show_turmas();
    //es->show_horario();
    //std::cout << "\n..........\n";
    //es->get_turmas().front()->show_horario_turma();
    //Turma* t = turmas.at(18);
    //Turma* t1 = turmas.at(5);
    //Turma* t2 = turmas.at(76); //dá para alterar turmas
    //std::cout << pode_alterar_turma(es,t2,ucs);

    /*for (auto it = estudantes.begin(); it!= estudantes.end(); it++){
        (*it)->show_turmas();
    }*/
    //t1->show_horario_turma();
    //t->show_horario_turma();
    //t2->show_horario_turma();
    //es->show_horario();
    //std::cout << es->compativel(t); // é compatível
    //std::cout << es->compativel(t1); //não é compatível
    //std::cout << max_diferenca(pesquisa_uc(t->get_codigo_uc(),ucs));
    //std::cout << pode_adicionar_turma(es,t,ucs);
    //t->show();
    //t->show_estudantes();
    //std::set<Aula*,Aula::cmp_dia_semana> a = es->horario();
    //es->show_horario();
    //es->adicionar_turma(t);
    //t->show_horario_turma();
    /*t->show_estudantes();
    es->remover_da_turma(t);
    t->show();
    t->show_estudantes();*/
    /*for (auto x: turmas){
        x->show();
    }*/
    //std::cout << ".......\n";
    //es->show_horario();
    //es->adicionar_turma(t1);
    //std::cout << ".......\n";
    //es->show_horario();
    //Turma* turma1 = turmas.at(120);
    //std::cout<< turma1->get_capacidade_atual() << std::endl;;
    //std::cout << es->compativel(turma1) << std::endl;
    //std::cout << es->compativel(t) << std::endl;
    //show_uc("L.EIC001",turmas);
    //show_ano("2019",estudantes);

    //show_estudantes_mais_que_n_ucs(6,estudantes, "numero de ucs");
    //show_estudantes_mais_que_n_ucs(6,estudantes, "codigo");
    //show_estudantes_mais_que_n_ucs(6,estudantes);
    return 0;
}
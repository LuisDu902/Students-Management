//
// Created by athos on 31/10/2022.
//

#include "Menu.h"

Menu::Menu(){
    g = new Gestao;
    std::cout << "Bem-vindo!" << '\n';
}

void Menu::init() {
    int input;
    while (true) {
        std::cout << "O que pretende fazer?\n[1] Ver estatísticas\n[2] Visualizar conteúdos\n[3] Realizar pedido\n[4] Terminar\n";
        std::cin >> input;
        switch (input) {
            case 1: {
                ver_estatisticas();
                break;
            }
            case 2: {
                ver_conteudos();
                break;
            }
            case 3: {
                fazer_pedido();
                break;
            }
            case 4: {
                // fim();
                std::cout << "Até à próxima!";
                return;
            }
            default: {
                std::cout << "Caractere Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }

}

void Menu::ver_estatisticas(){
    int input;
    while (true) {
        std::cout << "Selecione o que pretende ver:\n"
                     "[1] Nº de estudantes numa turma\n"
                     "[2] Nº de estudantes numa UC\n"
                     "[3] Nº de estudantes num ano\n"
                     "[4] Nª de estudantes com mais de n UC's\n"
                     "[5] Nº de turmas por UC\n"
                     "[6] Nº de pedidos efetuados\n"
                     "[7] Voltar atrás\n";
        std::cin >> input;
        int numero;
        switch (input) {
            case 1: {
                std::cout<< "Insira o número da turma:";

                break;
            }
            case 2: {
                for (auto turma: g->get_turmas()) {
                    turma->show();
                }
                break;
            }
            case 3: {

                break;
            }
            case 6: {
                numero = g->get_pedidos().size();
                if (numero == 1) std::cout<< "Foi efetuado " << numero << " pedido\n";
                else std::cout<< "Foram efetuados " << numero << " pedidos\n";
            }
            case 7: {
                return;
            }
            default: {
                std::cout << "Caractere Invalido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }

        }

    }
}

void Menu::ver_conteudos(){
    int input;
    while (true) {
        std::cout << "Selecione o que pretende ver:\n[1] Aulas\n[2] Turmas\n[3] Estudantes\n[4] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                for (auto aula: g->get_aulas())
                    aula->show();
                break;
            }
            case 2: {
                for (auto turma: g->get_turmas()) {
                    turma->show();
                }
                break;
            }
            case 3: {
                std::set<Estudante *, Turma::cmp_nome> vetor_estudantes = g->get_estudantes();
                for (auto estudante: vetor_estudantes) {
                    std::cout << estudante->get_nome() << '\n';
                }
                break;
            }
            case 4: {
                return;
            }
            default: {
                std::cout << "Caractere Invalido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }

        }

    }
}




void Menu::fazer_pedido(){
    std::cout <<"Selecione um estudante:\n";
    std::string nome;
    std::cin >> nome;
    std::cout << "Que pedido pretende fazer:\n[1] Adicionar a uma turma\n";
    int input;
    std::cin >> input;
    if (input == 1){
        std::cout << "Escolha uma turma:\n";
        std::string codigo_uc,codigo_turma;
        std::cout << "Codigo_uc:";
        std::cin >> codigo_uc;
        std::cout << "Codigo_turma:";
        std::cin>> codigo_turma;
        Estudante* estudante = g->pesquisa_estudante(nome);
        estudante->show_turmas();
        Turma* turma = g->pesquisa_turma(codigo_uc,codigo_turma);

        if (g->pode_adicionar_turma(estudante,turma)){
            Pedido* pedido = new Pedido(turma,estudante);
            g->get_pedidos().push(pedido);
            std::cout<< "Pedido válido\n";
        }
        else{
            std::cout << "Pedido inválido\n";
        }
    }
};

void Menu::fim(){
    //se existirem pedidos -> efetua-los
    // se comprimento de pedidos falhados == 0: std::cout << "Todos os pedidos foram efetuados com sucesso!"
    //else:
}

//CENAS QUE ESTAVAM NO MAIN
void Menu::show_uc(std::vector<Turma*> uc){
    std::set<Estudante*,Turma::cmp_nome> estudantes;

    for (auto turma: uc){
        for (auto es:turma->get_estudantes()) estudantes.insert(es);}

    std::cout << estudantes.size();
    for (auto x: estudantes){
        std::cout << x->get_nome() << std::endl;
    }}
void Menu::show_ano(std::string ano, std::set<Estudante *, Turma::cmp_nome> estudantes){
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
void Menu::show_estudantes_mais_que_n_ucs(int n,std::set<Estudante *, Turma::cmp_nome> estudantes, std::string modo_de_ordenacao = "ordem alfabética"){
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

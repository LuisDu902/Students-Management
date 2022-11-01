
#include <climits>
#include "Menu.h"
/**
 * Construtor da classe Menu
 */
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
                     "[4] Nº de turmas numa UC\n"
                     "[5] Nº de pedidos efetuados\n"
                     "[6] Voltar atrás\n";
        std::cin >> input;
        switch (input) {
            case 1: {
                std::string cod_turma, cod_uc;
                std::cout<< "Insira o código da turma:";
                std::cin >> cod_turma;
                std::cout<< "Insira o código da UC:";
                std::cin >> cod_uc;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                std::cout<< "Estão inscritos " << turma->get_capacidade_atual() << " alunos nesta turma\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 2: {
                std::string cod_uc;
                std::cout<< "Insira o código da UC:";
                std::cin >> cod_uc;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                int total_alunos = 0;
                for (auto turma: uc){
                    total_alunos += turma->get_capacidade_atual();
                }
                std::cout<< "Estão inscritos " << total_alunos << " alunos nesta UC\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 3: {
                std::string ano;
                std::cout << "Insira o ano:";
                std::cin >> ano;
                int total_alunos = 0;
                for (Estudante* estudante: g->get_estudantes()){
                    if (estudante->get_codigo().substr(0,4) == ano){
                        total_alunos++;
                    }
                }
                std::cout<< "Estão inscritos " << total_alunos << " alunos no " << ano <<"º ano\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 4: {
                std::string cod_uc;
                std::cout<< "Insira o código da UC:";
                std::cin >> cod_uc;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                std::cout<< "Existem " << uc.size() << " turmas nesta UC\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 5: {
                int numero = g->get_pedidos().size();
                if (numero == 1) std::cout<< "Foi efetuado " << numero << " pedido\n";
                else std::cout<< "Foram efetuados " << numero << " pedidos\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 6: {
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
                    estudante->show();
                    std::cout << std::endl;
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
            Pedido* pedido = new Pedido("adicionar", turma,estudante);
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
        estudante->show();
        std::cout << std::endl;
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
            estudante->show();
            std::cout << std::endl;
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
            estudante->show();
            std::cout << std::endl;
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
            estudante->show();
            std::cout << std::endl;
        }
        std::cout << count;
    }
}

//testar show_pedidos
void Menu::show_pedidos(){
    std::queue<Pedido*> fila_temp;
    unsigned initial_size = g->get_pedidos().size();
    for (unsigned i = 0; i< initial_size;i++){
        Pedido* p = g->get_pedidos().front();
        std::cout << p->get_tipo();
        fila_temp.push(g->get_pedidos().front());
    }
    g->set_pedidos(fila_temp);
}
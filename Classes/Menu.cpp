//
// Created by athos on 31/10/2022.
//

#include "Menu.h"

Menu::Menu(){
    g = new Gestao();
    std::cout << "Bem-vindo!" << '\n';
}

void Menu::init() {
    std::cout << "O que pretende fazer?" << '\n' << "[1] Verificar conteúdos" << '\n'<< "[2] Realizar pedido" << '\n' << "[3] Terminar" << '\n';
    int input;
    std::cin >> input;
    switch (input) {
        case 1:{
            ver_conteudos();
            break;}
        case 2:{
            fazer_pedido();
            break;}
        case 3:{
            // fim();
            std::cout << "Até à próxima!";
            return;
        }
        default:{
            std::cout << "Caractér inválido";
        }
    }
    init();
}

void Menu::ver_conteudos(){
    //system("CLS");
    std::cout <<"Selecione o que pretende ver:" << '\n' << "[1] Aulas" << '\n'<< "[2] Turmas" << '\n' << "[3] Estudantes" << '\n' << "[4] Voltar ao início" << '\n';
    int input;
    std::cin >> input;
    switch (input) {
        case 1:{
            for (auto aula: g->get_aulas())
                aula->show();
            break;}
        case 2:{
            for (auto turma: g->get_turmas()){
                turma->show();
            }
            break;}
        case 3: {
            std::set<Estudante*, Turma::cmp_nome> vetor_estudantes = g->get_estudantes();
            for (auto estudante: vetor_estudantes) {
                std::cout << estudante->get_nome() << '\n';
            }
            break;
        }
        case 4: {
            init();
        }
        default:{
            std::cout << "Caractér inválido";
            break;}
    }
};

void Menu::fazer_pedido(){};

void Menu::fim(){
    //se existirem pedidos -> efetua-los
    // se comprimento de pedidos falhados == 0: std::cout << "Todos os pedidos foram efetuados com sucesso!"
    //else:
}
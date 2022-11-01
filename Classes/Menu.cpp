
#include <climits>
#include "Menu.h"
/**
 * Construtor da classe Menu
 */
Menu::Menu(){
    g = new Gestao;
    std::cout << "Bem-vindo!\n";
}

void Menu::init() {
    int input;
    while (true) {
        std::cout << "O que pretende fazer?\n"
                     "[1] Ver estatísticas\n"
                     "[2] Visualizar conteúdos\n"
                     "[3] Realizar pedido\n"
                     "[4] Terminar\n";
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
                std::cout << "Até à próxima!\nAss: G67";
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
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);

                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                std::cout<< "Estão inscritos " << turma->get_capacidade_atual() << " alunos nesta turma\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
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
                char ano = validar_numero("Insira o ano:");

                int total_alunos = 0;
                for (auto uc : g->get_ucs()){
                    if (uc.front()->get_codigo_turma().at(0) == ano){
                        for (auto turma : uc){
                            for (auto estudante : turma->get_estudantes()){
                                total_alunos++;}}}}
                std::cout<< "Estão inscritos " << total_alunos << " alunos no " << ano <<"º ano\n";
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 4: {
                std::string cod_uc = validar_codigo_uc();

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
                std::cout << "Caractere Inválido\n";
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
        std::cout << "Selecione o que pretende ver:\n[1] Horários\n[2] Estudantes\n[3] Pedidos\n[4] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                ver_horarios();
                break;
            }
            case 2: {
                int ordem;
                std::cout << "Por que ordem prefere ver os estudantes?\n[1] Alfabética\n[2] Numérica\n";
                std::cin >> ordem;
                while(std::cin.fail() || (ordem != 1 && ordem != 2)) {
                        std::cout << "Input inválido" << std::endl;
                        std::cout << "Por que ordem prefere ver os estudantes?\n[1] Alfabética\n[2] Numérica\n";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cin >> ordem;
                    }
                ver_estudantes(ordem);
                break;
            }
            case 3: {
                ver_pedidos();
                break;
            }
            case 4: {
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


//FALTA MUDAR O LAYOUT DOS HORÁRIOS
void Menu::ver_horarios(){
    int input;
    while (true) {
        std::cout << "Pretende ver o horário de:\n[1] Uma turma\n[2] Uma UC\n[3] Um estudante\n[4] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);

                Turma* turma = g->pesquisa_turma(cod_uc,cod_turma);
                turma->show_horario_turma();
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();

                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                //uc->show_horario
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 3: {
                std::string cod_estudante = validar_numero_estudante("Insira o número up:");

                Estudante* estudante = g->pesquisa_estudante(cod_estudante);
                estudante->show_horario();
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 4: {
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

void Menu::ver_estudantes(int ordem){
    int input;
    while (true) {
        std::cout << "Pretende ver os estudantes:\n"
                     "[1] De uma turma\n"
                     "[2] De uma UC\n"
                     "[3] De um ano\n"
                     "[4] Com mais de n UC's\n"
                     "[5] Voltar atrás";
        std::cin >> input;

        switch (input) {
            case 1: {
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);

                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                turma->show_estudantes(ordem);
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                show_uc(uc, ordem);
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 3: {
                char ano = validar_numero("Insira o ano:");
                show_ano(ano, ordem);
                std::cout << "\n---------------------------------------------------\n";
                break;
            }
            case 4:{

                char o = validar_numero("\"Deseja ordenar os estudantes pelo número de UC's?\n"
                                        "[1] Sim, por ordem crescente\n"
                                        "[2] Sim, por ordem decrescente\n"
                                        "[3] Não\n");
                char n;
                std::cout << "Insira o n:";
                std::cin >> n;
                //FALTA ALTERAR ESTA FUNÇAO
                while(std::cin.fail() || (n < 0)) {
                    std::cout << "Input inválido" << std::endl;
                    std::cout << "Insira o n:";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cin >> ordem;
                }

                show_estudantes_mais_que_n_ucs(n, ordem);
                break;
            }
            case 5: {
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

void Menu::ver_pedidos(){
    show_pedidos();
}

void Menu::fazer_pedido(){
    while(true) {
        std::string numero = validar_numero_estudante("Selecione um estudante:");
        std::cout
                << "Que pedido pretende fazer:\n"
                   "[1] Adicionar a uma turma\n"
                   "[2] Remover de uma turma\n"
                   "[3] Alterar a turma de uma UC\n"
                   "[4] Trocar de turma com outro estudante\n"
                   "[5] Voltar atrás\n";
        int input;
        std::cin >> input;

        switch (input) {
            case 1: {
                std::cout << "Escolha uma turma:\n";
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Estudante *estudante = g->pesquisa_estudante(numero);
                estudante->show_turmas();

                if (g->pode_adicionar_turma(estudante, turma)) {
                    Pedido *pedido = new Pedido("adicionar", turma, estudante);
                    g->get_pedidos().push(pedido);
                    std::cout << "Pedido válido";
                    std::cout << "\n---------------------------------------------------\n";
                } else {
                    std::cout << "Pedido inválido";
                    std::cout << "\n---------------------------------------------------\n";
                }
                return;
            }
            case 2: {
                std::cout << "Escolha uma turma:\n";
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Estudante *estudante = g->pesquisa_estudante(numero);

                if (g->pode_remover_turma(estudante, turma)) {
                    Pedido *pedido = new Pedido("remover", turma, estudante);
                    g->get_pedidos().push(pedido);
                    std::cout << "Pedido válido";
                } else {
                    std::cout << "Pedido inválido";
                }
                std::cout << "\n---------------------------------------------------\n";

                return;
            }
            case 3: {
                std::cout << "Escolha uma turma:\n";
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Estudante *estudante = g->pesquisa_estudante(numero);

                if (g->pode_alterar_turma(estudante, turma)) {
                    Pedido *pedido = new Pedido("alterar", turma, estudante);
                    g->get_pedidos().push(pedido);
                    std::cout << "Pedido válido";
                } else {
                    std::cout << "Pedido inválido";
                }
                std::cout << "\n---------------------------------------------------\n";
                return;
            }
            case 4: {
                std::string numero_troca = validar_numero_estudante("Selecione o estudante com quem pretende trocar:\n");

                std::cout << "Escolha a turma que pretende trocar:\n";
                std::string cod_uc = validar_codigo_uc();
                std::string cod_turma = validar_codigo_turma(cod_uc);

                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                Estudante *estudante_troca = g->pesquisa_estudante(numero_troca);
                Estudante *estudante = g->pesquisa_estudante(numero);

                if (g->pode_trocar_turma(estudante, turma, estudante_troca)) {
                    Pedido *pedido = new Pedido("trocar", turma, estudante, estudante_troca);
                    g->get_pedidos().push(pedido);
                    std::cout << "Pedido válido";
                    std::cout << "\n---------------------------------------------------\n";
                } else {
                    std::cout << "Pedido inválido";
                    std::cout << "\n---------------------------------------------------\n";
                }
                return;
            }
            case 5: {
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

};

void Menu::fim(){
    if (g->get_pedidos().size() != 0){
        g->gerir_pedidos();
        if (g->get_pedidos_falhados().size() == 0) std::cout << "Todos os pedidos foram efetuados com sucesso!\n" << std::endl;
        else std::cout << "Pedidos por realizar: " << g->get_pedidos_falhados().size() << std::endl;
    }
}

void Menu::show_uc(std::vector<Turma*> uc, int ordem){
    std::set<Estudante*,Turma::cmp_nome> estudantes;

    for (auto turma: uc){
        for (auto es:turma->get_estudantes()) estudantes.insert(es);}

    std::cout << estudantes.size();
    for (auto estudante: estudantes){
        estudante->show(ordem);
        std::cout << std::endl;
    }}

void Menu::show_ano(char ano, int ordem){
    std::set<Estudante*,Turma::cmp_nome> estudantes;
    for (auto uc : g->get_ucs()){
        if (uc.front()->get_codigo_turma().at(0) == ano){
            for (auto turma : uc){
                for (auto estudante : turma->get_estudantes()){
                    estudantes.insert(estudante);}}}}
    for (auto estudante: estudantes){
        estudante->show(ordem);
        std::cout << std::endl;
    }

}
void Menu::show_estudantes_mais_que_n_ucs(int n, int ordem){
    int count = 0;
    switch (ordem) {
        case 1: {
            std::set<Estudante*, Turma::cmp_nome> es1;
            for (Estudante* estudante: g->get_estudantes()) {
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
            break;
        }
        case 2:{
            std::set<Estudante*, Turma::cmp_codigo> es1;
            for (Estudante* estudante: g->get_estudantes()) {
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
            break;
        }
        case 3:{
            std::set<Estudante*, Turma::cmp_nr_uc> es;
            for (Estudante* estudante: g->get_estudantes()) {
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
            break;
        }
    }

}

//testar show_pedidos
void Menu::show_pedidos(){
    std::queue<Pedido*> fila_temp;
    unsigned initial_size = g->get_pedidos().size();
    for (unsigned i = 0; i< initial_size;i++){
        Pedido* p = g->get_pedidos().front();
        std::cout << p->get_tipo() << std::endl;
        fila_temp.push(g->get_pedidos().front());
    }
    g->set_pedidos(fila_temp);
}

std::string Menu::validar_codigo_uc(){
    std::string cod_uc;
    std::cout<< "Insira o código da UC:";
    std::cin >> cod_uc;

    while(std::cin.fail() || g->pesquisa_uc(cod_uc).empty()) {
        std::cout << "Input inválido" << std::endl;
        std::cout << "Insira o código da UC:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_uc;
    }
    return cod_uc;
}

std::string Menu::validar_codigo_turma(std::string cod_uc){
    std::string cod_turma;
    std::cout<< "Insira o código da turma:";
    std::cin >> cod_turma;

    while(std::cin.fail() || g->pesquisa_turma(cod_uc,cod_turma) == nullptr) {
        std::cout << "Input inválido" << std::endl;
        std::cout << "Insira o código da turma:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_turma;
    }
    return cod_turma;
}

std::string Menu::validar_numero_estudante(std::string mensagem){
    std::string numero;
    std::cout<< mensagem;
    std::cin >> numero;

    while(std::cin.fail() || g->pesquisa_estudante(numero) == nullptr) {
        std::cout << "Input inválido" << std::endl;
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> numero;
    }
    return numero;
}

char Menu::validar_numero(std::string mensagem){
    char numero;
    std::cout<< mensagem;
    std::cin >> numero;

    while(std::cin.fail() || numero > 3 || numero < 1) {
        std::cout << "Input inválido" << std::endl;
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> numero;
    }
    return numero;
}

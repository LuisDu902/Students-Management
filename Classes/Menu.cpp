#include "Menu.h"
/**
 * Construtor da classe Menu
 */
Menu::Menu(){
    std::cout << "Bem-vindo!\n"
                 "[Pressione -1 sempre que tencione voltar para trás]\n";

    std::ifstream myfile;
    myfile.open ("C:/Users/luisd/OneDrive/Ambiente de Trabalho/Projeto_AED-erro-pedido-troca/CSV files/new_students_classes.csv");
    int n = 1, m = 2;
    if (myfile.is_open()) {
        myfile.close();
        n = validar_opcao("\nPretende utilizar os dados do ficheiro:\n[1] Inicial\n[2] Atualizado\n");
        if (n == 2) {
            m = validar_opcao("\nPretende restaurar os pedidos falhados do dia anterior?\n[1] Sim\n[2] Não\n");
        }
    }
    g = new Gestao(n,m);
}

/**
 * Menu principal
 */
void Menu::init() {
    int input;
    while (true) {
        std::cout << "\n============ Menu Principal ============\n"
                     "O que pretende fazer?\n"
                     "[1] Ver estatísticas\n"
                     "[2] Visualizar conteúdos\n"
                     "[3] Realizar pedido\n"
                     "[4] Cancelar pedido\n"
                     "[5] Alterar configurações\n"
                     "[6] Terminar\n";
        std::cin >> input;
        switch (input) {
            case -1: {
                std::cout << "\nAinda não encontramos a máquina do tempo :(\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
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
                if (g->get_pedidos().empty()) std::cout << "Não há pedidos para cancelar\n";
                else {
                    std::cout << "\n============ Cancelar Pedido ============\n";
                    show_pedidos(1);
                    std::cout << '\n';
                    cancelar_pedido();
                }
                break;
            }
            case 5: {
                configuracoes();
                break;
            }
            case 6: {
                int opcao = validar_opcao("Tem a certeza que pretende terminar? [A sua ação é irreversível]\n[1] Sim\n[2] Não\n");
                if (opcao == 1) {
                    fim();
                    std::cout << "Até à próxima!\nAss: G67";
                    return;
                }
                break;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Cancela pedido de adição/remoção/alteração/troca de turma
 */
void Menu::cancelar_pedido(){
    int n;
    std::cout << "Qual o número do pedido que pretende cancelar?";
    std::cin >> n;

    while(std::cin.fail() || n < 1 || n > g->get_pedidos().size()) {
        if (n == -1) return;
        std::cout << "Input inválido" << '\n';
        std::cout << "Qual o número do pedido que pretende cancelar?";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> n;
    }
    g->cancelar_pedido(n);
    std::cout << "Pedido cancelado com sucesso\n";
}

/**
 * Apresenta ao utilizador as opções de estatísticas que podem ser visualizadas
 */
void Menu::ver_estatisticas(){
    int input;
    while (true) {
        std::cout << "\n============ Ver Estatísticas ============\n"
                     "Selecione o que pretende ver:\n"
                     "[1] Nº de estudantes numa turma\n"
                     "[2] Nº de estudantes numa UC\n"
                     "[3] Nº de estudantes num ano\n"
                     "[4] Nº de estudantes da L.EIC\n"
                     "[5] Nº de turmas numa UC\n"
                     "[6] Nº de pedidos efetuados\n"
                     "[-1] Voltar atrás\n";
        std::cin >> input;
        switch (input) {

            case 1: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                if (turma->get_estudantes().size() == 1) std::cout <<  "\nEstá inscrito 1 aluno nesta turma\n";
                else std::cout<< "\nEstão inscritos " << turma->get_estudantes().size() << " alunos nesta turma\n";
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                size_t total_alunos = 0;
                for (Turma* turma: uc){
                    total_alunos += turma->get_estudantes().size();
                }
                if (total_alunos == 1) std::cout <<  "\nEstá inscrito 1 aluno nesta UC\n";
                else std::cout<< "\nEstão inscritos " << total_alunos << " alunos nesta UC\n";
                break;
            }
            case 3: {
                int ano = validar_numero("Insira o ano: ");
                if (ano == -1) break;
                char a = ano + '0';
                int total_alunos = 0;
                for (Estudante* es : g->get_estudantes()){
                    for (Turma* turma: es->get_turmas()){
                        if (turma->get_codigo_turma().at(0) == a){
                            total_alunos++;
                            break;
                        }
                    }
                }
                if (total_alunos == 1) std::cout <<  "\nEstá inscrito 1 aluno no " << ano << "º ano\n";
                else std::cout<< "\nEstão inscritos " << total_alunos << " alunos no " << ano <<"º ano\n";
                break;
            }
            case 4: {
                std::cout<< "\nEstão inscritos " << g->get_estudantes().size() << " alunos na L.EIC\n";
                break;
            }
            case 5: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                std::cout<< "\nExistem " << uc.size() << " turmas nesta UC\n";
                break;
            }
            case 6: {
                size_t numero = g->get_pedidos().size();
                if (numero == 1) std::cout<< "\nFoi efetuado " << numero << " pedido\n";
                else std::cout<< "\nForam efetuados " << numero << " pedidos\n";
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Apresenta ao utilizador as opções de conteúdos que podem ser visualizados
 */
void Menu::ver_conteudos(){
    int input;
    while (true) {
        std::cout << "\n============ Visualizar Conteúdos ============\n"
                     "Selecione o que pretende ver:\n[1] Horários\n[2] Estudantes\n[3] Turmas\n[4] UC's\n[5] Pedidos\n[-1] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                ver_horarios();
                break;
            }
            case 2: {
                ver_estudantes();
                break;
            }
            case 3:{
                ver_turmas();
                break;
            }
            case 4:{
                for (std::vector<Turma* > uc: g->get_ucs()){
                    std::cout << uc.front()->get_codigo_uc() << '\n';
                }
                break;
            }
            case 5: {
                if (g->get_pedidos().empty()) std::cout << "Não há pedidos para mostrar\n";
                else {
                    int ordem = validar_opcao("Por que ordem prefere ver os pedidos?\n"
                                              "[1] Ordem de entrada\n"
                                              "[2] Tipo de pedido\n");
                    if (ordem == 0) return;
                    show_pedidos(ordem);
                }
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Mostra o horário de uma entidade, conforme o input do utilizador
 */
void Menu::ver_horarios(){
    int input;
    while (true) {
        std::cout << "\n============ Ver Horários ============\n"
                     "Pretende ver o horário de:\n[1] Uma turma\n[2] Uma UC\n[3] Um estudante\n[-1] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc,cod_turma);
                turma->show_horario_turma();
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                std::cout << '\n';
                show_horario_uc(uc);
                break;
            }
            case 3: {
                std::string cod_estudante = validar_numero_estudante("Selecione um estudante (número up): ");
                if (cod_estudante == "-1") break;
                Estudante* estudante = g->pesquisa_estudante(cod_estudante);
                std::cout << '\n';
                estudante->show_horario();
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Mostra os estudantes de uma entidade conforme o input do utilizador
 */
void Menu::ver_estudantes(){
    int input;
    while (true) {
        std::cout << "\n============ Ver Estudantes ============\n"
                     "Pretende ver os estudantes:\n"
                     "[1] De uma turma\n"
                     "[2] De uma UC\n"
                     "[3] De um ano\n"
                     "[4] Da L.EIC\n"
                     "[5] Com mais de n UC's\n"
                     "[-1] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                int ordem = validar_opcao("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                std::cout << '\n';
                turma->show_estudantes(ordem,ordem_c);
                std::cout << '\n';
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                int ordem = validar_opcao("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                std::cout << '\n';
                show_uc(uc, ordem,ordem_c);
                std::cout << '\n';
                break;
            }
            case 3: {
                int ano = validar_numero("Insira o ano: ");
                if (ano == -1) break;
                char a = ano+'0';
                int ordem = validar_opcao("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                std::cout << '\n';
                show_ano(a, ordem, ordem_c);
                std::cout << '\n';
                break;
            }
            case 4:{
                int ordem = validar_opcao("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                std::cout << '\n';
                if (ordem == 1){
                    std::set<Estudante*,Turma::cmp_nome> estudantes;
                    for (Estudante* es:g->get_estudantes()) {
                        estudantes.insert(es);
                    }
                    show_ordem_c(estudantes,ordem,ordem_c);
                }
                else{
                    show_ordem_c(g->get_estudantes(),ordem,ordem_c);
                }
                std::cout << '\n';
                break;
            }
            case 5:{
                int n;
                std::cout << "Insira o n: ";
                std::cin >> n;
                if (n == -1) break;
                while(std::cin.fail() || (n < 0)) {
                    std::cout << "Input inválido" << "\n";
                    std::cout << "Insira o n: ";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cin >> n;
                }
                int ordem = validar_numero("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n"
                                          "[3] Número de UC's\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                std::cout << '\n';
                show_estudantes_mais_de_n_ucs(n, ordem,ordem_c);
                std::cout << '\n';
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Mostra as turmas de uma entidade conforme o input do utilizador
 */
void Menu::ver_turmas(){
    int input;
    while (true) {
        std::cout << "\n============ Ver Turmas ============\n"
                     "Pretende ver as turmas:\n"
                     "[1] De um estudante\n"
                     "[2] De uma UC\n"
                     "[-1] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                std::string numero = validar_numero_estudante("Selecione um estudante (número up): ");
                if (numero == "-1") break;
                Estudante* estudante = g->pesquisa_estudante(numero);
                estudante->show_turmas();
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                for (Turma* turma : uc){
                    std::cout << turma->get_codigo_turma() << '\n';
                }
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Realiza pedido de adição/remoção/alteração/troca de turma
 */
void Menu::fazer_pedido(){
    std::cout << "\n============ Realizar Pedido ============\n";
    std::string numero = validar_numero_estudante("Selecione um estudante (número up): ");
    if (numero == "-1") return;
    Estudante* estudante = g->pesquisa_estudante(numero);
    while(true) {
        std::cout
                << "Que pedido pretende fazer:\n"
                   "[1] Adicionar a uma turma\n"
                   "[2] Remover de uma UC\n"
                   "[3] Alterar a turma de uma UC\n"
                   "[4] Trocar de turma com outro estudante\n"
                   "[-1] Voltar atrás\n";
        int input;
        std::cin >> input;

        switch (input) {
            case 1: {

                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);
                bool flag = true;
                for (auto turmss: estudante->get_turmas()){
                    if (turma == turmss) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    Pedido *pedido = new Pedido(input, turma, estudante);
                    g->adicionar_pedido(pedido);

                    std::cout << "\nPedido adicionado à fila\n\n";
                    }
                else{
                    std::cout << "\nERRO: O estudante já está nesta turma\n\n";
                }
                int v = validar_opcao("Pretende fazer outro pedido para o mesmo estudante?\n[1] Sim\n[2] Não\n");
                if (v == 1) continue;
                return;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                Turma* turma = nullptr;

                for (Turma* y : estudante->get_turmas()){
                    if (y->get_codigo_uc() == cod_uc){
                        turma = y;
                        break;
                    }
                }
                if (turma == nullptr){
                    std::cout << "\nERRO: O estudante não está inscrito nesta UC\n\n";
                    continue;
                }
                else {
                    Pedido *pedido = new Pedido(2, turma, estudante);
                    g->adicionar_pedido(pedido);
                    std::cout << "\nPedido adicinado à fila\n\n";
                    int v = validar_opcao("Pretende fazer outro pedido para o mesmo estudante?\n[1] Sim\n[2] Não\n");
                    if (v == 1){
                        continue;
                    }
                }
                return;

            }
            case 3: {

                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Pedido *pedido = new Pedido(input, turma, estudante);
                g->adicionar_pedido(pedido);
                std::cout << "\nPedido adicionado à fila\n\n";
                int v = validar_opcao("Pretende fazer outro pedido para o mesmo estudante?\n[1] Sim\n[2] Não\n");
                if (v == 1){
                    continue;
                }
                return;
            }
            case 4: {
                std::string numero_troca = validar_numero_estudante("Selecione o estudante com quem pretende trocar: ");
                if (numero_troca == "-1") break;
                Estudante *estudante_troca = g->pesquisa_estudante(numero_troca);
                if(estudante_troca == estudante){
                    std::cout << "\nERRO: Não pode trocar de turma com o mesmo estudante\n\n";
                    continue;
                }
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                Turma* ptr = new Turma(cod_uc);
                Pedido *pedido = new Pedido(input, ptr, estudante, estudante_troca);
                g->adicionar_pedido(pedido);
                std::cout << "\nPedido adicionado à fila\n\n";
                int v = validar_opcao("Pretende fazer outro pedido para o mesmo estudante?\n[1] Sim\n[2] Não\n");
                if (v == 1){
                    continue;
                }
                return;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

/**
 * Termina a execução
 */
void Menu::fim(){
    std::cout << "\n============ Terminar ============\n";
    if (!g->get_pedidos().empty()){
        g->gerir_pedidos();
        if (g->get_pedidos_falhados().empty()) std::cout << "Todos os pedidos foram efetuados com sucesso!\n\n";
        else {
            std::cout << "Pedidos por realizar: " << g->get_pedidos_falhados().size() << "\n\n";
            oportunidade();
        }
        int opcao = validar_opcao("Pretende guardar permanentemente as suas alterações?\n[1] Sim\n[2] Não\n");
        while (opcao == -1){
            std::cout << "Nem sempre se pode voltar atrás :(\n";
            opcao = validar_opcao("Pretende guardar permanentemente as suas alterações?\n[1] Sim\n[2] Não\n");
        }
        if (opcao == 1) {
            g->atualiza_estudantes();
            g->arquivo_pedidos();
        }
    }
}

/**
 * Dá a oportunidade ao utlizador de alterar as configurações antes de terminar a execução
 */
void Menu::oportunidade(){
    std::list<Pedido*> lista_original = g->get_pedidos_falhados();
    std::list<Pedido*> pedidos_desequilibro;
    for (Pedido* p: g->get_pedidos_falhados()){
        if (p->get_tipo() == 1){
            if(g->pode_adicionar_turma(p->get_estudante1(), p->get_turma()) && g->erro_desequilibrio(p)){
                pedidos_desequilibro.push_back(p);
                g->remover_pedido_falhado(p);}
        }
        else if (p->get_tipo() == 3){
            if(g->pode_alterar_turma(p->get_estudante1(), p->get_turma()) && g->erro_desequilibrio(p)){
                pedidos_desequilibro.push_back(p);
                g->remover_pedido_falhado(p);}
        }
    }

    if (pedidos_desequilibro.empty()) return;
    if (pedidos_desequilibro.size() == 1){
        std::cout << "O seguinte pedido não foi satisfeito devido ao limite de desequilíbrio definido entre as turmas:\n";
    }
    else  std::cout << "Os seguintes pedidos não foram satisfeitos devido ao limite de desequilíbrio definido entre as turmas:\n";
    for (Pedido* pedido: pedidos_desequilibro){
        std::cout << Pedido::tipos[pedido->get_tipo()] << ": " ;
        if (pedido->get_tipo() == 4){
            pedido->get_estudante1()->show(1);
            std::cout << " | " ;
            pedido->get_estudante2()->show(1);
            std::cout << " -> " << pedido->get_turma()->get_codigo_uc() << '\n';
        }
        else {
            pedido->get_estudante1()->show(1);
            std::cout << " -> " << pedido->get_turma()->get_codigo_uc() << " | "
                      << pedido->get_turma()->get_codigo_turma() << '\n';
        }
    }
    std::cout << '\n';
    int x = validar_opcao("Deseja mudar as configurações e tentar novamente?\n[1] Sim\n[2] Não\n");
    if (x == 1){
       configuracoes();
        for(Pedido* pedido: pedidos_desequilibro){
            g->processar_pedido(pedido);
        }
        if (g->get_pedidos_falhados().empty()) std::cout << "Todos os pedidos foram efetuados com sucesso!\n\n";
        else {
            std::cout << "Pedidos por realizar após ter alterado as configurações: " << g->get_pedidos_falhados().size() << "\n\n";
        }
    }
    else{
        g->set_pedidos_falhados(lista_original);
    }

}

/**
 * Mostra os estudantes inscritos numa uc
 * @param uc
 * @param ordem (1) alfabética / (2) numérica
 * @param ordem_c (1) crescente / (2) decrescente
 */
void Menu::show_uc(const std::vector<Turma*>& uc, int ordem, int ordem_c){
    if (ordem == 1){
        std::set<Estudante*,Turma::cmp_nome> estudantes;
        for (Turma* turma: uc) {
            for (Estudante* es: turma->get_estudantes()) estudantes.insert(es);
        }
        show_ordem_c(estudantes,ordem,ordem_c);
    }
    else {
        std::set<Estudante*,Turma::cmp_codigo> estudantes;
        for (Turma* turma: uc) {
            for (Estudante* es: turma->get_estudantes()) estudantes.insert(es);
        }
        show_ordem_c(estudantes,ordem,ordem_c);
    }
}

/**
 * Mostra os estudantes inscritos num ano
 * @param ano (1) / (2) / (3)
 * @param ordem (1) alfabética / (2) numérica
 * @param ordem_c (1) crescente / (2) decrescente
 */
void Menu::show_ano(char a, int ordem, int ordem_c){
    if (ordem == 1) {
        std::set<Estudante*, Turma::cmp_nome> estudantes;
        for (Estudante* es : g->get_estudantes()){
            for (Turma* turma: es->get_turmas()){
                if (turma->get_codigo_turma().at(0) == a){
                    estudantes.insert(es);
                    break;
                }
            }
        }
        show_ordem_c(estudantes,ordem,ordem_c);
    }
    else{
        std::set<Estudante *, Turma::cmp_codigo> estudantes;
        for (Estudante* es : g->get_estudantes()){
            for (Turma* turma: es->get_turmas()){
                if (turma->get_codigo_turma().at(0) == a){
                    estudantes.insert(es);
                    break;
                }
            }
        }
        show_ordem_c(estudantes,ordem,ordem_c);
    }
}

/**
 * Mostra os estudantes com mais que n ucs
 * @param n nº de ucs
 * @param ordem (1) alfabética / (2) numérica / (3) nº de ucs
 * @param ordem_c (1) crescente / (2) decrescente
 */
void Menu::show_estudantes_mais_de_n_ucs(int n, int ordem, int ordem_c){
    switch (ordem) {
        case 1: {
            std::set<Estudante*, Turma::cmp_nome> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            if (es.empty()){
                std::cout << "Não existem estudantes com mais de " << n << " UC's\n";
                break;
            }
            show_ordem_c(es,ordem,ordem_c,1);
            break;
        }
        case 2:{
            std::set<Estudante*, Turma::cmp_codigo> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            if (es.empty()){
                std::cout << "Não existem estudantes com mais de " << n << " UC's\n";
                break;
            }
            show_ordem_c(es,ordem,ordem_c,1);
            break;
        }
        case 3:{
            std::set<Estudante*, Turma::cmp_nr_uc> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            if (es.empty()){
                std::cout << "Não existem estudantes com mais de " << n << " UC's\n";
                break;
            }
            show_ordem_c(es,ordem,ordem_c,1);
            break;
        }
    }
}

/**
 * Mostra os pedidos por processar
 * @param ordem (1) Ordem de entrada / (2) Tipo de pedido
 */
void Menu::show_pedidos(int ordem){
    std::queue<Pedido*> fila_temp = g->get_pedidos();
    std::vector<Pedido*> v_pedidos;
    unsigned initial_size = g->get_pedidos().size();
    for (unsigned i = 0; i < initial_size; i++) {
        Pedido *p = fila_temp.front();
        if (ordem == 1) {
            if (p->get_tipo() == 4){
                std::cout << "Pedido nº " << i+1 <<" -> "<<Pedido::tipos[p->get_tipo()] << ": " ;
                p->get_estudante1()->show(1);
                std::cout << " | " ;
                p->get_estudante2()->show(1);
                std::cout << " -> " << p->get_turma()->get_codigo_uc() << '\n';
            }
            else{
                std::cout << "Pedido nº " << i+1 <<" -> "<<Pedido::tipos[p->get_tipo()] << ": " ;
                p->get_estudante1()->show(1);
                std::cout << " -> " << p->get_turma()->get_codigo_uc() << " | " << p->get_turma()->get_codigo_turma() << '\n';
            }
        }
        v_pedidos.push_back(p);
        fila_temp.pop();
    }
    if (ordem == 2) {
        sort(v_pedidos.begin(), v_pedidos.end(), Pedido::cmp);
        auto it = v_pedidos.begin();
        int tipo_atual = (*it)->get_tipo();
        std::cout << Pedido::tipos[(*it)->get_tipo()] << ":\n";
        while (it != v_pedidos.end()){
            if ((*it)->get_tipo() == tipo_atual){
                if ((*it)->get_tipo() == 4){
                    (*it)->get_estudante1()->show(1);
                    std::cout << " | " ;
                    (*it)->get_estudante2()->show(1);
                    std::cout << " -> " << (*it)->get_turma()->get_codigo_uc() << "\n";}
                else {
                    (*it)->get_estudante1()->show(1);
                    std::cout << " -> " << (*it)->get_turma()->get_codigo_uc() << " | "
                              << (*it)->get_turma()->get_codigo_turma() << '\n';
                }}
            else {
                tipo_atual = (*it)->get_tipo();
                std::cout << Pedido::tipos[(*it)->get_tipo()] << ":\n";
                if ((*it)->get_tipo() == 4){
                    (*it)->get_estudante1()->show(1);
                    std::cout << " | " ;
                    (*it)->get_estudante2()->show(1);
                    std::cout << " -> " << (*it)->get_turma()->get_codigo_uc() << '\n';
                }
                else {
                    (*it)->get_estudante1()->show(1);
                    std::cout << " -> " << (*it)->get_turma()->get_codigo_uc() << " | "
                              << (*it)->get_turma()->get_codigo_turma() << '\n';
                }
            }
            it++;
        }
    }

}

/**
 * Mostra o horário da uc
 * @param uc
 */
void Menu::show_horario_uc(const std::vector<Turma*>& uc) {
    std::vector<Aula *> aulas;
    for (Turma *turma: uc) {
        for (Aula *aula: turma->get_aulas()) {
            aulas.push_back(aula);
        }
    }
    sort(aulas.begin(), aulas.end(), Aula::cmp);

    int dia_atual = 0;
    std::string tipo_atual;
    double hora = 0;
    for (Aula* aula: aulas){
        Aula* x = aula;
        if (Aula::dias[aula->get_dia_semana()] != dia_atual){
            dia_atual = Aula::dias[aula->get_dia_semana()];
            std::cout << '\n' << Aula::portugues[aula->get_dia_semana()] << ":";
            tipo_atual = "";
            hora = 0;
        }
        if (aula->get_hora_inicio() != hora || aula->get_tipo() != tipo_atual){
            tipo_atual = aula->get_tipo();
            hora = aula->get_hora_inicio();
            std::cout << '\n';
            aula->show();
            std::cout << " | " << aula->get_codigo_turma();
        }
        else {
            std::cout << " | " << aula->get_codigo_turma() ;
        }
    }
        std::cout << '\n';
    }

/**
 * Valida o código_uc dado como input
 * @return o código_uc de uma uc
 */
std::string Menu::validar_codigo_uc(){
    std::string cod_uc;
    std::cout<< "Insira o código da UC:";
    std::cin >> cod_uc;

    while(std::cin.fail() || (cod_uc != "UP001" && cod_uc.size() != 8) || g->pesquisa_uc(cod_uc).empty()) {
        if (cod_uc == "-1") return cod_uc;
        std::cout << "Input inválido" << '\n';
        std::cout << "Insira o código da UC:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_uc;
    }
    return cod_uc;
}

/**
 * Valida o código_turma dado como input
 * @param cod_uc codigo_uc da turma a validar
 * @return o código_turma de uma turma da uc
 */
std::string Menu::validar_codigo_turma(const std::string& cod_uc){
    std::string cod_turma;
    std::cout<< "Insira o código da turma:";
    std::cin >> cod_turma;

    while(std::cin.fail() || cod_turma.size() != 7 || g->pesquisa_turma(cod_uc,cod_turma) == nullptr) {
        if (cod_turma == "-1") return cod_turma;
        std::cout << "Input inválido" << '\n';
        std::cout << "Insira o código da turma:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_turma;
    }
    return cod_turma;
}

/**
 * Valida o número de estudante dado como input
 * @param mensagem mensagem a mostrar
 * @return o número de um estudante
 */
std::string Menu::validar_numero_estudante(const std::string& mensagem){
    std::string numero;
    std::cout<< mensagem;
    std::cin >> numero;

    while(std::cin.fail() || g->pesquisa_estudante(numero) == nullptr) {
        if (numero == "-1") return numero;
        std::cout << "Input inválido" << '\n';
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> numero;
    }
    return numero;
}

/**
 * Valida o número dado como input
 * @param mensagem mensagem a mostrar
 * @return opção escolhida (-1) / (1) / (2) / (3)
 */
int Menu::validar_numero(const std::string& mensagem){
    int numero;
    std::cout<< mensagem;
    std::cin >> numero;

    while(std::cin.fail() || (numero !=1 && numero !=2 && numero != 3)) {
        if (numero == -1) return numero;
        std::cout << "Input inválido" << '\n';
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> numero;
    }
    return numero;
}

/**
 * Valida a opção dada como input
 * @param mensagem mensagem a mostrar
 * @return opção escolhida (-1) / (1) / (2)
 */
int Menu::validar_opcao(const std::string& mensagem){
    int opcao;
    std::cout << mensagem;
    std::cin >> opcao;

    while(std::cin.fail() || (opcao != 1 && opcao != 2)) {
        if (opcao == -1) return -1;
        std::cout << "Input inválido" << '\n';
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> opcao;
    }
    return opcao;
}

/**
 * Mostra os estudantes ordenados
 * @tparam T BST de estudantes
 * @param es BST de estudantes
 * @param ordem (1) alfabética / (2) numérica
 * @param ordem_c (1) crescente / (2) decrescente
 * @param n_ucs (1) mostra o nº de UC's do estudante
 */
template <typename T>
void Menu::show_ordem_c(T es, int ordem, int ordem_c, int n_ucs){

    if (ordem_c == 1) {
        for (Estudante* estudante: es) {
            estudante->show(ordem);
            if (n_ucs==1) std::cout << " -> nº de UC's: " << estudante->get_turmas().size();
            std::cout << '\n';
        }
    }
    else{
        for (auto it = es.rbegin(); it !=es.rend(); it++){
            (*it)->show(ordem);
            if (n_ucs==1) std::cout << " -> nº de UC's: " << (*it)->get_turmas().size();
            std::cout << '\n';
        }
    }
    }

/**
 * Permite que o utilizador altere as configurações de capacidade e desequilíbrio entre turmas
 */
void Menu::configuracoes(){
    int input;
    while (true){
        std::cout <<
        "\n============ Alterar Configurações ============\n"
        "O que pretende alterar?\n"
        "[1] Capacidade máxima de estudantes por turma\n"
        "[2] Desequilíbrio (maior diferença do nº de estudantes) entre turmas de uma UC\n"
        "[-1] Voltar atrás\n";
        std::cin >> input;

        switch (input) {
            case 1: {
                int nova_cap_max;
                std::cout << "Capacidade máxima atual: " << Turma::capacidade_maxima;
                std::cout << "\nNova capacidade máxima: ";
                std::cin >> nova_cap_max;
                while(std::cin.fail() || (nova_cap_max < 0)) {
                    if (nova_cap_max == -1) return;
                    std::cout << "Input inválido" << '\n';
                    std::cout << "Nova capacidade máxima: ";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cin >> nova_cap_max;
                }

                Turma::set_capacidade_maxima(nova_cap_max);
                std::cout << "\n";

                break;
            }
            case 2: {

                int novo_desequilibrio;
                std::cout << "Desequilíbrio atual: " << Gestao::desequilibrio;
                std::cout << "\nNovo desequilibrio: ";
                std::cin >> novo_desequilibrio;
                while(std::cin.fail() || (novo_desequilibrio < 0)) {
                    if (novo_desequilibrio == -1) return;
                    std::cout << "Input inválido" << '\n';
                    std::cout << "Novo desequilibrio: ";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cin >> novo_desequilibrio;
                }

                Gestao::set_desequilibrio(novo_desequilibrio);
                std::cout << "\n";
                break;
            }
            case -1: {
                return;
            }
            default: {
                std::cout << "Input Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

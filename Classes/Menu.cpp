#include <climits>
#include "Menu.h"
/**
 * Construtor da classe Menu
 */
Menu::Menu(){
    std::cout << "Bem-vindo!\n"
                 "[Pressione -1 sempre que tencione voltar para trás]\n";

    std::ifstream myfile;
    myfile.open ("C:/AED/Projeto_AED-master/CSV files/new_students_classes.csv");
    if (myfile.is_open()){
        myfile.close();
        int n = validar_opcao("\nPretende utilizar os dados do ficheiro:\n[1] Inicial\n[2] Atualizado\n");
        g = new Gestao(n);
    }
    else g = new Gestao(1);
}
/**
 *
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
                     "[5] Terminar\n";
        std::cin >> input;
        switch (input) {
            case -1: {
                std::cout << "Ainda não encontramos a máquina do tempo :(\n";
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
                int opcao = validar_opcao("Tem a certeza que pretende terminar? [A sua ação é irreversível]\n[1] Sim\n[2] Não\n");
                if (opcao == 1) {
                    fim();
                    std::cout << "Até à próxima!\nAss: G67";
                    return;
                }
                break;
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

void Menu::cancelar_pedido(){
    int n;
    std::cout << "Qual o número do pedido que pretende cancelar?";
    std::cin >> n;

    while(std::cin.fail() || n < 1 || n > g->get_pedidos().size()) {
        if (n == -1) return;
        std::cout << "Input inválido" << std::endl;
        std::cout << "Qual o número do pedido que pretende cancelar?";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> n;
    }
    g->cancelar_pedido(n);
    std::cout << "Pedido cancelado com sucesso\n";
}

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
                std::cout<< "Estão inscritos " << turma->get_estudantes().size() << " alunos nesta turma\n";
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                int total_alunos = 0;
                for (auto turma: uc){
                    total_alunos += turma->get_estudantes().size();
                }
                std::cout<< "Estão inscritos " << total_alunos << " alunos nesta UC\n";
                break;
            }
            case 3: {
                int ano = validar_numero("Insira o ano:");
                if (ano == -1) break;
                char a = ano + '0';
                int total_alunos = 0;
                for (auto es : g->get_estudantes()){
                    for (auto turma: es->get_turmas()){
                        if (turma->get_codigo_turma().at(0) == a){
                            total_alunos++;
                            break;
                        }
                    }
                }


                std::cout<< "Estão inscritos " << total_alunos << " alunos no " << ano <<"º ano\n";
                break;
            }
            case 4: {
                std::cout<< "Estão inscritos " << g->get_estudantes().size() << " alunos na L.EIC\n";
                break;
            }
            case 5: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                std::cout<< "Existem " << uc.size() << " turmas nesta UC\n";
                break;
            }
            case 6: {
                int numero = g->get_pedidos().size();
                if (numero == 1) std::cout<< "Foi efetuado " << numero << " pedido\n";
                else std::cout<< "Foram efetuados " << numero << " pedidos\n";
                break;
            }
            case -1: {
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
                std::cout << "Caractere Inválido\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
}

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
                show_horario_uc(uc);
                break;
            }
            case 3: {
                std::string cod_estudante = validar_numero_estudante("Insira o número up:");
                if (cod_estudante == "-1") break;
                Estudante* estudante = g->pesquisa_estudante(cod_estudante);
                estudante->show_horario();
                break;
            }
            case -1: {
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
                show_uc(uc, ordem,ordem_c);
                std::cout << '\n';
                break;
            }
            case 3: {
                int ano = validar_numero("Insira o ano:");
                if (ano == -1) break;
                char a = ano+'0';
                int ordem = validar_opcao("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n");
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
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
                std::cout << "Insira o n:";
                std::cin >> n;
                if (n == -1) break;
                while(std::cin.fail() || (n < 0)) {
                    std::cout << "Input inválido" << "\n";
                    std::cout << "Insira o n:";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cin >> n;
                }
                int ordem = validar_numero("\nPor que ordem prefere ver os estudantes?\n"
                                          "[1] Alfabética\n"
                                          "[2] Numérica\n"
                                          "[3] Número de UC's\n")-'0';
                if (ordem == -1) break;
                int ordem_c = validar_opcao("Escolha o método de ordenação:\n[1] Crescente\n[2] Decrescente\n");
                if (ordem_c == -1) break;
                show_estudantes_mais_que_n_ucs(n, ordem,ordem_c);
                std::cout << '\n';
                break;
            }
            case -1: {
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
/**
 *
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
                std::string numero = validar_numero_estudante("Selecione um estudante:");
                if (numero == "-1") break;
                Estudante* estudante = g->pesquisa_estudante(numero);
                estudante->show_turmas();
                std::cout << '\n';
                break;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::vector<Turma*> uc = g->pesquisa_uc(cod_uc);
                for (auto turma : uc){
                    std::cout << turma->get_codigo_turma() << '\n';
                }
                break;
            }
            case -1: {
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
/**
 *
 * Complexidade: O(m log(n)), n-> tamanho do vetor das ucs, m-> nº de inputs
 */
void Menu::fazer_pedido(){
    std::cout << "\n============ Realizar Pedido ============\n";
    std::string numero = validar_numero_estudante("Selecione um estudante:");
    if (numero == "-1") return;
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
        Estudante* estudante = g->pesquisa_estudante(numero);
        switch (input) {
            case 1: {

                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Pedido *pedido = new Pedido(input, turma, estudante);
                g->adicionar_pedido(pedido);

                std::cout << "\nPedido adicionado à fila\n";

                return;
            }
            case 2: {
                std::string cod_uc = validar_codigo_uc();
                if (cod_uc == "-1") break;
                Turma* turma = nullptr;

                for (auto y : estudante->get_turmas()){
                    if (y->get_codigo_uc() == cod_uc){
                        turma = y;
                        break;
                    }
                }
                if (turma == nullptr){
                    std::cout << "\nERRO: O estudante não está inscrito nesta UC\n";}
                else {
                    Pedido *pedido = new Pedido(2, turma, estudante);
                    g->adicionar_pedido(pedido);
                    std::cout << "\nPedido adicinado à fila\n";
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
                    std::cout << "\nPedido adicionado à fila\n";
                return;
            }
            case 4: {
                std::string numero_troca = validar_numero_estudante("Selecione o estudante com quem pretende trocar:\n");
                if (numero_troca == "-1") break;
                Estudante *estudante_troca = g->pesquisa_estudante(numero_troca);
                if(estudante_troca == estudante){
                    std::cout << "\nERRO: Não pode trocar de turma com o mesmo estudante\n";
                    return;
                }
                std::string cod_uc = validar_codigo_uc();

                std::string cod_turma = validar_codigo_turma(cod_uc);
                if (cod_turma == "-1") break;
                Turma* turma = g->pesquisa_turma(cod_uc, cod_turma);

                Pedido *pedido = new Pedido(input, turma, estudante, estudante_troca);
                g->adicionar_pedido(pedido);
                std::cout << "\nPedido adicionado à fila\n";
                return;
            }
            case -1: {
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

/**
 * Terminar execução
 * Complexidade: O(n*m*l*k), n -> nº total de pedidos, m -> nº de pedidos falhados, l -> tamanho do vetor das aulas do estudante, k -> tamanho do vetor das aulas da turma
 */
void Menu::fim(){
    std::cout << "\n============ Terminar ============\n";
    if (!g->get_pedidos().empty()){
        g->gerir_pedidos();
        if (g->get_pedidos_falhados().empty()) std::cout << "Todos os pedidos foram efetuados com sucesso!\n\n";
        else std::cout << "Pedidos por realizar: " << g->get_pedidos_falhados().size() << "\n\n";
        int opcao = validar_opcao("Pretende guardar permanentemente as suas alterações?\n[1] Sim\n[2] Não\n");
        while (opcao == -1){
            std::cout << "Nem sempre se pode voltar atrás :(\n";
            opcao = validar_opcao("Pretende guardar permanentemente as suas alterações?\n[1] Sim\n[2] Não\n");
        }
        if (opcao == 1) {
            g->atualiza_estudantes();
            if (!g->get_pedidos_falhados().empty()) g->arquivo_pedidos();
        }
    }
}

/**
 * Mostra os estudantes inscritos numa uc
 * Complexidade: O(n*m*log(l)), n -> nº de turmas da uc, m -> nº de estudantes de cada turma, l -> nº de estudantes da uc
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
        show_ordem_c(g->get_estudantes(),ordem,ordem_c);
    }
}

/**
 * Mostra os estudantes inscritos num ano
 * Complexidade: O(n*m*log(l)), n -> nº de estudantes, m -> nº de turmas de cada estudantes, l -> nº de estudantes do ano a
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
 * Complexidade: O(n log(m)), n -> nº de estudantes, m -> nº de estudantes com mais que n ucs
 * @param n nº de ucs
 * @param ordem (1) alfabética / (2) numérica / (3) nº de ucs
 * @param ordem_c (1) crescente / (2) decrescente
 */
void Menu::show_estudantes_mais_que_n_ucs(int n, int ordem, int ordem_c){
    switch (ordem) {
        case 1: {
            std::set<Estudante*, Turma::cmp_nome> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            show_ordem_c(es,ordem,ordem_c);
            break;
        }
        case 2:{
            std::set<Estudante*, Turma::cmp_codigo> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            show_ordem_c(es,ordem,ordem_c);
            break;
        }
        case 3:{
            std::set<Estudante*, Turma::cmp_nr_uc> es;
            for (Estudante* estudante: g->get_estudantes()) {
                if (estudante->get_turmas().size() > n) {
                    es.insert(estudante);
                }
            }
            show_ordem_c(es,ordem,ordem_c);
            break;
        }
    }

}

/**
 * Mostra os pedidos por processar
 * Complexidade: O(n log(n)), n -> nº de pedidos
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
        auto tipo_atual = (*it)->get_tipo();
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
 * Complexidade: O(n*m*log(n*m)), n-> nª de turmas da uc, m -> nª de aulas da turma
 * @param uc
 */
void Menu::show_horario_uc(const std::vector<Turma*>& uc){

    std::set<Aula*,Aula::cmp_aula> aulas;
    for (Turma* turma: uc){
        for (Aula* aula: turma->get_aulas()){
            aulas.insert(aula);
        }
    }
    auto it = aulas.begin();
    int dia_atual = Aula::dias[(*it)->get_dia_semana()];
    std::cout << Aula::portugues[(*it)->get_dia_semana()] << ":\n";
    while (it != aulas.end()){
        if (Aula::dias[(*it)->get_dia_semana()] != dia_atual) {
            dia_atual = Aula::dias[(*it)->get_dia_semana()];
            std::cout << Aula::portugues[(*it)->get_dia_semana()] << ":\n";
        }
        (*it)->show();
        std::cout << " | " << (*it)->get_codigo_turma() << '\n';
        it++;
        }
    }

/**
 * Valida o código_uc dado como input
 * Complexidade: O(m log(n)), n-> tamanho do vetor das ucs, m-> nº de inputs
 * @return o código_uc de uma uc
 */
std::string Menu::validar_codigo_uc(){
    std::string cod_uc;
    std::cout<< "Insira o código da UC:";
    std::cin >> cod_uc;

    while(std::cin.fail() || g->pesquisa_uc(cod_uc).empty()) {
        if (cod_uc == "-1") return cod_uc;
        std::cout << "Input inválido" << std::endl;
        std::cout << "Insira o código da UC:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_uc;
    }
    return cod_uc;
}

/**
 * Valida o código_turma dado como input
 * Complexidade: O(m log(n)), n-> tamanho do vetor das turmas, m-> nº de inputs
 * @param cod_uc codigo_uc da turma a validar
 * @return o código_turma de uma turma da uc
 */
std::string Menu::validar_codigo_turma(const std::string& cod_uc){
    std::string cod_turma;
    std::cout<< "Insira o código da turma:";
    std::cin >> cod_turma;

    while(std::cin.fail() || g->pesquisa_turma(cod_uc,cod_turma) == nullptr) {
        if (cod_turma == "-1") return cod_turma;
        std::cout << "Input inválido" << std::endl;
        std::cout << "Insira o código da turma:";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> cod_turma;
    }
    return cod_turma;
}
/**
 * Valida o número de estudante dado como input
 * Complexidade: O(m log(n)), n-> tamanho da BST de estudantes, m-> nº de inputs
 * @param mensagem mensagem a mostrar
 * @return o número de um estudante
 */
std::string Menu::validar_numero_estudante(const std::string& mensagem){
    std::string numero;
    std::cout<< mensagem;
    std::cin >> numero;

    while(std::cin.fail() || g->pesquisa_estudante(numero) == nullptr) {
        if (numero == "-1") return numero;
        std::cout << "Input inválido" << std::endl;
        std::cout << mensagem;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> numero;
    }
    return numero;
}
/**
 * Valida o número dado como input
 * Complexidade: O(n), n -> nº de inputs
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
 * Complexidade: O(n), n -> nº de inputs
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
 * Complexidade: O(n), n -> tamanho da estrutura T
 * @tparam T BST de estudantes
 * @param es BST de estudantes
 * @param ordem (1) alfabética / (2) numérica
 * @param ordem_c (1) crescente / (2) decrescente
 */
template <typename T>
void Menu::show_ordem_c(T es, int ordem, int ordem_c){
    if (ordem_c == 1) {
        for (Estudante* estudante: es) {
            estudante->show(ordem);
            std::cout << std::endl;
        }
    }
    else{
        for (auto it = es.rbegin(); it !=es.rend(); it++){
            (*it)->show(ordem);
            std::cout << std::endl;
        }
    }
}

//
// Created by athos on 31/10/2022.
//

#include "Gestao.h"
/**
 * Construtor da classe Gestao. Criação dos vetores aulas, turmas, uc e da BST estudantes
 */
Gestao::Gestao(){
    criacao_aulas();
    criacao_turmas();
    criacao_estudantes();
    criacao_uc();
}
/**
 * Leitura do ficheiro classes.csv e criação das aulas, armazenando-os no vetor aulas
 */
void Gestao::criacao_aulas(){

    std::string CurrentLine, x, codigo_turma, codigo_uc, dia_semana, tipo;
    double hora_inicio, duracao;
    std::ifstream myFile;

    myFile.open("C:/AED/Projeto_AED-master/CSV files/classes.csv");
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
}
/**
 * Leitura do ficheiro classes_per_uc.csv e criação das turmas, armazenando-os no vetor turmas.
 * Atribuição das aulas à sua respetiva turma.
 */
void Gestao::criacao_turmas(){
    std::string CurrentLine, codigo_uc, codigo_turma;
    std::ifstream myFile;

    myFile.open("C:/AED/Projeto_AED-master/CSV files/classes_per_uc.csv");
    getline(myFile,CurrentLine);

    while(getline(myFile,CurrentLine)){

        std::istringstream iss(CurrentLine);

        getline(iss,codigo_uc,',');
        getline(iss,codigo_turma,',');  if (codigo_turma.back() == '\r') codigo_turma.pop_back();

        Turma* ptr = new Turma(codigo_uc,codigo_turma);
        turmas.push_back(ptr);
    }
    for (Aula* aula : aulas){
        Turma* turma = pesquisa_turma(aula->get_codigo_uc(),aula->get_codigo_turma());
        turma->adicionar_aula(aula);
    }

}
/**
 * Leitura do ficheiro students_classes.csv e criação dos estudantes, armazenando-os na BST estudantes.
 * Atribuição das turmas a cada estudante.
 */
void Gestao::criacao_estudantes(){
    std::ifstream myFile;
    std::string CurrentLine, codigo, nome, codigo_uc, codigo_turma;
    myFile.open("C:/AED/Projeto_AED-master/CSV files/new_students_classes.csv");
    if (!myFile.is_open()) myFile.open("C:/AED/Projeto_AED-master/CSV files/students_classes.csv");
    getline(myFile,CurrentLine);
    getline(myFile,CurrentLine);
    std::istringstream iss(CurrentLine);

    getline(iss,codigo,',');
    getline(iss,nome,',');
    getline(iss,codigo_uc,',');
    getline(iss,codigo_turma,',');  if (codigo_turma.back() == '\r') codigo_turma.pop_back();

    Estudante* estudante_atual = new Estudante(codigo,nome);

    Turma * turma = pesquisa_turma(codigo_uc,codigo_turma);
    estudante_atual->adicionar_turma(turma);

    while(getline(myFile,CurrentLine)){

        std::istringstream iss1(CurrentLine);

        getline(iss1,codigo,',');
        getline(iss1,nome,',');
        getline(iss1,codigo_uc,',');
        getline(iss1,codigo_turma,',');  if (codigo_turma.back() == '\r') codigo_turma.pop_back();

        if (codigo == estudante_atual->get_codigo()){
            Turma * turma = pesquisa_turma(codigo_uc,codigo_turma);
            estudante_atual->adicionar_turma(turma);
        }

        else{
            estudantes.insert(estudante_atual);

            Estudante* estudante_novo = new Estudante(codigo,nome);
            estudante_atual = estudante_novo;

            Turma * turma = pesquisa_turma(codigo_uc, codigo_turma);
            estudante_novo->adicionar_turma(turma);
        }
    estudantes.insert(estudante_atual);
    }
}
/**
 * Criação de todas as ucs existentes
 */
void Gestao::criacao_uc(){

    std::vector<Turma*> uc;
    std::string codigo_uc = "L.EIC001";
    for (auto turma : turmas){
        if (turma->get_codigo_uc() == codigo_uc){
            uc.push_back(turma);
        }
        else{
            ucs.push_back(uc);
            codigo_uc = turma->get_codigo_uc();
            uc.clear();
            uc.push_back(turma);
        }
    }
    ucs.push_back(uc);
}
/**
 * Procura no vetor turmas a turma que apresenta código_uc e código_turma ...
 * @param codigo_uc
 * @param codigo_turma
 * @return
 */
Turma* Gestao::pesquisa_turma(std::string codigo_uc, std::string codigo_turma){
    for (auto turma : turmas){
        if (turma->get_codigo_turma() == codigo_turma && turma->get_codigo_uc() == codigo_uc){
            return turma;
        }
    }
    return nullptr;

}
/**
 * Procura no vetor ucs a uc (vetor de turmas) que apresenta código_uc ...
 * @param codigo_uc
 * @return
 */
std::vector<Turma*> Gestao::pesquisa_uc(std::string codigo_uc){
    for (auto uc: ucs){
        if (uc.front()->get_codigo_uc() == codigo_uc){
            return uc;
        }
    }
    return {};
}
/**
 * Procura na BST estudantes o estudante que apresenta numero up ...
 * @param nome
 * @return
 */
Estudante* Gestao::pesquisa_estudante(std::string numero){
    for (auto e: estudantes){
        if (e->get_codigo() == numero){
            return e;
        }
    }
    return nullptr;
}
/**
 * Verifica se se pode adicionar a turma t ao estudante es
 * @param es
 * @param t
 * @return
 */
bool Gestao::pode_adicionar_turma(Estudante* es, Turma* t){
    t->set_capacidade(t->get_capacidade_atual()+1);
    if (t->get_capacidade_atual() > Turma::capacidade_maxima || max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= 4) {
        return false;
    }
    t->set_capacidade(t->get_capacidade_atual()-1);
    return es->compativel(t);
}
/**
 * Verifica se o estudante es se pode alterar para a turma ...
 * @param es
 * @param turma
 * @return
 */
bool Gestao::pode_alterar_turma(Estudante* es, Turma* turma){
    Turma* turma_com_mesmo_uc = nullptr;
    bool flag = false;
    for (auto turma_estudante: es->get_turmas()){
        if (turma_estudante->get_codigo_uc() == turma->get_codigo_uc()){
            turma_com_mesmo_uc = turma_estudante;
            es->remover_da_turma(turma_com_mesmo_uc);
            if(es->compativel(turma)) flag = true;
            break;
        }
    }
    if (turma_com_mesmo_uc != nullptr){
        turma->set_capacidade(turma->get_capacidade_atual()+1);
        if (turma->get_capacidade_atual() > Turma::capacidade_maxima || max_diferenca(pesquisa_uc(turma->get_codigo_uc())) >= 4) {
            flag = false;
        }
        turma->set_capacidade(turma->get_capacidade_atual()-1);
        es->adicionar_turma(turma_com_mesmo_uc);
    }
    return flag;
}

void Gestao::adicionar_pedido(Pedido* pedido) {pedidos.push(pedido);}

bool Gestao::pode_remover_turma(Estudante* es, Turma* turma){
    for (auto t:es->get_turmas()){
        if (t == turma){
            return true;
        }
    }
    return false;
}

bool Gestao::verifica_mesma_uc(Estudante* es1, Estudante* es2, std::vector<Turma*> uc){
    bool v1 = false;
    bool v2 = false;
    Turma* turma1;
    Turma* turma2;
    for (auto turma: uc){
        for (auto estudante : turma->get_estudantes()){
            if (es1 == estudante){
                v1 = true;
                turma1 = turma;
            }
            if (es2 == estudante){
                v2 = true;
                turma2 = turma;
            }
        }
    }
    return (v1 && v2) && (turma1 != turma2);
}

bool Gestao::pode_trocar_turma(Estudante* es1, Turma* turma1, Estudante* es2){


    std::vector<Turma*> uc = pesquisa_uc(turma1->get_codigo_uc()); //BD
    bool v1 = verifica_mesma_uc(es1,es2,uc);

    Turma* turma2;
    for (auto turma: es2->get_turmas()){
        if (turma->get_codigo_uc() == turma1->get_codigo_uc() && turma != turma1){
            turma2 = turma;

            break;
        }
    }

    es1->remover_da_turma(turma1);
    es2->remover_da_turma(turma2);

    bool v2 = pode_adicionar_turma(es1,turma2) && pode_adicionar_turma(es2, turma1);
    es1->adicionar_turma(turma1);
    es2->adicionar_turma(turma2);
    return v1 && v2;

}

/**
 * Calcula o maior desiquilíbrio existente entre as turmas de uma uc
 * @param uc
 * @return
 */
int Gestao::max_diferenca(std::vector<Turma*> uc){
    std::vector<int> difs;
    for (auto it = uc.begin(); it != uc.end()-1;it++){
        for (auto j = it+1; j != uc.end();j++){
            difs.push_back(abs((*it)->get_capacidade_atual() - (*j)->get_capacidade_atual()));
        }
    }
    sort(difs.begin(),difs.end());
    return difs.back();
}
/**
 * ???
 * @param pedidos
 */
void Gestao::set_pedidos(std::queue<Pedido*> pedidos){ this->pedidos = pedidos; }
/**
 * Gestão dos pedidos
 */
void Gestao::gerir_pedidos() {
    while (!pedidos.empty()){
        //gerir_pedidos_falhados();
        if (pedidos.front()->get_tipo() == "Adicionar") pedido_adicionar(pedidos.front());
        else if (pedidos.front()->get_tipo() == "Remover") pedido_remover(pedidos.front());
        else if (pedidos.front()->get_tipo() == "Alterar") pedido_alterar(pedidos.front());
        else if (pedidos.front()->get_tipo() == "Trocar") pedido_trocar(pedidos.front());
        pedidos.pop();
    }
}
void Gestao::gerir_pedidos_falhados(){
    int size = pedidos_falhados.size();
    int i = 0;
    while (i < size){
        auto it = pedidos_falhados.begin();
        Pedido* pedido = (*it);
        if (pedido->get_tipo() == "Adicionar") {pedido_adicionar(pedido);}
        else if (pedido->get_tipo() == "Remover") pedido_remover(pedido);
        else if (pedido->get_tipo() == "Alterar") pedido_alterar(pedido);
        else if (pedido->get_tipo() == "Trocar") pedido_trocar(pedido);
        pedidos_falhados.erase(it);
        i++;
    }
}
/**
 * Pedido para adicionar um estudante a uma turma
 * @param pedido
 */
void Gestao::pedido_adicionar(Pedido * pedido) {
    bool pode = pode_adicionar_turma(pedido->get_estudante1(), pedido->get_turma());
    if (pode) pedido->get_estudante1()->adicionar_turma(pedido->get_turma());
    else{
        pedidos_falhados.push_back(pedido);
    }
    }
/**
 * Pedido para alterar um estudante para uma turma
 * @param pedido
 */
void Gestao::pedido_alterar(Pedido * pedido) {
    bool pode = pode_alterar_turma(pedido->get_estudante1(), pedido->get_turma());
    if (pode) pedido->get_estudante1()->alterar_turma(pedido->get_turma());
    else{
        pedidos_falhados.push_back(pedido);
    }
}
/**
 * Pedido para remover um estudante de uma turma
 * @param pedido
 */
void Gestao::pedido_remover(Pedido * pedido) {
    bool pode = pode_remover_turma(pedido->get_estudante1(), pedido->get_turma());
    if (pode) pedido->get_estudante1()->remover_da_turma(pedido->get_turma());
}
/**
 * Pedido para trocar dois estudantes de turma
 * @param pedido
 */
void Gestao::pedido_trocar(Pedido * pedido) {

    bool pode = pode_trocar_turma(pedido->get_estudante1(), pedido->get_turma(), pedido->get_estudante2());
    if (pode) pedido->get_estudante1()->trocar_turma_com_estudante(pedido->get_turma(), pedido->get_estudante2());
    else{
        pedidos_falhados.push_back(pedido);
    }}

void Gestao::cancelar_pedido(int n) {
    std::queue<Pedido*> fila_temp;
    int pos = 1;
    while (!pedidos.empty()){
        if (pos != n) fila_temp.push(pedidos.front());
        pos ++;
        pedidos.pop();
    }
   pedidos = fila_temp;
}

/**
 * Retorna o vetor de todas as aulas
 * @return
 */
std::vector<Aula*> Gestao::get_aulas() const{ return aulas; }
/**
 * Retorna o vetor de todas as turmas
 * @return
 */
std::vector<Turma*> Gestao::get_turmas() const{ return turmas; }
/**
 * Retorna a BST de todos os estudantes
 * @return
 */
std::set<Estudante*,Turma::cmp_codigo> Gestao::get_estudantes() const{ return estudantes; }
/**
 * Retorna o vetor de todas as ucs
 * @return
 */
std::vector<std::vector<Turma*>> Gestao::get_ucs() const{ return ucs;}
/**
 * Retorna a fila de todos os pedidos
 * @return
 */
std::queue<Pedido*> Gestao::get_pedidos() const{return pedidos;}
/**
 * Retorna a lista de todos os pedidos falhados
 * @return
 */
std::list<Pedido*> Gestao::get_pedidos_falhados() const{return pedidos_falhados;}

void Gestao::novo_ficheiro(){

    std::ofstream myfile;
    myfile.open ("C:/AED/Projeto_AED-master/CSV files/new_students_classes.csv");
    myfile << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (auto es: estudantes){
        auto StudentCode = es->get_codigo();
        auto StudentName = es->get_nome();
        if (!es->get_turmas().empty()){
            for (auto turma: es->get_turmas()){
                auto UcCode = turma->get_codigo_uc();
                auto ClassCode = turma->get_codigo_turma();
                myfile << StudentCode << "," << StudentName << "," << UcCode << "," << ClassCode << '\n';
            }
        }
    }
    myfile.close();

    std::ofstream myfile1;
    myfile1.open ("C:/AED/Projeto_AED-master/CSV files/arquivo_pedidos_falhados.csv");
    myfile1 << "Tipo,Estudante1,Estudante2,CodigoUC,CodigoTurma\n";
    for (auto pedido: pedidos_falhados){
        auto tipo = pedido->get_tipo();
        auto es1 = pedido->get_estudante1();
        auto n1 = es1->get_codigo();
        auto es2 = pedido->get_estudante2();
        std::string n2;
        if (es2 == nullptr) n2 = "-";
        else n2 = es2->get_codigo();
        auto Codigo_UC = pedido->get_turma()->get_codigo_uc();
        auto Codigo_turma = pedido->get_turma()->get_codigo_turma();
        myfile1 << tipo << "," << n1 << "," << n2 << "," << Codigo_UC << "," << Codigo_turma<< '\n';
    }
    myfile1.close();
}
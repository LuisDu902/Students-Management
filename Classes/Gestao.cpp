#include "Gestao.h"

/**
 * Construtor da classe Gestao
 * Criação dos vetores aulas, turmas, uc e da BST estudantes
 * Complexidade: O(m log(n)), n -> tamanho da BST estudantes, m -> número de linhas do ficheiro dos estudantes
 * @param n (1) ficheiro inicial / (2) ficheiro atualizado
 */
Gestao::Gestao(int n){
    criacao_aulas();
    criacao_turmas();
    criacao_estudantes(n);
    criacao_uc();
}

/**
 * Procura no vetor turmas a turma que apresenta código_uc e código_turma ...
 * Complexidade: O(log(n)), n -> tamanho do vetor das turmas
 * @param codigo_uc
 * @param codigo_turma
 * @return pointer para turma / nullpointer caso a turma não exista
 */
Turma* Gestao::pesquisa_turma(const std::string& codigo_uc, const std::string& codigo_turma) const{

    unsigned long long primeiro = 0, ultimo = turmas.size()-1;
    std::string chave = codigo_uc+codigo_turma;
    while(primeiro <= ultimo){
        unsigned long long middle = primeiro + (ultimo-primeiro)/2;
        Turma* turma = turmas.at(middle);
        std::string c = turma->get_codigo_uc()+turma->get_codigo_turma();
        if (c == chave)  return turma;
        else if (c.compare(chave) < 0) primeiro = middle+1;
        else ultimo = middle - 1;
    }
    return nullptr;

}

/**
 * Procura no vetor ucs a uc com codigo_uc igual a codigo
 * Complexidade: O(log (n)), n -> tamanho do vetor das ucs
 * @param codigo código da uc a ser pesquisada
 * @return vetor de turmas da uc com codigo_uc igual a codigo / vetor vazio caso não encontre a uc
 */
std::vector<Turma*> Gestao::pesquisa_uc(const std::string& codigo) {
    unsigned long long primeiro = 0, ultimo = ucs.size()-1;
    while(primeiro <= ultimo){
        unsigned long long middle = primeiro + (ultimo-primeiro)/2;
        std::vector<Turma*> uc = ucs.at(middle);
        std::string c = uc.front()->get_codigo_uc();
        if (c == codigo)  return uc;
        else if (c.compare(codigo) < 0) primeiro = middle+1;
        else ultimo = middle - 1;
    }
    return {};
}

/**
 * Procura na BST estudantes o estudante com número up igual a numero
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes
 * @param numero número up do estudante
 * @return retorna um pointer para o estudante / nullpointer caso o estudante não exista
 */
Estudante* Gestao::pesquisa_estudante(std::string numero) {
    Estudante es1(std::move(numero));
    Estudante *es = &es1;
    if (estudantes.find(es) != estudantes.end()) return (*estudantes.find(es));
    return nullptr;
}

/**
 * Verifica se se pode adicionar a turma t ao estudante es
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es pointer para o estudante
 * @param t pointer para a turma
 * @return true se der para adicionar a turma t ao estudante es, caso contrário false
 */
bool Gestao::pode_adicionar_turma(Estudante* es, Turma* t){
    for (Turma* x: es->get_turmas()){
        if (x->get_codigo_uc() == t->get_codigo_uc()) return false;
    }
    t->adicionar_estudante(es);
    if (t->get_estudantes().size() > Turma::capacidade_maxima || max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= 4) {
        t->remover_estudante(es);
        return false;
    }
    t->remover_estudante(es);
    return es->compativel(t);
}


/**
 * Verifica se o estudante está na turma t
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante
 * @param es pointer para o estudante
 * @param turma pointer para a turma
 * @return true se o estudante está na turma t, caso contrário false
 */
bool Gestao::pode_remover_turma(Estudante* es, Turma* t){
    for (Turma* turma:es->get_turmas()){
        if (t == turma) return true;
    }
    return false;
}

/**
 * Verifica se o estudante es pode alterar para a turma t dentro de uma UC
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es pointer para o estudante
 * @param turma pointer para a turma
 * @return true se o estudante es pode alterar para a turma t, caso contrário false
 */
bool Gestao::pode_alterar_turma(Estudante* es, Turma* t){
    Turma* turma_com_mesmo_uc = nullptr;
    bool flag = false;
    for (Turma* turma_estudante: es->get_turmas()){
        if (turma_estudante->get_codigo_uc() == t->get_codigo_uc()){
            turma_com_mesmo_uc = turma_estudante;
            es->remover_da_turma(turma_com_mesmo_uc);
            if(es->compativel(t)) flag = true;
            break;
        }
    }
    if (turma_com_mesmo_uc != nullptr){
        es->adicionar_turma(t);
        if (t->get_estudantes().size() > Turma::capacidade_maxima || max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= 4) {
            flag = false;
        }
        es->adicionar_turma(turma_com_mesmo_uc);
        es->remover_da_turma(t);
    }
    return flag;
}

/**
 * Verifica se o estudante 1 pode trocar de turma com o estudante 2
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es1  pointer para o estudante 1
 * @param turma1 pointer para a turma do estudante 1
 * @param es2  pointer para o estudante 2
 * @return
 */
bool Gestao::pode_trocar_turma(Estudante* es1, Turma* turma1, Estudante* es2){

    std::vector<Turma*> uc = pesquisa_uc(turma1->get_codigo_uc());
    bool v1 = verifica_mesma_uc(es1,es2,uc);
    if (!v1) return false;
    Turma* turma2;
    for (Turma* turma: es2->get_turmas()){
        if (turma->get_codigo_uc() == turma1->get_codigo_uc()){
            turma2 = turma;
            break;
        }
    }

    es1->remover_da_turma(turma1);
    es2->remover_da_turma(turma2);
    bool v2 = pode_adicionar_turma(es1,turma2) && pode_adicionar_turma(es2, turma1);
    es1->adicionar_turma(turma1);
    es2->adicionar_turma(turma2);
    return v2;

}

/**
 * Verifica se dois estudantes estão inscritos na mesma UC, mas não na mesma turma
 * Complexidade: O(n), n -> tamanho do vetor de turmas do estudante que está inscrito em mais turmas
 * @param es1 pointer para o estudante 1
 * @param es2 pointer para o estudante 2
 * @param uc
 * @return true se dois estudantes estão inscritos na mesma UC, mas não na mesma turma, caso contrário false
 */
bool Gestao::verifica_mesma_uc(Estudante* es1, Estudante* es2, std::vector<Turma*> uc){
    bool v1 = false, v2 = false;
    Turma* turma1;
    Turma* turma2;
    for (Turma* t: es1->get_turmas()){
        if (t->get_codigo_uc() == uc.front()->get_codigo_uc()){
            turma1 = t;
            v1 = true;
            break;
        }
    }
    for (Turma* t: es2->get_turmas()){
        if (t->get_codigo_uc() == uc.front()->get_codigo_uc()){
            turma2 = t;
            v2 = true;
            break;
        }
    }
    return (v1 && v2) && (turma1 != turma2);
}

/**
 * Calcula a maior diferença entre o número de alunos das turmas de uma uc
 * Complexidade: O(n), n -> número de turmas no vetor uc
 * @param uc
 * @return maior diferença entre o número de alunos das turmas de uma uc
 */
size_t Gestao::max_diferenca(std::vector<Turma*> uc){

    size_t min = uc.at(0)->get_estudantes().size();
    size_t max = uc.at(0)->get_estudantes().size();

    for (Turma* turma: uc){
        size_t nr_estudantes = turma->get_estudantes().size();
        if (nr_estudantes > max) max = nr_estudantes;
        else if (nr_estudantes < min) min = nr_estudantes;
    }

    return max - min;
}

/**
 * Adiciona um pedido à fila de pedidos
 * Complexidade: O(1)
 * @param pedido pointer para o pedido
 */
void Gestao::adicionar_pedido(Pedido* pedido) {pedidos.push(pedido);}

/**
 * Processa todos os pedidos da fila
 * Complexidade: O(n*m*l*k), n -> nº total de pedidos, m -> nº de pedidos falhados, l -> tamanho do vetor das aulas do estudante, k -> tamanho do vetor das aulas da turma
 */
void Gestao::gerir_pedidos() {
    while (!pedidos.empty()){
        processar_pedido(pedidos.front());
        pedidos.pop();
        gerir_pedidos_falhados();
    }
}

/**
 * Processa todos os pedidos falhados até ao momento
 * Complexidade: O(n*m*l), n -> nº de pedidos falhados, m -> tamanho do vetor das aulas do estudante, l -> tamanho do vetor das aulas da turma
 */
void Gestao::gerir_pedidos_falhados(){
    int size = pedidos_falhados.size();
    int i = 0;
    while (i < size){
        processar_pedido(pedidos_falhados.front());
        pedidos_falhados.pop_front();
        i++;
    }
}

/**
 * Processa o pedido: efetua o pedido se for válido, senão guarda-o na fila de pedidos falhados
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma
 * @param pedido pointer para o pedido a ser processado
 */
void Gestao::processar_pedido(Pedido* pedido){
    bool pode = false;
    int x = pedido->get_tipo();
    switch (x) {
        case 1:{
            if (pode_adicionar_turma(pedido->get_estudante1(), pedido->get_turma())) {
                pedido->get_estudante1()->adicionar_turma(pedido->get_turma());
                pode = true;}
            break;}
        case 2:{
            if (pode_remover_turma(pedido->get_estudante1(), pedido->get_turma())) {
                pedido->get_estudante1()->remover_da_turma(pedido->get_turma());
                pode = true;}
            break;}
        case 3:{
            if (pode_alterar_turma(pedido->get_estudante1(), pedido->get_turma())) {
                pedido->get_estudante1()->alterar_turma(pedido->get_turma());
                pode = true;}
            break;}
        case 4:{
            if (pode_trocar_turma(pedido->get_estudante1(), pedido->get_turma(), pedido->get_estudante2())) {
                pedido->get_estudante1()->trocar_turma_com_estudante(pedido->get_turma(), pedido->get_estudante2());
                pode = true;}
            break;}
    }
    if (!pode) pedidos_falhados.push_back(pedido);
}

/**
 * Cancela o pedido nº n
 * Complexidade: O(n), n -> nº de pedidos na fila
 * @param n número do pedido a cancelar
 */
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
 * Obtém a BST de estudantes
 * Complexidade: O(1)
 * @return BST de estudantes
 */
std::set<Estudante*,Turma::cmp_codigo> Gestao::get_estudantes() const{ return estudantes; }

/**
 * Obtém o vetor de todas as ucs
 * Complexidade: O(1)
 * @return vetor de todas as ucs
 */
std::vector<std::vector<Turma*>> Gestao::get_ucs() const{ return ucs;}

/**
 * Obtém a fila de todos os pedidos por processar
 * Complexidade: O(1)
 * @return fila de todos os pedidos por processar
 */
std::queue<Pedido*> Gestao::get_pedidos() const{return pedidos;}

/**
 * Obtém a lista de todos os pedidos falhados
 * Complexidade: O(1)
 * @return lista de todos os pedidos falhados
 */
std::list<Pedido*> Gestao::get_pedidos_falhados() const{return pedidos_falhados;}

/**
 * Escreve no ficheiro new_students_classes.csv o conteúdo do ficheiro students_classes.csv atualizado, ou seja, depois de processados todos os pedidos do dia
 * Complexidade: O(n*m), n -> tamanho da BST de estudantes, m -> nº de turmas de cada estudante
 */
void Gestao::atualiza_estudantes(){

    std::ofstream myfile;
    myfile.open ("C:/AED/Projeto_AED-master/CSV files/new_students_classes.csv");
    myfile << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (Estudante* es: estudantes){
        std::string StudentCode = es->get_codigo();
        std::string StudentName = es->get_nome();
        if (!es->get_turmas().empty()){
            for (Turma* turma: es->get_turmas()){
                std::string UcCode = turma->get_codigo_uc();
                std::string ClassCode = turma->get_codigo_turma();
                myfile << StudentCode << "," << StudentName << "," << UcCode << "," << ClassCode << '\n';
            }
        }
    }
    myfile.close();

}
/**
 * Escreve no ficheiro arquivo.csv os pedidos falhados no final da execução
 * Complexidade: O(n), n -> nº de pedidos falhados
 */
void Gestao::arquivo_pedidos(){
    auto map = Pedido::tipos;
    std::ofstream myfile;
    myfile.open ("C:/AED/Projeto_AED-master/CSV files/arquivo.csv");
    myfile << "Tipo,Estudante1,Estudante2,CodigoUC,CodigoTurma\n";
    for (Pedido* pedido: pedidos_falhados){
        std::string tipo = map[pedido->get_tipo()];
        Estudante* es1 = pedido->get_estudante1();
        std::string n1 = es1->get_codigo();
        Estudante* es2 = pedido->get_estudante2();
        std::string n2;
        if (es2 == nullptr) n2 = "-";
        else n2 = es2->get_codigo();
        std::string Codigo_UC = pedido->get_turma()->get_codigo_uc();
        std::string Codigo_turma = pedido->get_turma()->get_codigo_turma();
        myfile << tipo << "," << n1 << "," << n2 << "," << Codigo_UC << "," << Codigo_turma<< '\n';
    }
    myfile.close();
}

/**
 * Leitura do ficheiro classes.csv e criação das aulas, armazenando-os no vetor aulas
 * Complexidade: O(n), n -> número de linhas do ficheiro classes.csv
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
 * Complexidade: O(n log(m)), n -> tamanho do vetor aulas, m -> tamanho do vetor turmas
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
 * Complexidade: O(m log(n)), n -> tamanho da BST estudantes, m -> número de linhas do ficheiro
 * @param n (1) ficheiro inicial / (2) ficheiro atualizado
 */
void Gestao::criacao_estudantes(int n){
    std::ifstream myFile;
    std::string CurrentLine, codigo, nome, codigo_uc, codigo_turma;
    if (n == 2) myFile.open("C:/AED/Projeto_AED-master/CSV files/new_students_classes.csv");
    else myFile.open("C:/AED/Projeto_AED-master/CSV files/students_classes.csv");
    getline(myFile,CurrentLine);
    getline(myFile,CurrentLine);
    std::istringstream iss(CurrentLine);

    getline(iss,codigo,',');
    getline(iss,nome,',');
    getline(iss,codigo_uc,',');
    getline(iss,codigo_turma,',');
    if (codigo_turma.back() == '\r') codigo_turma.pop_back();

    Estudante* estudante_atual = new Estudante(codigo,nome);

    Turma * turma = pesquisa_turma(codigo_uc,codigo_turma);
    estudante_atual->adicionar_turma(turma);

    while(getline(myFile,CurrentLine)){

        std::istringstream iss1(CurrentLine);

        getline(iss1,codigo,',');
        getline(iss1,nome,',');
        getline(iss1,codigo_uc,',');
        getline(iss1,codigo_turma,',');
        if (codigo_turma.back() == '\r') codigo_turma.pop_back();

        if (codigo == estudante_atual->get_codigo()){
            Turma* turma = pesquisa_turma(codigo_uc,codigo_turma);
            estudante_atual->adicionar_turma(turma);
        }

        else{
            estudantes.insert(estudante_atual);

            Estudante* estudante_novo = new Estudante(codigo,nome);
            estudante_atual = estudante_novo;

            Turma* turma = pesquisa_turma(codigo_uc, codigo_turma);
            estudante_novo->adicionar_turma(turma);
        }

    }
    estudantes.insert(estudante_atual);
}

/**
 * Criação de todas as ucs existentes
 * Complexidade: O(n), n -> nº de turmas
 */
void Gestao::criacao_uc(){

    std::vector<Turma*> uc;
    std::string codigo_uc = turmas.front()->get_codigo_uc();
    for (Turma* turma : turmas){
        if (turma->get_codigo_uc() == codigo_uc){
            uc.push_back(turma);
        }
        else{
            ucs.push_back(uc);
            codigo_uc = turma->get_codigo_uc();
            uc = {};
            uc.push_back(turma);
        }
    }
    ucs.push_back(uc);
}
#include "Gestao.h"

/**
 * Construtor da classe Gestao\n
 * Criação dos vetores aulas, turmas, uc e da BST estudantes\n
 * Complexidade: O(m log(n)), n -> tamanho da BST estudantes, m -> número de linhas do ficheiro dos estudantes
 * @param n (1) ficheiro inicial / (2) ficheiro atualizado
 */
Gestao::Gestao(int n,int m){
    criacao_aulas();
    criacao_turmas();
    criacao_estudantes(n);
    criacao_uc();
    if (m == 1) leitura_pedidos();
}

/**
 * Obtém a BST de estudantes\n
 * Complexidade: O(1)
 * @return BST de estudantes
 */
std::set<Estudante*,Estudante::cmp_codigo> Gestao::get_estudantes() const { return estudantes; }

/**
 * Obtém o vetor de todas as ucs\n
 * Complexidade: O(1)
 * @return vetor de todas as ucs
 */
std::vector<std::vector<Turma*>> Gestao::get_ucs() const { return ucs; }

/**
 * Obtém a fila de todos os pedidos por processar\n
 * Complexidade: O(1)
 * @return fila de todos os pedidos por processar
 */
std::queue<Pedido*> Gestao::get_pedidos() const { return pedidos; }

/**
 * Obtém a lista de todos os pedidos falhados\n
 * Complexidade: O(1)
 * @return lista de todos os pedidos falhados
 */
std::list<Pedido*> Gestao::get_pedidos_falhados() const { return pedidos_falhados; }

/**
 * Procura no vetor turmas a turma que apresenta código_uc e código_turma \n
 * Complexidade: O(log(n)), n -> tamanho do vetor das turmas
 * @param codigo_uc L.EIC0__ / UP001
 * @param codigo_turma _LEIC__
 * @return pointer para turma / nullpointer caso a turma não exista
 */
Turma* Gestao::pesquisa_turma(const std::string& codigo_uc, const std::string& codigo_turma) const{
    unsigned long long primeiro = 0, ultimo = turmas.size()-1;
    std::string chave = codigo_uc + codigo_turma;
    while(primeiro <= ultimo){
        unsigned long long middle = primeiro + (ultimo - primeiro)/2;
        Turma* turma = turmas.at(middle);
        std::string c = turma->get_codigo_uc() + turma->get_codigo_turma();
        if (c == chave)  return turma;
        else if (c.compare(chave) < 0) primeiro = middle+1;
        else ultimo = middle - 1;
    }
    return nullptr;
}

/**
 * Procura no vetor ucs a uc com codigo_uc igual a codigo\n
 * Complexidade: O(log (n)), n -> tamanho do vetor das ucs
 * @param codigo L.EIC0__ / UP001
 * @return vetor de turmas da uc com codigo_uc igual a codigo / vetor vazio caso não encontre a uc
 */
std::vector<Turma*> Gestao::pesquisa_uc(const std::string& codigo) {
    unsigned long long primeiro = 0, ultimo = ucs.size()-1;
    while(primeiro <= ultimo){
        unsigned long long middle = primeiro + (ultimo - primeiro)/2;
        std::vector<Turma*> uc = ucs.at(middle);
        std::string c = uc.front()->get_codigo_uc();
        if (c == codigo)  return uc;
        else if (c.compare(codigo) < 0) primeiro = middle+1;
        else ultimo = middle - 1;
    }
    return {};
}

/**
 * Procura na BST estudantes o estudante com número up igual a numero\n
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
 * Verifica se se pode adicionar a turma t ao estudante es\n
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es pointer para o estudante
 * @param t pointer para a turma
 * @return true se der para adicionar a turma t ao estudante es, caso contrário false
 */
bool Gestao::pode_adicionar_turma(Estudante* es, Turma* t){
    if (es->procura_turma(t->get_codigo_uc()) != nullptr) return false;
    if (t->get_estudantes().size()+1 > Turma::capacidade_maxima) return false;
    return es->compativel(t);
}

/**
 * Verifica se o estudante está na turma t\n
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante
 * @param es pointer para o estudante
 * @param t pointer para a turma
 * @return true se o estudante está na turma t, caso contrário false
 */
bool Gestao::pode_remover_turma(Estudante* es, Turma* t){
    if (es->procura_turma(t->get_codigo_uc()) == t) return true;
    return false;
}

/**
 * Verifica se o estudante es pode alterar para a turma t dentro de uma UC\n
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es pointer para o estudante
 * @param t pointer para a turma
 * @return true se o estudante es pode alterar para a turma t, caso contrário false
 */
bool Gestao::pode_alterar_turma(Estudante* es, Turma* t){
    bool flag = false;
    Turma* turma_com_mesmo_uc = es->procura_turma(t->get_codigo_uc());
    if (turma_com_mesmo_uc == nullptr) return false;

    es->remover_da_turma(turma_com_mesmo_uc);
    if (es->compativel(t)) flag = true;
    es->adicionar_turma(turma_com_mesmo_uc);

    if (t->get_estudantes().size()+1 > Turma::capacidade_maxima) return false;

    return flag;
}

/**
 * Verifica se o estudante 1 pode trocar de turma com o estudante 2\n
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param es1  pointer para o estudante 1
 * @param turma1 pointer para a turma do estudante 1
 * @param es2  pointer para o estudante 2
 * @return true se o estudante es1 pode trocar de turma com o estudante es2 na UC da turma1, caso contrário false
 */
bool Gestao::pode_trocar_turma(Estudante* es1, Turma* turma1, Estudante* es2){

    Turma* t1 = es1->procura_turma(turma1->get_codigo_uc());
    Turma* turma2 = es2->procura_turma(turma1->get_codigo_uc());
    if (t1 == nullptr || turma2 == nullptr) return false;

    es1->remover_da_turma(t1);
    es2->remover_da_turma(turma2);
    bool v2 = pode_adicionar_turma(es1,turma2) && pode_adicionar_turma(es2, t1);
    es1->adicionar_turma(t1);
    es2->adicionar_turma(turma2);
    return v2;

}

/**
 * Calcula a maior diferença entre o número de alunos das turmas de uma uc\n
 * Complexidade: O(n), n -> número de turmas no vetor uc
 * @param uc L.EIC0__ / UP001
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
 * Limite de desequilíbrio entre as turmas de uma UC
 */
int Gestao::desequilibrio = 4;

/**
 * Modifica o limite de desequilíbrio para x
 * Complexidade: O(1)
 * @param x novo limite de desequilíbrio
 */
void Gestao::set_desequilibrio(int x) {desequilibrio = x;}

/**
 * Verifica se o pedido causa desequilíbrio no nº de estudantes nas turmas de uma UC
 * Complexidade: O(n), n -> nº de turmas na UC
 * @param pedido pointer para pedido a ser testado
 * @return true se causar desequilíbrio, caso contrário false
 */
bool Gestao::erro_desequilibrio(Pedido* pedido){
    Turma* t = pedido->get_turma();
    Estudante* es = pedido->get_estudante1();
    if (pedido->get_tipo() == 1){
        t->adicionar_estudante(es);
        if (max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= desequilibrio){
            t->remover_estudante(es);
            return true;
        }
        t->remover_estudante(es);
        return false;
    }
    else{
        Turma* turma_inicial = es->procura_turma(t->get_codigo_uc());
        if (turma_inicial == t) return false;
        turma_inicial->remover_estudante(es);
        t->adicionar_estudante(es);
        if (max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= desequilibrio){
            t->remover_estudante(es);
            turma_inicial->adicionar_estudante(es);
            return true;
        }
        t->remover_estudante(es);
        turma_inicial->adicionar_estudante(es);
        return false;
    }

}

/**
 * Processa todos os pedidos da fila\n
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
 * Processa o pedido: efetua o pedido se for válido, senão guarda-o na fila de pedidos falhados\n
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma
 * @param pedido pointer para o pedido a ser processado
 */
void Gestao::processar_pedido(Pedido* pedido){
    bool pode = false;
    int x = pedido->get_tipo();
    switch (x) {
        case 1:{
            if (pode_adicionar_turma(pedido->get_estudante1(), pedido->get_turma()) && !erro_desequilibrio(pedido)) {
                pedido->get_estudante1()->adicionar_turma(pedido->get_turma());
                pode = true;}
            break;}
        case 2:{
            if (pode_remover_turma(pedido->get_estudante1(), pedido->get_turma())) {
                pedido->get_estudante1()->remover_da_turma(pedido->get_turma());
                pode = true;}
            break;}
        case 3:{
            if (pode_alterar_turma(pedido->get_estudante1(), pedido->get_turma())  && !erro_desequilibrio(pedido)) {
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
 * Adiciona um pedido à fila de pedidos\n
 * Complexidade: O(1)
 * @param pedido pointer para o pedido
 */
void Gestao::adicionar_pedido(Pedido* pedido) { pedidos.push(pedido); }

/**
 * Cancela o pedido nº n\n
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
 * Remove o pedido p da lista de pedidos falhados
 * Complexidade: O(n), n -> tamanho da lista de pedidos falhados
 * @param p pointer para o pedido a ser removido
 */
void Gestao::remover_pedido_falhado(Pedido* p){
    for (auto it = pedidos_falhados.begin(); it != pedidos_falhados.end(); it++){
        Pedido* pedido = (*it);
        if (pedido == p) {
            pedidos_falhados.erase(it);
            return;
        }
    }
}

/**
 * Modifica a lista de pedidos falhados para l
 * Complexidade: O(1)
 * @param l lista de pedidos
 */
void Gestao::set_pedidos_falhados(std::list<Pedido*> l) { pedidos_falhados = std::move(l); }

/**
 * Escreve no ficheiro new_students_classes.csv o conteúdo do ficheiro students_classes.csv atualizado, ou seja, depois de processados todos os pedidos do dia\n
 * Complexidade: O(n*m), n -> tamanho da BST de estudantes, m -> nº de turmas de cada estudante
 */
void Gestao::atualiza_estudantes(){
    std::ofstream myfile;
    myfile.open ("/home/du/CLionProjects/Projeto_AED/CSV files/new_students_classes.csv");
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
 * Escreve no ficheiro arquivo.csv os pedidos falhados no final da execução\n
 * Complexidade: O(n), n -> nº de pedidos falhados
 */
void Gestao::arquivo_pedidos(){
    std::ofstream myfile;
    myfile.open("/home/du/CLionProjects/Projeto_AED/CSV files/arquivo.csv");

    if (pedidos_falhados.empty()){
        myfile << "Não tem pedidos falhados (づ｡◕‿‿◕｡)づ\n";
        myfile.close();
        return;
    }

    std::string nome_tipo, cod1, cod2, Codigo_UC, Codigo_turma;
    int num_tipo;

    myfile << "Tipo,NumTipo,Estudante1,Estudante2,CodigoUC,CodigoTurma\n";
    for (Pedido* pedido: pedidos_falhados){
        nome_tipo = Pedido::tipos[pedido->get_tipo()];
        num_tipo = pedido->get_tipo();
        Estudante* es1 = pedido->get_estudante1();
        cod1 = es1->get_codigo();
        Estudante* es2 = pedido->get_estudante2();
        if (es2 == nullptr) cod2 = "-";
        else cod2 = es2->get_codigo();
        Codigo_UC = pedido->get_turma()->get_codigo_uc();
        Codigo_turma = pedido->get_turma()->get_codigo_turma();
        myfile << nome_tipo << "," << num_tipo << "," << cod1 << "," << cod2 << "," << Codigo_UC << "," << Codigo_turma<< '\n';
    }
    myfile.close();
}

/**
 * Leitura do ficheiro classes.csv e criação das aulas, armazenando-os no vetor aulas\n
 * Complexidade: O(n), n -> número de linhas do ficheiro classes.csv
 */
void Gestao::criacao_aulas(){

    std::string CurrentLine, x, codigo_turma, codigo_uc, dia_semana, tipo;
    double hora_inicio, duracao;
    std::ifstream myFile;

    myFile.open("/home/du/CLionProjects/Projeto_AED/CSV files/classes.csv");
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
 * Leitura do ficheiro classes_per_uc.csv e criação das turmas, armazenando-os no vetor turmas.\n
 * Atribuição das aulas à sua respetiva turma.
 * Complexidade: O(n log(m)), n -> tamanho do vetor aulas, m -> tamanho do vetor turmas
 */
void Gestao::criacao_turmas(){
    std::string CurrentLine, codigo_uc, codigo_turma;
    std::ifstream myFile;

    myFile.open("/home/du/CLionProjects/Projeto_AED/CSV files/classes_per_uc.csv");
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
 * Leitura do ficheiro students_classes.csv e criação dos estudantes, armazenando-os na BST estudantes.\n
 * Atribuição das turmas a cada estudante.\n
 * Complexidade: O(m log(n)), n -> tamanho da BST estudantes, m -> número de linhas do ficheiro
 * @param n (1) ficheiro inicial / (2) ficheiro atualizado
 */
void Gestao::criacao_estudantes(int n){
    std::ifstream myFile;
    std::string CurrentLine, codigo, nome, codigo_uc, codigo_turma;
    if (n == 2) myFile.open("/home/du/CLionProjects/Projeto_AED/CSV files/new_students_classes.csv");
    else myFile.open("/home/du/CLionProjects/Projeto_AED/CSV files/students_classes.csv");
    getline(myFile,CurrentLine);
    getline(myFile,CurrentLine);
    std::istringstream iss(CurrentLine);

    getline(iss,codigo,',');
    getline(iss,nome,',');
    getline(iss,codigo_uc,',');
    getline(iss,codigo_turma,',');   if (codigo_turma.back() == '\r') codigo_turma.pop_back();

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
            Turma* t = pesquisa_turma(codigo_uc,codigo_turma);
            estudante_atual->adicionar_turma(t);
        }

        else{
            estudantes.insert(estudante_atual);

            Estudante* estudante_novo = new Estudante(codigo,nome);
            estudante_atual = estudante_novo;

            Turma* t = pesquisa_turma(codigo_uc, codigo_turma);
            estudante_novo->adicionar_turma(t);
        }

    }
    estudantes.insert(estudante_atual);
}

/**
 * Criação de todas as ucs existentes\n
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

/**
 * Leitura do ficheiro arquivo.csv e criação dos pedidos falhados, armazenando-os na lista pedidos_falhados
 * Complexidade: O(n): n -> nº de linhas do ficheiro arquivo.csv
 */
void Gestao::leitura_pedidos(){
    std::ifstream myFile;
    std::string CurrentLine, t, es1_up, es2_up, codigo_uc, codigo_turma;
    int tipo;
    Estudante* estudante1;
    Estudante* estudante2;
    Turma* turma;

    myFile.open("/home/du/CLionProjects/Projeto_AED/CSV files/arquivo.csv");
    getline(myFile,CurrentLine);

    while (getline(myFile,CurrentLine)){

        std::istringstream iss(CurrentLine);

        getline(iss,t,',');
        getline(iss,t,','); tipo = stoi(t);
        getline(iss,es1_up,','); estudante1 = pesquisa_estudante(es1_up);
        getline(iss,es2_up,',');
        if (es2_up == "-") estudante2 = nullptr;
        else estudante2 = pesquisa_estudante(es2_up);
        getline(iss,codigo_uc,',');
        getline(iss,codigo_turma,',');

        if(codigo_turma == "-") turma = new Turma(codigo_uc);
        else turma = pesquisa_turma(codigo_uc,codigo_turma);

        Pedido* ptr = new Pedido(tipo,turma,estudante1,estudante2);
        pedidos_falhados.push_back(ptr);
    }
}

/**
 * Processa todos os pedidos falhados até ao momento\n
 * Complexidade: O(n*m*l), n -> nº de pedidos falhados, m -> tamanho do vetor das aulas do estudante, l -> tamanho do vetor das aulas da turma
 */
void Gestao::gerir_pedidos_falhados(){
    size_t size = pedidos_falhados.size();
    size_t i = 0;
    while (i < size){
        processar_pedido(pedidos_falhados.front());
        pedidos_falhados.pop_front();
        i++;
    }
}

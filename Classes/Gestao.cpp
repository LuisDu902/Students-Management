//
// Created by athos on 31/10/2022.
//

#include "Gestao.h"
Gestao::Gestao(){
    criacao_aulas();
    criacao_turmas();
    criacao_estudantes();
    criacao_uc();
}

void Gestao::criacao_aulas(){

    std::string CurrentLine, x, codigo_turma, codigo_uc, dia_semana, tipo;
    double hora_inicio, duracao;
    std::ifstream myFile;

    myFile.open("/home/du/CLionProjects/Projeto_AED-erro-run/CSV files/classes.csv");
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
void Gestao::criacao_turmas(){
    std::string CurrentLine, codigo_uc, codigo_turma;
    std::ifstream myFile;

    myFile.open("/home/du/CLionProjects/Projeto_AED-erro-run/CSV files/classes_per_uc.csv");
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
void Gestao::criacao_estudantes(){
    std::ifstream myFile;
    std::string CurrentLine, codigo, nome, codigo_uc, codigo_turma;;

    myFile.open("/home/du/CLionProjects/Projeto_AED-erro-run/CSV files/students_classes.csv");
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

Turma* Gestao::pesquisa_turma(std::string codigo_uc, std::string codigo_turma){
    for (auto turma : turmas){
        if (turma->get_codigo_turma() == codigo_turma && turma->get_codigo_uc() == codigo_uc){
            return turma;
        }
    }
    return turmas.at(0);

}
std::vector<Turma*> Gestao::pesquisa_uc(std::string codigo_uc){
    for (auto uc: ucs){
        if (uc.front()->get_codigo_uc() == codigo_uc){
            return uc;
        }
    }
    return {};
}
Estudante* Gestao::pesquisa_estudante(std::string nome){
    for (auto e: estudantes){
        if (e->get_nome() == nome){
            return e;
        }
    }
    return nullptr;
}
bool Gestao::pode_adicionar_turma(Estudante* es, Turma* t){
    t->set_capacidade(t->get_capacidade_atual()+1);
    if (t->get_capacidade_atual() > Turma::capacidade_maxima || max_diferenca(pesquisa_uc(t->get_codigo_uc())) >= 4) {
        t->set_capacidade(t->get_capacidade_atual()-1);
        return false;
    }
    t->set_capacidade(t->get_capacidade_atual()-1);
    return es->compativel(t);
}
bool Gestao::pode_alterar_turma(Estudante* es, Turma* turma){
    Turma* turma_removida;
    for (auto t=es->get_turmas().begin();t!=es->get_turmas().end();t++){
        if ((*t)->get_codigo_uc() == turma->get_codigo_uc()){
            es->get_turmas().erase(t);
            turma_removida = *t;
        }
    }
    if (es->compativel(turma)) return true;
    else{
        es->get_turmas().pop_back();
        es->get_turmas().push_back(turma_removida);
        return false;
    }
}

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

void Gestao::set_pedidos(std::queue<Pedido*> pedidos){ this->pedidos = pedidos; }

void Gestao::gerir_pedidos() {
    while (!pedidos.empty()){
        if (pedidos.front()->get_tipo() == "adicionar") pedido_adicionar(pedidos.front());
        if (pedidos.front()->get_tipo() == "remover") pedido_remover(pedidos.front());
        if (pedidos.front()->get_tipo() == "alterar") pedido_alterar(pedidos.front());
        if (pedidos.front()->get_tipo() == "trocar") pedido_trocar(pedidos.front());
    }
}
void Gestao::pedido_adicionar(Pedido * pedido) {pedido->get_estudante1()->adicionar_turma(pedido->get_turma()); }
void Gestao::pedido_alterar(Pedido * pedido) {pedido->get_estudante1()->alterar_turma(pedido->get_turma()); }
void Gestao::pedido_remover(Pedido * pedido) {pedido->get_estudante1()->remover_da_turma(pedido->get_turma());}
void Gestao::pedido_trocar(Pedido * pedido) {pedido->get_estudante1()->trocar_turma_com_estudante(pedido->get_turma(), pedido->get_estudante2());}


std::vector<Aula*> Gestao::get_aulas() const{ return aulas; }
std::vector<Turma*> Gestao::get_turmas() const{ return turmas; }
std::set<Estudante*,Turma::cmp_nome> Gestao::get_estudantes() const{ return estudantes; }
std::vector<std::vector<Turma*>> Gestao::get_ucs() const{ return ucs;}
std::queue<Pedido*> Gestao::get_pedidos() const{return pedidos;}
std::list<Pedido*> Gestao::get_pedidos_falhados() const{return pedidos_falhados;}
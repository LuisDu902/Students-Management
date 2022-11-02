//
// Created by athos on 13/10/2022.
//

#include "Turma.h"
#include "Menu.h"
//construtor
/**
 * Construtor da classe Turma, recebe um código_uc e um código_turma (a capacidade atual da turma é iniciada a 0, sendo o vetor de aulas corresponde a um vetor vazio, e o BST de estudantes a uma BST vazio
 * @param codigo_uc
 * @param codigo_turma
 */
Turma::Turma(std::string codigo_uc,std::string codigo_turma){
    this->codigo_turma = codigo_turma;
    this->codigo_uc = codigo_uc;
    capacidade_atual = 0;
}

//getters
/**
 * Retorna o código_uc da turma
 * @return
 */
std::string Turma::get_codigo_uc() const {return codigo_uc;}
/**
 * Retorna o código_turma da turma
 * @return
 */
std::string Turma::get_codigo_turma() const {return codigo_turma;}
/**
 * Retorna o vetor de todas as aulas associadas à turma
 * @return
 */
std::vector<Aula*> Turma::get_aulas() const{return aulas;}
/**
 * Retorna a BST de todos os estudantes da turma
 * @return
 */
std::set<Estudante*,Turma::cmp_nome> Turma::get_estudantes() const{return estudantes;}
/**
 * Retorna o número atual de estudantes da turma
 * @return
 */
int Turma::get_capacidade_atual() const{return capacidade_atual;}

//operators
/**
 * Modifica o valor da capacidade atual da turma para cap
 * @param capacidade
 */
void Turma::set_capacidade(int capacidade) {capacidade_atual=capacidade;}
/**
 * Adiciona a aula no fim do vetor de aulas da turma
 * @param aula
 */
void Turma::adicionar_aula(Aula* aula){aulas.push_back(aula);}
/**
 * Adiciona um estudante à BST de estudantes da turma
 * @param estudante
 */
void Turma::adicionar_estudante(Estudante* estudante){estudantes.insert(estudante);}
/**
 * Remove um estudante da BST de estudantes da turma
 * @param estudante
 */
void Turma::remover_estudante(Estudante* estudante){estudantes.erase(estudantes.find(estudante));}

//compare
/**
 * Método de ordenação entre dois estudantes pela ordem alfabética
 * @param lhs
 * @param rhs
 * @return
 */
bool Turma::cmp_nome::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_nome() < rhs->get_nome();}

/**
 * Método de ordenação entre dois estudantes de acordo com o código do estudante
 * @param lhs
 * @param rhs
 * @return
 */
bool Turma::cmp_codigo::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_codigo() < rhs->get_codigo();}

/**
 * Método de ordenação entre dois estudantes de acordo com o número de ucs que frequenta. Se os estudantes frequentarem o mesmo número de ucs, a ordenação é feita alfabeticamente
 * @param lhs
 * @param rhs
 * @return
 */
bool Turma::cmp_nr_uc::operator()(const Estudante* lhs, const Estudante* rhs) const  {
    return (lhs->get_turmas().size() < rhs->get_turmas().size()) ||
     (lhs->get_turmas().size() == rhs->get_turmas().size() && lhs->get_nome() < rhs->get_nome());}
//show
/**
 * Mostra a turma
 */
void Turma::show() const{
    std::cout << codigo_uc << " | " << codigo_turma << '\n';
}

/**
 * Mostra todos os estudantes pertencentes à turma
 */
void Turma::show_estudantes(int ordem, int ordem_c) const{
    if (ordem == 2){
        std::set<Estudante*, Turma::cmp_codigo> es;
        for (auto estudante: estudantes){
            es.insert(estudante);
        }
        Menu::show_ordem_c(es,ordem,ordem_c);
    }
    else Menu::show_ordem_c(estudantes,ordem,ordem_c);
}
/**
 * Mostra todas as aulas associadas à turma
 */
void Turma::show_horario_turma() {

    std::map<std::string,int> dias = Aula::dias;
    std::map<std::string,std::string> pt = Aula::pt;

    sort(aulas.begin(),aulas.end(),Aula::cmp);

    int dia_atual = 0;

    for (Aula* aula: aulas){
        if (dias[aula->get_dia_semana()] != dia_atual){
            dia_atual = dias[aula->get_dia_semana()];
            std::cout << pt[aula->get_dia_semana()] << ":\n";
        }
        aula->show();
        std::cout << '\n';
    }
}




//
// Created by athos on 13/10/2022.
//

#include "Turma.h"

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
    if (lhs->get_turmas().size() != rhs->get_turmas().size()) return lhs->get_turmas().size() < rhs->get_turmas().size();
    return lhs->get_nome() < rhs->get_nome();}

//show
/**
 * Mostra o código_uc, o código_turma e a capacidade atual da turma
 */
void Turma::show() {
    std::cout << codigo_uc << " | " << codigo_turma << " | numero de alunos: " << capacidade_atual << std::endl;
}
/**
 * Mostra todos os estudantes pertencentes à turma
 */
void Turma::show_estudantes(int ordem, int ordem_c){
    if (ordem == 2){
        std::set<Estudante*, Turma::cmp_codigo> es;
        for (auto estudante: estudantes){
            es.insert(estudante);
        }
        if (ordem_c == 2){
            for (auto it = es.rbegin(); it != es.rend(); it++){
                (*it)->show(ordem);
                std::cout << std::endl;
            }
        }
        else {
            for (auto estudante: es) {
                estudante->show(ordem);
                std::cout << std::endl;
            }
        }
    }
    else{
        if (ordem_c == 2){
            for (auto it = estudantes.rbegin(); it != estudantes.rend(); it++){
                (*it)->show(ordem);
                std::cout << std::endl;
            }
        }
        else {
            for (auto estudante: estudantes){
                estudante->show(ordem);
                std::cout << std::endl;
            }
        }
    }
}
/**
 * Mostra todas as aulas associadas à turma
 */
void Turma::show_horario_turma(){
    std::map<std::string,int> days = {
            std::pair<std::string,int> ("Monday",1),
            std::pair<std::string,int> ("Tuesday",2),
            std::pair<std::string,int> ("Wednesday",3),
            std::pair<std::string,int> ("Thursday",4),
            std::pair<std::string,int> ("Friday",5),
    };
    sort(aulas.begin(),aulas.end(),Aula::cmp);
    auto it = aulas.begin();
    int dia_atual = days[(*it)->get_dia_semana()];
    std::cout << (*it)->get_dia_semana() << ":\n";
    while (it != aulas.end()){
        if (days[(*it)->get_dia_semana()] == dia_atual){
            (*it)->show_horario_turma();
            it++;
        }
        else {
            dia_atual = days[(*it)->get_dia_semana()];
            std::cout << (*it)->get_dia_semana() << ":\n";
            (*it)->show_horario_turma();
            it++;
        }
        }
    }





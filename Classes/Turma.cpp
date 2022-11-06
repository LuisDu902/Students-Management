#include "Turma.h"

/**
 * Construtor da classe Turma
 * @param codigo_uc _L.EIC0__ / UP001
 * @param codigo_turma _LEIC__
 */
Turma::Turma(std::string codigo_uc,std::string codigo_turma){
    this->codigo_turma = std::move(codigo_turma);
    this->codigo_uc = std::move(codigo_uc);
}

/**
 * Obtém o código_uc da turma\n
 * Complexidade: O(1)
 * @return codigo_uc da turma
 */
std::string Turma::get_codigo_uc() const {return codigo_uc;}

/**
 * Obtém o código_turma da turma\n
 * Complexidade: O(1)
 * @return código_turma da turma
 */
std::string Turma::get_codigo_turma() const {return codigo_turma;}

/**
 * Obtém o vetor de todas as aulas associadas à turma\n
 * Complexidade: O(1)
 * @return vetor de aulas da turma
 */
std::vector<Aula*> Turma::get_aulas() const{return aulas;}

/**
 * Obtém a BST de todos os estudantes da turma\n
 * Complexidade: O(1)
 * @return BST de todos os estudantes da turma
 */
std::set<Estudante*> Turma::get_estudantes() const{return estudantes;}

/**
 * Capacidade máxima de uma turma
 */
int Turma::capacidade_maxima = 30;

/**
 * Modifica a capacidade máxima de uma turma para x
 * Complexidade: O(1)
 * @param x
 */
void Turma::set_capacidade_maxima(int x) {capacidade_maxima = x;}

/**
 * Adiciona a aula no fim do vetor de aulas da turma\n
 * Complexidade: O(1)
 * @param aula pointer para a aula a adicionar
 */
void Turma::adicionar_aula(Aula* aula) {aulas.push_back(aula);}

/**
 * Adiciona um estudante à BST de estudantes da turma\n
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes
 * @param estudante pointer para o estudante a adicionar
 */
void Turma::adicionar_estudante(Estudante* estudante) {estudantes.insert(estudante);}

/**
 * Remove um estudante da BST de estudantes da turma\n
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes
 * @param estudante pointer para o estudante a remover
 */
void Turma::remover_estudante(Estudante* estudante) {estudantes.erase(estudantes.find(estudante));}

/**
 * Mostra o codigo_uc e o codigo_turma da turma\n
 * Complexidade: O(1)
 */
void Turma::show() const{std::cout << codigo_uc << " | " << codigo_turma << '\n';}

/**
 * Mostra todos os estudantes pertencentes à turma\n
 * Complexidade: O(n log(n)), n -> tamanho da BST de estudantes
 * @param ordem (1) ordem alfabética / (2) ordem numérica
 * @param ordem_c (1) ordem crescente / (2) ordem decrescente
 */
void Turma::show_estudantes(int ordem, int ordem_c) const{
    if (ordem == 1){
        std::set<Estudante*,Estudante::cmp_nome> es;
        for (Estudante* estudante: estudantes) es.insert(estudante);
        if (ordem_c == 1){
            for (Estudante* estudante: es) {
                estudante->show(ordem);
                std::cout << '\n';
            }
        }
        else{
            for (auto it = es.rbegin(); it !=es.rend(); it++){
                (*it)->show(ordem);
                std::cout << '\n';
            }
        }
    }
    else{
        std::set<Estudante*,Estudante::cmp_codigo> es;
        for (Estudante* estudante: estudantes) es.insert(estudante);
        if (ordem_c == 1){
            for (Estudante* estudante: es) {
                estudante->show(ordem);
                std::cout << '\n';
            }
        }
        else{
            for (auto it = es.rbegin(); it !=es.rend(); it++){
                (*it)->show(ordem);
                std::cout << '\n';
            }
        }
    }
}

/**
 * Mostra todas as aulas associadas à turma em ordem cronológica\n
 * Complexidade: O(n log(n)), n-> tamanho do vetor das aulas da turma
 */
void Turma::show_horario_turma() {

    sort(aulas.begin(),aulas.end(),Aula::cmp);

    int dia_atual = 0;

    for (Aula* aula: aulas){
        if (Aula::dias[aula->get_dia_semana()] != dia_atual){
            dia_atual = Aula::dias[aula->get_dia_semana()];
            std::cout << Aula::portugues[aula->get_dia_semana()] << ":\n";
        }
        aula->show();
        std::cout << '\n';
    }
}

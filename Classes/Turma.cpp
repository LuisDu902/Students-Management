#include "Turma.h"

#include <utility>
#include "Menu.h"
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
 * Obtém o código_uc da turma
 * Complexidade: O(1)
 * @return codigo_uc da turma
 */
std::string Turma::get_codigo_uc() const {return codigo_uc;}

/**
 * Obtém o código_turma da turma
 * Complexidade: O(1)
 * @return código_turma da turma
 */
std::string Turma::get_codigo_turma() const {return codigo_turma;}

/**
 * Obtém o vetor de todas as aulas associadas à turma
 * Complexidade: O(1)
 * @return vetor de aulas da turma
 */
std::vector<Aula*> Turma::get_aulas() const{return aulas;}

/**
 * Obtém a BST de todos os estudantes da turma
 * Complexidade: O(1)
 * @return BST de todos os estudantes da turma
 */
std::set<Estudante*,Turma::cmp_nome> Turma::get_estudantes() const{return estudantes;}

/**
 * Adiciona a aula no fim do vetor de aulas da turma
 * Complexidade: O(1)
 * @param aula pointer para a aula a adicionar
 */
void Turma::adicionar_aula(Aula* aula){aulas.push_back(aula);}

/**
 * Adiciona um estudante à BST de estudantes da turma
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes
 * @param estudante pointer para o estudante a adicionar
 */
void Turma::adicionar_estudante(Estudante* estudante){estudantes.insert(estudante);}

/**
 * Remove um estudante da BST de estudantes da turma
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes
 * @param estudante pointer para o estudante a remover
 */
void Turma::remover_estudante(Estudante* estudante){estudantes.erase(estudantes.find(estudante));}

/**
 * Método de comparação entre dois estudantes pela ordem alfabética
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o nome do estudante 1 for anterior ao nome do estudante 2, caso contrário false
 */
bool Turma::cmp_nome::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_nome() < rhs->get_nome();}

/**
 * Método de comparação entre dois estudantes de acordo com o código do estudante
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o código do estudante 1 for menor que o do estudante 2, caso contrário false
 */
bool Turma::cmp_codigo::operator()(const Estudante* lhs, const Estudante* rhs) const  { return lhs->get_codigo() < rhs->get_codigo();}

/**
 * Método de comparação entre dois estudantes de acordo com o número de ucs que frequenta.
 * Se os estudantes frequentarem o mesmo número de ucs, a comparação é feita alfabeticamente
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o estudante 1 estiver inscrito em menos uc's que o estudante 2, ou inscrito no mesmo número de uc's mas tiver nome anterior, caso contrário false
 */
bool Turma::cmp_nr_uc::operator()(const Estudante* lhs, const Estudante* rhs) const  {
    return (lhs->get_turmas().size() < rhs->get_turmas().size()) ||
     (lhs->get_turmas().size() == rhs->get_turmas().size() && lhs->get_nome() < rhs->get_nome());}

/**
 * Mostra o codigo_uc e o codigo_turma da turma
 * Complexidade: O(1)
 */
void Turma::show() const{
    std::cout << codigo_uc << " | " << codigo_turma << '\n';
}

/**
 * Mostra todos os estudantes pertencentes à turma
 * Complexidade: O(n log(n)), n -> tamanho da BST de estudantes
 */
void Turma::show_estudantes(int ordem, int ordem_c) const{
    if (ordem == 2){
        std::set<Estudante*, Turma::cmp_codigo> es;
        for (Estudante* estudante: estudantes){
            es.insert(estudante);
        }
        Menu::show_ordem_c(es,ordem,ordem_c);
    }
    else Menu::show_ordem_c(estudantes,ordem,ordem_c);
}

/**
 * Mostra todas as aulas associadas à turma em ordem cronológica
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





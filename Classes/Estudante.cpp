#include "Estudante.h"

/**
 * Construtor da classe Estudante
 * @param codigo número up do estudante
 * @param nome nome do estudante
 */
Estudante::Estudante(std::string codigo, std::string nome) {
    this->codigo = std::move(codigo);
    this-> nome = std::move(nome);
}

/**
 * Obtém o nome do estudante\n
 * Complexidade: O(1)
 * @return nome do estudante
 */
std::string Estudante::get_nome() const {return nome;}

/**
 * Obtém o número up do estudante\n
 * Complexidade: O(1)
 * @return número up do estudante
 */
std::string Estudante::get_codigo() const {return codigo;}

/**
 * Obtém o vetor de todas as turmas do estudante\n
 * Complexidade: O(1)
 * @return vetor de todas as turmas do estudante
 */
std::vector<Turma *> Estudante::get_turmas() const {return turmas;}

/**
 * Método de comparação entre dois estudantes pela ordem alfabética\n
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o nome do estudante 1 for anterior ao nome do estudante 2, caso contrário false
 */
bool Estudante::cmp_nome::operator()(const Estudante* lhs, const Estudante* rhs) const { return lhs->get_nome() < rhs->get_nome();}

/**
 * Método de comparação entre dois estudantes de acordo com o código do estudante\n
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o código do estudante 1 for menor que o do estudante 2, caso contrário false
 */
bool Estudante::cmp_codigo::operator()(const Estudante* lhs, const Estudante* rhs) const { return lhs->get_codigo() < rhs->get_codigo();}

/**
 * Método de comparação entre dois estudantes de acordo com o número de ucs que frequenta.\n
 * Se os estudantes frequentarem o mesmo número de ucs, a comparação é feita alfabeticamente\n
 * Complexidade: O(1)
 * @param lhs pointer para estudante 1
 * @param rhs pointer para estudante 2
 * @return true se o estudante 1 estiver inscrito em menos uc's que o estudante 2, ou inscrito no mesmo número de uc's mas tiver nome anterior, caso contrário false
 */
bool Estudante::cmp_nr_uc::operator()(const Estudante* lhs, const Estudante* rhs) const  {
    return (lhs->get_turmas().size() < rhs->get_turmas().size()) ||
           (lhs->get_turmas().size() == rhs->get_turmas().size() && lhs->get_nome() < rhs->get_nome());}

/**
 * Adicionar a turma no fim do vetor de turmas do estudante\n
 * Complexidade: O(log(n)), n -> tamanho da BST de estudantes da turma t
 * @param t pointer para a turma a adicionar
 */
void Estudante::adicionar_turma(Turma* t){
    t->adicionar_estudante(this);
    turmas.push_back(t);
}

/**
 * Remove o estudante da turma t\n
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante
 * @param t pointer para a turma a ser removida
 */
void Estudante::remover_da_turma(Turma* t){
    for (auto it = turmas.begin();it != turmas.end();it++){
        if ((*it)->get_codigo_turma() == t->get_codigo_turma() && (*it)->get_codigo_uc() == t->get_codigo_uc()){
            Turma* t1 = *it;
            t1->remover_estudante(this);
            turmas.erase(it);
            return;
        }
    }
}

/**
 * Altera o estudante para a turma t de uma mesma UC\n
 * Complexidade: O(n) -> tamanho do vetor das turmas do estudante
 * @param t pointer para a turma que o estudante vai
 */
void Estudante::alterar_turma(Turma* t){
    for (Turma* turma: turmas){
        if (turma->get_codigo_uc() == t->get_codigo_uc()){
            remover_da_turma(turma);
            break;
        }
    }
    adicionar_turma(t);
}

/**
 * Troca dois estudantes de turma um com o outro\n
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante com mais turmas
 * @param turma1 pointer para a turma
 * @param estudante_troca pointer para estudante com o qual se pretende trocar de turma
 */
void Estudante::trocar_turma_com_estudante(Turma *turma1, Estudante *estudante_troca) {
    Turma* t1 = procura_turma(turma1->get_codigo_uc());

    Turma* turma2;
    for (Turma* t: estudante_troca->get_turmas()){
        if (t->get_codigo_uc() == turma1->get_codigo_uc() && t != turma1){
            turma2 = t;
            break;
        }
    }

    remover_da_turma(t1);
    estudante_troca->remover_da_turma(turma2);

    adicionar_turma(turma2);
    estudante_troca->adicionar_turma(t1);
}

/**
 * Obtém a turma do estudante com codigo_uc igual a cod\n
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante
 * @param cod codigo_uc
 * @return pointer para a turma procurada / Nullpointer caso não encontre
 */
Turma* Estudante::procura_turma(const std::string& cod){
    for (Turma* x: turmas){
        if (x->get_codigo_uc() == cod) return x;
    }
    return nullptr;
}

/**
 * Obtém o horário do estudante\n
 * Complexidade: O(n*m), n -> tamanho do vetor das turmas do estudante, m -> tamanho do vetor das aulas de cada turma
 * @return vetor de todas as aulas do estudante
 */
std::vector<Aula*> Estudante::horario(){
    std::vector<Aula*> a;
    for (Turma* turma: turmas){
        for (Aula* aula : turma->get_aulas())
            a.push_back(aula);
    }
    return a;
}

/**
 * Verifica se o horário da turma é compatível com o horário do estudante\n
 * Complexidade: O(n*m), n -> tamanho do vetor das aulas do estudante, m -> tamanho do vetor das aulas da turma t
 * @param t pointer para a turma
 * @return true se o horário da turma é compatível com o horário do estudante, caso contrário false
 */
bool Estudante::compativel(Turma* t){
    std::vector<Aula*> h = horario();
    for (Aula* aula_turma : t->get_aulas()){
        for (Aula* aula_estudante: h){
            if (aula_turma->sobrepoe(aula_estudante)) return false;
        }
    }
    return true;
}

/**
  * Mostra o nome e o código do estudante\n
  * Complexidade: O(1)
  * @param ordem (1) nome - número  / (2) número - nome
  */
void Estudante::show(int ordem) const{
    if (ordem == 2) std::cout << "up" << codigo << " - " << nome;
    else std::cout << nome << " - up" << codigo;
}

/**
 * Mostra o horário do estudante em ordem cronológica\n
 * Complexidade: O(n log(n)), n -> tamanho do vetor das aulas do estudante
 */
void Estudante::show_horario(){
    std::vector<Aula*> aulas = horario();

    sort(aulas.begin(),aulas.end(),Aula::cmp);

    int dia_atual = 0;
    std::string tipo_atual;
    double hora = 0;

    for (Aula* aula: aulas){
        if (Aula::dias[aula->get_dia_semana()] != dia_atual){
            dia_atual = Aula::dias[aula->get_dia_semana()];
            std::cout << '\n' << Aula::portugues[aula->get_dia_semana()] << ":";
            tipo_atual = "";
            hora = 0;
        }
        if (aula->get_hora_inicio() != hora || aula->get_tipo() != tipo_atual) {
            tipo_atual = aula->get_tipo();
            hora = aula->get_hora_inicio();
            std::cout << '\n';
            aula->show();
            std::cout << " | " << aula->get_codigo_uc() << " | " << aula->get_codigo_turma();
        }
    }
}

/**
 * Mostra todas as turmas do estudante\n
 * Complexidade: O(n), n -> tamanho do vetor das turmas do estudante
 */
void Estudante::show_turmas() const{
    for (Turma* turma: turmas) turma->show();
}
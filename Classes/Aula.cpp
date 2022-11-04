#include "Aula.h"

/**
 * Construtor da classe Aula
 * @param codigo_turma _LEIC__
 * @param codigo_uc _L.EIC0__ / UP001
 * @param dia_semana
 * @param hora_inicio
 * @param duracao
 * @param tipo T / TP / PL
 */
Aula::Aula(std::string codigo_turma, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo){
    this->codigo_turma = std::move(codigo_turma);
    this->codigo_uc = std::move(codigo_uc);
    this->dia_semana = std::move(dia_semana);
    this->hora_inicio = hora_inicio;
    this->duracao = duracao;
    this->tipo = std::move(tipo);
}
/**
 * Obtém o tipo da aula T / TP / PL\n
 * Complexidade: O(1)
 * @return tipo da aula T / TP / PL
 */
std::string Aula::get_tipo() const {return tipo;}

/**
 * Obtém o código_turma da aula\n
 * Complexidade: O(1)
 * @return código_turma da aula
 */
std::string Aula::get_codigo_turma() const {return codigo_turma;}
/**
 * Obtém o código_uc da aula\n
 * Complexidade: O(1)
 * @return código_uc da aula
 */
std::string Aula::get_codigo_uc() const {return codigo_uc;}
/**
 * Obtém o dia da semana da aula\n
 * Complexidade: O(1)
 * @return dia da semana da aula
 */
std::string Aula::get_dia_semana() const { return dia_semana; }

/**
 * Método de comparação entre duas aulas de acordo com o dia da semana\n
 * Se as aulas forem no mesmo dia, a comparação é feita tendo em conta a hora de início\n
 * Complexidade: O(1)
 * @param lhs pointer para a aula 1
 * @param rhs pointer para a aula 2
 * @return true se a aula 1 for antes da aula 2, caso contrário false
 */
bool Aula::cmp(Aula* lhs, Aula* rhs){
    return (dias[lhs->dia_semana] < dias[rhs->dia_semana]) ||
    ((dias[lhs->dia_semana] == dias[rhs->dia_semana]) && (lhs->hora_inicio < rhs->hora_inicio)) ||
    ((dias[lhs->dia_semana] == dias[rhs->dia_semana]) && (lhs->hora_inicio == rhs->hora_inicio) && lhs->tipo < rhs->tipo) ||
    ((dias[lhs->dia_semana] == dias[rhs->dia_semana]) && (lhs->hora_inicio == rhs->hora_inicio) && (lhs->tipo == rhs->tipo) && (lhs->codigo_turma < rhs->codigo_turma));
}

/**
 * Verifica se duas aulas ocorrem em simultâneo\n
 * Complexidade: O(1)
 * @param aula pointer para a aula a ser comparada
 * @return true se as aulas se sobrepõe, caso contrário false
 */
bool Aula::sobrepoe(Aula* aula) const{
    return (dia_semana == aula->dia_semana) &&
            (((hora_inicio < aula->hora_inicio) && (duracao+hora_inicio > aula->hora_inicio)) ||
            ((aula->hora_inicio < hora_inicio) && (aula->duracao+aula->hora_inicio > hora_inicio)));
}

/**
 * Mostra a hora de início, a hora de fim e o tipo da aula\n
 * Complexidade: O(1)
 */
void Aula::show() const{
    std::cout << "   " << hora_inicio << " - " << hora_inicio+duracao << " | " << tipo;
}
/**
 * Dicionário de conversão entre dias da semana (inglês) e inteiros
 */
Aula::Days Aula::dias = dias_semana();
/**
 * Dicionário de conversão entre dias da semana (inglês para português)
 */
Aula::Conversion Aula::portugues= para_portugues();

/**
 * Obtém a hora de início da aula\n
 * Complexidade: O(1)
 * @return hora de início
 */
double Aula::get_hora_inicio() const {return hora_inicio;}
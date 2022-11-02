#include "Pedido.h"
/**
 * Construtor da classe Pedido, recebe o tipo (adicionar, alterar,remover, trocar), estudante 1, turma 1 e estudante 2(caso apenas receba três parâmetros, o estudante 2 é um nullptr)
 * @param tipo
 * @param turma
 * @param estudante1
 * @param estudante2
 */
Pedido::Pedido(int tipo, Turma* turma, Estudante* estudante1, Estudante* estudante2){
    this->estudante1 = estudante1;
    this->estudante2 = estudante2;
    this->turma1 = turma;
    this->tipo = tipo;
}
/**
 * Retorna o tipo do pedido
 * @return
 */
int Pedido::get_tipo() const {return tipo; }
/**
 * Retorna o estudante 1 que fez o pedido
 * @return
 */
Estudante* Pedido::get_estudante1() const {return estudante1; }
/**
 * Retorna o estudante 2 que fez o pedido
 * @return
 */
Estudante* Pedido::get_estudante2() const {return estudante2; }
/**
 * Retorna a turma do pedido
 * @return
 */
Turma* Pedido::get_turma() const {return turma1; }

bool Pedido::cmp(Pedido* pedido1, Pedido* pedido2){return (pedido1->tipo < pedido2->tipo);}

Pedido::OpMap Pedido::tipos = init_map();
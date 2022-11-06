#include "Pedido.h"

/**
 * Construtor da classe Pedido
 * @param tipo (1) Adicionar / (2) Remover / (3) Alterar / (4) Trocar
 * @param turma pointer para a turma do pedido
 * @param estudante1 pointer para o estudante que fez o pedido
 * @param estudante2 pointer para o estudante com quem o estudante 1 quer trocar / nullpointer
 */
Pedido::Pedido(int tipo, Turma* turma, Estudante* estudante1, Estudante* estudante2){
    this->estudante1 = estudante1;
    this->estudante2 = estudante2;
    this->turma1 = turma;
    this->tipo = tipo;
}

/**
 * Obtém o tipo do pedido\n \n
 * <b>Complexidade\n</b>
 * <pre>
 *      <b>O(1)</b>
 * </pre>
 * @return tipo do pedido
 */
int Pedido::get_tipo() const {return tipo; }

/**
 * Obtém o estudante que fez o pedido\n \n
 * <b>Complexidade\n</b>
 * <pre>
 *      <b>O(1)</b>
 * </pre>
 * @return pointer para o estudante que fez o pedido
 */
Estudante* Pedido::get_estudante1() const {return estudante1; }

/**
 * Obtém o estudante com quem o estudante 1 quer trocar\n \n
 * <b>Complexidade\n</b>
 * <pre>
 *      <b>O(1)</b>
 * </pre>
 * @return pointer para o estudante com quem o estudante 1 quer trocar
 */
Estudante* Pedido::get_estudante2() const {return estudante2; }

/**
 * Obtém a turma do pedido\n \n
 * <b>Complexidade\n</b>
 * <pre>
 *      <b>O(1)</b>
 * </pre>
 * @return pointer para a turma do pedido
 */
Turma* Pedido::get_turma() const {return turma1; }

/**
 * Dicionário de conversão entre número inteiro e tipo de pedido\n
 */
Pedido::OpMap Pedido::tipos = init_map();

/**
 * Método de comparação entre dois pedidos de acordo com o seu tipo\n \n
 * <b>Complexidade\n</b>
 * <pre>
 *      <b>O(1)</b>
 * </pre>
 * @param pedido1 pointer para o pedido 1
 * @param pedido2 pointer para o pedido 2
 * @return true se o tipo do pedido 1 for menor que o tipo do pedido 2, caso contrário false
 */
bool Pedido::cmp(Pedido* pedido1, Pedido* pedido2) {return (pedido1->tipo < pedido2->tipo);}


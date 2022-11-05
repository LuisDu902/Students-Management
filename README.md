# README

Antes de fazer build, certifique-se de que alterou os paths dos ficheiros nos métodos/construtores que se seguem:

		Menu::Menu();
		void Gestao::atualiza_estudantes();
		void Gestao::arquivo_pedidos();
		void Gestao::criacao_aulas();
		void Gestao::criacao_turmas();
		void Gestao::criacao_estudantes(int n);
		void Gestao::leitura_pedidos();

Note também que nas linhas 367, 391, 422 e 437 de "Gestao.cpp" foram inseridas condições que retiram o caractere '\r' do final dos ficheiros lidos, uma vez que este estava a causar problemas aquando da leitura dos respetivos ficheiros em Linux e MacOS, que ficam assim resolvidos.

/* Componentes da Equipe
Felipe Brasileiro
João Humberto Braz
Pedro Caria
Rui Couro
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct
{
	char nome[30];					 //
	int coordMax[2];				 //
	int qtdGuerreirosDisponiveis[3]; //
	int vez;						 // Indica se é a vez do jogador
	char especial;					 // Caractere do guerreiro especial
	int partidas[2];				 // 0- Vencidas  1- Perdidas
	int selecionado;				 // Indica se o jogador foi selecionado pra começar o jogo
	int totalDisponivel;
	int guerreirosVivos;
	int cooldownEspecialMax; // Rodadas maximas
	int cooldownEspecialAtual;
	int pernaQuebrada[2];	// Coordenadas do Guerreiro com a perna quebrada
	int pernaQuebradaMax;	// Tempo maximo com a perna quebrada
	int pernaQuebradaAtual; // Tempo com a perna quebrada
} Jogador;

void delay()
{
#if defined(__APPLE__) || defined(__linux__)
	system("sleep 2");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 2 127.0.0.1 > NUL");
#endif
}

void limparTela() // Funcao que vai checar o sistema operacional e executar comandos para limpar a tela de acordo com ele
{
#if defined(__APPLE__) || defined(__linux__)
	system("clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("CLS");
#endif
}

void limparTelaDelay() // Funcao que vai checar o sistema operacional e executar comandos para limpar a tela de acordo com ele e vai dar um delay de 4 segundos
{
#if defined(__APPLE__) || defined(__linux__)
	system("sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
#endif
}

void printLogo() // Funçao que vai printar o Logo do jogo
{
	printf("   _________ __         .__       __________                   .___             __  .__                      \n");
	printf(" /   _____//  |________|__|__  __\\______   \\_______  ____   __| _/_ __   _____/  |_|__| ____   ____   ______\n");
	printf(" \\_____  \\\\   __\\_  __ \\  \\  \\/  /|     ___/\\_  __ \\/  _ \\ / __ |  |  \\_/ ___\\   __\\  |/  _ \\ /    \\ /  ___/\n");
	printf(" /        \\|  |  |  | \\/  |>    < |    |     |  | \\(  <_> ) /_/ |  |  /\\  \\___|  | |  (  <_> );   |  \\___ \\ \n");
	printf("/_______  /|__|  |__|  |__/__/\\_ \\|____|     |__|   \\____/\\____ |____/  \\___  >__| |__|\\____/|___|  /____  >\n");
	printf("        \\/                      \\/                             \\/           \\/                    \\/     \\/ \n");
	printf("__________                                      __               \n");
	printf("\\______   \\_______   ____   ______ ____   _____/  |_  ______     \n");
	printf(" |     ___/\\_  __ \\_/ __ \\ /  ___// __ \\ /    \\   __\\/  ___/     \n");
	printf(" |    |     |  | \\/\\  ___/ \\___ \\   ___/|   |  \\  |  \\___ \\      \n");
	printf(" |____|     |__|    \\___  >____  >\\___  >___|  /__| /____  >     \n");
	printf("                        \\/     \\/     \\/     \\/          \\/      \n");

	limparTelaDelay();

	printf("__________        __         .__  .__                                  		\n");
	printf("\\______   \\____ _/  |______  |  | |  |__ _____    ______               	\n");
	printf(" |    |  _|__  \\   __ \\__  \\ |  | |  |  \\ __  \\  /  ___/               \n");
	printf(" |    |   \\/ __ \\|  |  / __ \\|  |_|   Y  \\/ __ \\_\\___ \\              \n");
	printf(" |______  (____  /__| (____  /____/___|  (____  /____  >               		\n");
	printf("        \\/     \\/          \\/          \\/     \\/     \\/               \n");
	printf("________                                                               		\n");
	printf("\\______ \\ _____                                                        	\n");
	printf(" |    |  \\__   \\                                                       	\n");
	printf(" |    `   \\/ __ \\_                                                     	\n");
	printf("/_______  (____  /                                                     		\n");
	printf("        \\/     \\/                                                      	\n");
	printf(".____                                .__                               		\n");
	printf("|    |   _____  ______   ____   ____ |__|____                          		\n");
	printf("|    |   \\__  \\ \\____ \\ /  _ \\ /    \\|  \\__  \\                      \n");
	printf("|    |___ / __ \\|  |_> >  <_> )   |  \\  |/ __ \\_                        	\n");
	printf("|_______ (____  /   __/ \\____/|___|  /__(____  /                         	\n");
	printf("        \\/    \\/|__|               \\/        \\/                        	\n");

	limparTelaDelay();
}

void configCampo(char campo[12][12], int demo) // Funçao que vai preencher os espaços da matriz com os caracteres do campo
{

	if (!demo)
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (i == 0 || i == 11)
				{
					campo[i][j] = '*';
				}
				else if (i == 5 || i == 6)
				{
					campo[i][j] = '~';
				}
				else
				{
					campo[i][j] = '.';
				}
			}
			campo[i][0] = '*';
			campo[i][11] = '*';
		}
	}
}

void printCampo(char campo[12][12], int limpar) // Funcao que vai printar o campo e numeraçoes para auxiliar o usuario
{
	printf("0 1 2 3 4 5 6 7 8 9 10 11\n-------------------------\n");
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (limpar)
			{
				if (campo[i][j] == 'X')
				{
					campo[i][j] = '.';
				}
			}
			printf("%c ", campo[i][j]);
		}
		printf(" | %i\n", i);
	}
}
// -----------
// Inicio de Jogo
void getNomeJogador(Jogador *ptr_j1, Jogador *ptr_j2) // Funcao que vai pegar o nome dos jogadores
{

	printf("Digite o nome do player 1: ");
	scanf("%s", ptr_j1->nome);

	// system("CLS");

	printf("Digite o nome do player 2: ");
	scanf("%s", ptr_j2->nome);
}

void sorteioJogador(Jogador *ptr_j1, Jogador *ptr_j2) // Funçao que vai sortear o jogador que começa a jogar
{
	srand(time(NULL));
	if (rand() % 2 == 0) // Caso o valor randomico seja 0, vai selecionar o jogador1
	{
		ptr_j1->selecionado = 1; // Marcando que o jogador1 foi selecionado para ser o 1o a jogar
		ptr_j2->selecionado = 0;
	}
	else // Caso seja diferente de 0, o jogador2 vai ser selecionado
	{
		ptr_j1->selecionado = 0;
		ptr_j2->selecionado = 1; // Marcando que o jogador2 foi selecionado para ser o 1o a jogar
	}
}

void mostrarGuerreirosAlocacao(Jogador *ptr_j)
{
	printf("\nQUANTIDADE DE GUERREIROS\n");
	printf(" ---------------------------\n");
	printf("| Guerreiro 1        |  %d  |\n", ptr_j->qtdGuerreirosDisponiveis[0]);
	printf(" ---------------------------\n");
	printf("| Guerreiro 2        |  %d  |\n", ptr_j->qtdGuerreirosDisponiveis[1]);
	printf(" ---------------------------\n");
	printf("| Guerreiro Especial |  %d  |\n", ptr_j->qtdGuerreirosDisponiveis[2]);
	printf(" ---------------------------\n");
}

int alocarGuerreiros(Jogador *ptr_j, char campo[12][12]) // Funcao que vai posicionar os guerreiros no campo
{
	if (ptr_j->totalDisponivel == 0)
	{
		return 0;
	}
	char tipoGuerreiro;
	int erro = 0;
	int lin, col;

	printCampo(campo, 1);
	mostrarGuerreirosAlocacao(ptr_j);
	printf("Quantidade de Guerreiros disponíveis: %d\n", ptr_j->totalDisponivel);
	if (ptr_j->selecionado)
	{
		printf("SEU CAMPO É O DE CIMA\n");
	}
	else
	{
		printf("SEU CAMPO É O DE BAIXO\n");
	}
	printf("%s, posicione suas tropas digitando o numero da coluna e o da linha, EX: 0 2\n", ptr_j->nome);
	scanf("%i %i", &col, &lin);
	fflush(stdin);

	//delimitando os locais possiveis para alocacao da tropa no tabuleiro
	if (lin > ptr_j->coordMax[0] && lin < ptr_j->coordMax[1] && col > 0 && col < 11 && campo[lin][col] == '.') // Vai checar se a linha é maior que o "valor minimo" do campo e menor que o maximo
	//Por ex: se o usuario estiver no campo de cima e digitar 0 0 n vai cair no if pq a linha é igual ao espaço das montanhas
	// Para o campo de cima: coordMax[0] é a linha das montanhas e coordMax[1] é a 1a linha do rio
	// Para o campo de baixo: coordMax[0] é a 2a linha do rio e coordMax[1] é a linha da montanha
	{

		printf("Qual tipo de guerreiro? (1 (Ataca somente para frente) ou 2 (Ataca somente nas diagonais) ou %c (Guerreiro especial))\n", ptr_j->especial);
		printf("Escreva: ");
		scanf("%c", &tipoGuerreiro);
		fflush(stdin);
		if (tipoGuerreiro == '1' && ptr_j->qtdGuerreirosDisponiveis[0] > 0) // Se o tipo do guerreiro for igual a '1' e ainda tiver tropas desse tipo disponiveis cai nesse if
		{
			campo[lin][col] = tipoGuerreiro;
			ptr_j->qtdGuerreirosDisponiveis[0]--;
			ptr_j->totalDisponivel--;
			limparTela();
			printCampo(campo, 1);
			printf("Você ainda pode posicionar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[0], tipoGuerreiro);
		}
		else if (tipoGuerreiro == '2' && ptr_j->qtdGuerreirosDisponiveis[1] > 0) // Se o tipo do guerreiro for igual a '1' e ainda tiver tropas desse tipo disponiveis cai nesse if
		{
			campo[lin][col] = tipoGuerreiro;
			ptr_j->qtdGuerreirosDisponiveis[1]--;
			ptr_j->totalDisponivel--;
			limparTela();
			printCampo(campo, 1);
			printf("Você ainda pode posicionar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[1], tipoGuerreiro);
		}
		else if (tipoGuerreiro == ptr_j->especial && ptr_j->qtdGuerreirosDisponiveis[2] > 0) // Se o tipo do guerreiro for igual ao caractere especial e ainda tiver tropas desse tipo disponiveis cai nesse else if
		{
			campo[lin][col] = tipoGuerreiro;
			ptr_j->qtdGuerreirosDisponiveis[2]--;
			ptr_j->totalDisponivel--;
			limparTela();
			printCampo(campo, 1);
			printf("Você ainda pode posicionar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[2], tipoGuerreiro);
		}
		else // vai cair nesse else caso o usuario digite um guerreiro inexistente ou tente escolher um tipo de guerreiro que ja foi todo posicionado
		{
			limparTela();
			printf("Você não pode fazer isso\n");
			erro = 1;
		}
	}
	else // Vai cair nesse else caso o usuario tenha digitado um valor fora do seu campo ou um valor ja ocupado por uma tropa
	{
		limparTela();
		printf("Posição inválida, tente novamente.\n");
		erro = 1;
	}
	limparTelaDelay();

	return erro; // Esse "erro" vai ser o valor retornado pela funçao, podendo ser 1 (caso tenha ocorrido algum erro) ou 0 (sem erros)
}

void inicioPartida(Jogador *ptr_j1, Jogador *ptr_j2, char campo[12][12], int demo, int final) // Vai atribuir valores as variaveis necessarias para o inicio do jogo e chamar a funcao para alocar os guerreiros
{
	if (final)
	{
		ptr_j1->guerreirosVivos = 1;
		ptr_j2->guerreirosVivos = 1;
		ptr_j1->totalDisponivel = 1;
		ptr_j2->totalDisponivel = 1;
	}
	else
	{
		ptr_j1->guerreirosVivos = 9;
		ptr_j2->guerreirosVivos = 9;
		ptr_j1->totalDisponivel = 9;
		ptr_j2->totalDisponivel = 9;
	}
	// Iniciando variaveis necessarias para o inicio do jogo

	ptr_j1->qtdGuerreirosDisponiveis[0] = 4; // Guerreiro tipo 1 - ataque vertical
	ptr_j1->qtdGuerreirosDisponiveis[1] = 4; // Guerreiro tipo 2 - ataque diagonal
	ptr_j1->qtdGuerreirosDisponiveis[2] = 1; // Guerreiro especial - ataque especial

	ptr_j2->qtdGuerreirosDisponiveis[0] = 4; // Guerreiro tipo 1 - ataque vertical
	ptr_j2->qtdGuerreirosDisponiveis[1] = 4; // Guerreiro tipo 2 - ataque diagonal
	ptr_j2->qtdGuerreirosDisponiveis[2] = 1; // Guerreiro especial - ataque especial

	if (ptr_j1->selecionado)
	{
		printf("%s, o seu campo eh o de baixo\n", ptr_j2->nome);
		ptr_j2->especial = '@';	  // Setando o caractere do guerreiro especial do campo de baixo
		ptr_j2->coordMax[0] = 6;  // Setando as coord maximas da linha que esse usuario vai poder jogar, ou seja, setando o campo
		ptr_j2->coordMax[1] = 11; // nesse caso vai ser (6, 11), entao o jogador vai poder jogar da linha 7 ate a linha 10, pq 6 é o rio e 11 é a montanha
		ptr_j2->vez = 0;
		ptr_j2->cooldownEspecialMax = 4;
		ptr_j2->cooldownEspecialAtual = 0;
		printf("%s comeca\n", ptr_j1->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j1->especial = '#';	 // Setando o caractere do guerreiro especial do campo de cima
		ptr_j1->coordMax[0] = 0; // Setando as coord maximas da linha que esse usuario vai poder jogar, ou seja, setando o campo
		ptr_j1->coordMax[1] = 5; // nesse caso vai ser (0, 5), entao o jogador vai poder jogar da linha 1 ate a linha 4, pq 0 é a montanha e 5 é rio
		ptr_j1->vez = 1;		 // Se o jogador1 for selecionado pelo sorteio, ele vai começar o jogo
		ptr_j1->cooldownEspecialMax = 3;
		ptr_j1->cooldownEspecialAtual = 0;
	}
	else
	{

		printf("%s, o seu campo eh o de baixo\n", ptr_j1->nome);
		ptr_j1->especial = '@';
		ptr_j1->coordMax[0] = 6;
		ptr_j1->coordMax[1] = 11;
		ptr_j1->vez = 0;
		ptr_j1->cooldownEspecialMax = 4;
		ptr_j1->cooldownEspecialAtual = 0;
		printf("%s comeca\n", ptr_j2->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j2->especial = '#';
		ptr_j2->coordMax[0] = 0;
		ptr_j2->coordMax[1] = 5;
		ptr_j2->vez = 1; // Se o jogador2 for selecionado pelo sorteio, ele vai começar o jogo
		ptr_j2->cooldownEspecialMax = 3;
		ptr_j2->cooldownEspecialAtual = 0;
	}
	// --------------------------
	if (!demo)
	{
		while (ptr_j1->totalDisponivel > 0 || ptr_j2->totalDisponivel > 0) // Enquanto os jogadores ainda tiverem guerreiros a serem colocados, ficara nesse loop
		{
			if (ptr_j1->vez) // Se for a vez do Jogador1 jogar vai executar isso
			{

				while (alocarGuerreiros(ptr_j1, campo)) // O while vai executar a funçao para alocar o guerreiro e vai continuar executando caso seja retornado 1 (erro)
				{
				}
				ptr_j1->vez = 0;
				ptr_j2->vez = 1; // Seta que eh a vez do jogador2 jogar
			}
			if (ptr_j2->vez)
			{
				while (alocarGuerreiros(ptr_j2, campo)) // O while vai executar a funçao para alocar o guerreiro e vai continuar executando caso seja retornado 1 (erro)
				{
				}
				ptr_j2->vez = 0;
				ptr_j1->vez = 1; // Seta que eh a vez do jogador2 jogar
			}
		}
	}
}
// ------------
// Meio / Fim de jogo
int checkVencedor(Jogador *ptr_j1, Jogador *ptr_j2, char campo[12][12])
{
	if (ptr_j2->guerreirosVivos <= 0)
	{
		limparTela();
		printCampo(campo, 1);
		printf("%s GANHOU!!\n", ptr_j1->nome);
		return 1;
	}
	else if (ptr_j1->guerreirosVivos <= 0)
	{
		limparTela();
		printCampo(campo, 1);
		printf("%s GANHOU!!\n", ptr_j2->nome);
		return 1;
	}
	else
	{
		return 0;
	}
}

void decCooldown(Jogador *ptr_j)
{
	if (ptr_j->cooldownEspecialAtual < 0) // Vai verificar se o cooldown é 0 ou negativo e atribuir 0
	{
		ptr_j->cooldownEspecialAtual--;
	}
}

void decPernaQuebrada(Jogador *ptr_j)
{
	if (ptr_j->selecionado == 0)
	{
		if (ptr_j->pernaQuebradaAtual > 0)
		{
			ptr_j->pernaQuebradaAtual--;
		}
		if (ptr_j->pernaQuebradaAtual == 0)
		{
			ptr_j->pernaQuebrada[0] = 999;
			ptr_j->pernaQuebrada[1] = 999;
		}
	}
}

int movimentoEspecial(Jogador *ptr_j, char campo[12][12], char tipoGuerreiro, int lin, int col)
{
	int lin2, col2, erro = 0;
	char guerreiroTroca;

	printf("Digite a posição do guerreiro que você quer trocar de lugar\n");
	scanf("%d %d", &col2, &lin2);
	if (lin > ptr_j->coordMax[0] && lin < ptr_j->coordMax[1] && col > 0 && col < 11) // Checa se o jogador escolheu uma posição no proprio campo
	{
		if (campo[lin2][col2] == '1' || campo[lin2][col2] == '2') // Checa se tem um guerreiro na posição escolhida
		{
			guerreiroTroca = campo[lin2][col2]; // Salva o guerreiro q ta na posição escolhida dentro da funçao
			campo[lin2][col2] = tipoGuerreiro;	// Coloca o guerreiro especial na posição escolhida
			campo[lin][col] = guerreiroTroca;	// Coloca o guerreiro na posição que o guerreiro especial estáva
			if (ptr_j->pernaQuebrada[0] == col && ptr_j->pernaQuebrada[1] == lin)
			{
				ptr_j->pernaQuebrada[0] = col2;
				ptr_j->pernaQuebrada[1] = lin2;
			}
			else if (ptr_j->pernaQuebrada[0] == col2 && ptr_j->pernaQuebrada[1] == lin2)
			{
				ptr_j->pernaQuebrada[0] = col;
				ptr_j->pernaQuebrada[1] = lin;
			}

			// printCampo(campo, 1);
		}
		else
		{
			limparTela();
			printCampo(campo, 1);
			printf("Não existe guerreiros nessa posição\n");
			erro = 1;
		}
	}
	else
	{
		limparTela();
		printf("Você não pode jogar nesse campo\n");
		erro = 1;
	}
	limparTela();
	return erro; // Caso tenha algum erro, retorna 1 (Logo, sai da funçao e não executa td oq estiver abaixo disso)
}

int movimentoJoao(Jogador *ptr_j, char campo[12][12], char tipoGuerreiro, int lin, int col)
{
	int direcaoMOV, erro = 0;

	// Caso o Guerreiro seja "normal" executa essa parte
	printf("Cima = 1 \nBaixo = 2 \nEsquerda = 3 \nDireita = 4 \n");
	if (tipoGuerreiro == ptr_j->especial)
	{
		printf("Movimento Especial = 99\n");
		scanf("%d", &direcaoMOV);
		if (direcaoMOV == 99)
		{
			while (movimentoEspecial(ptr_j, campo, tipoGuerreiro, lin, col))
			{
			}
			return erro;
		}
	}
	else
	{
		scanf("%d", &direcaoMOV);
	}

	//verificar se a operacao foi efetuada ou ocorreu algum erro e o usuario precisa digitar novamente
	if (direcaoMOV == 1 || direcaoMOV == 2 || direcaoMOV == 3 || direcaoMOV == 4)
	{

		//se a direção for para cima
		if (direcaoMOV == 1 && campo[lin - 1][col] == '.')
		{
			limparTela();
			campo[lin][col] = '.';
			campo[lin - 1][col] = tipoGuerreiro;
		}

		//se a direção for para baixo
		else if (direcaoMOV == 2 && campo[lin + 1][col] == '.')
		{
			limparTela();
			campo[lin][col] = '.';
			campo[lin + 1][col] = tipoGuerreiro;
		}

		//se a direção for para esquerda
		else if (direcaoMOV == 3 && campo[lin][col - 1] == '.')
		{
			limparTela();
			campo[lin][col] = '.';
			campo[lin][col - 1] = tipoGuerreiro;
		}

		//se a direção for para direita
		else if (direcaoMOV == 4 && campo[lin][col + 1] == '.')
		{
			limparTela();
			campo[lin][col] = '.';
			campo[lin][col + 1] = tipoGuerreiro;
		}
		else
		{
			limparTela();
			printf("Posição não disponível, tente novamente\n");
			erro = 1;
		}
	}
	else
	{
		limparTela();
		printf("Opção inválida, tente novamente\n");
		erro = 1;
	}
	return erro;
}

int ataqueVertical(Jogador *ptr_j, Jogador *ptr_j2, char campo[12][12], char tipoGuerreiro, int lin, int col)
{
	int erro = 0;
	if (lin > ptr_j->coordMax[0] && lin < ptr_j->coordMax[1])
	{
		if (ptr_j->selecionado) // Campo de cima
		{
			for (int i = lin + 1; i < 11; i++)
			{
				if (i <= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
				{
					limparTela();
					printf("O guerreiro está sendo bloqueado por outro\n");
					printf("Você não atacou ninguém\n");
					erro = 1;
					break;
				}
				else if (i >= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
				{
					limparTela();
					printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
					campo[i][col] = 'X';
					ptr_j2->guerreirosVivos--;
					erro = 0;
					break;
				}
			}

			printCampo(campo, 0);
			delay();
			limparTela();
		}
		else
		{
			for (int i = lin - 1; i > 0; i--)
			{
				// printf("Ataque passando pela linha: %d\n", i);
				if (i >= ptr_j->coordMax[0] && campo[i][col] != '.' && campo[i][col] != '~')
				{
					limparTela();
					printf("O guerreiro está sendo bloqueado por outro\n");
					printf("Você não atacou ninguém\n");
					erro = 1;
					break;
				}
				else if (i <= ptr_j->coordMax[0] && campo[i][col] != '.' && campo[i][col] != '~')
				{
					limparTela();
					printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
					campo[i][col] = 'X';
					ptr_j2->guerreirosVivos--;
					erro = 0;
					break;
				}
			}

			printCampo(campo, 0);
			delay();
			limparTela();
		}
	}
	else
	{
		limparTela();
		printf("Você não pode jogar nesse campo\n");
		erro = 1;
	}
	return erro;
}

int ataqueDiagonal(Jogador *ptr_j, Jogador *ptr_j2, char campo[12][12], char tipoGuerreiro, int lin, int col, int direcao)
{
	int erro = 0, qtd;

	if (ptr_j->selecionado && direcao == 1)
	{
		col = col + 1;
		for (int i = lin + 1; i < 11; i++)
		{

			// printf("i = %d", i);
			if (col >= 11)
			{
				limparTela();
				printf("Você não atacou ninguém\n");
				return erro;
			}

			if (i <= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("O guerreiro está sendo bloqueado por outro\n");
				printf("Você não atacou ninguém\n");
				erro = 1;
				break;
			}
			else if (i >= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
				campo[i][col] = 'X';
				ptr_j2->guerreirosVivos--;
				break;
			}
			col += 1;
		}

		printCampo(campo, 0);
		delay();
		limparTela();
	}
	else if (ptr_j->selecionado && direcao == 2)
	{
		col = col - 1;
		for (int i = lin + 1; i < 11; i++)
		{

			if (col <= 0)
			{
				limparTela();
				printf("Você não atacou ninguém\n");
				return erro;
			}

			if (i <= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("O guerreiro está sendo bloqueado por outro\n");
				printf("Você não atacou ninguém\n");
				erro = 1;
				break;
			}
			else if (i >= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
				campo[i][col] = 'X';
				ptr_j2->guerreirosVivos--;
				break;
			}
			col--;
		}

		printCampo(campo, 0);
		delay();
		limparTela();
	}

	//Campo de baixo
	else if (!ptr_j->selecionado && direcao == 1)
	{
		col = col + 1;
		for (int i = lin - 1; i > 0; i--)
		{

			if (col >= 11)
			{
				limparTela();
				printf("Você não atacou ninguém\n");
				return erro;
			}
			if (i >= ptr_j->coordMax[0] && i <= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("O guerreiro está sendo bloqueado por outro\n");
				printf("Você não atacou ninguém\n");
				erro = 1;
				break;
			}
			else if (i <= ptr_j->coordMax[0] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
				campo[i][col] = 'X';
				ptr_j2->guerreirosVivos--;
				break;
			}
			col++;
		}

		printCampo(campo, 0);
		delay();
		limparTela();
	}
	else if (!ptr_j->selecionado && direcao == 2)
	{
		col = col - 1;
		for (int i = lin - 1; i > 0; i--)
		{
			erro = 0;
			if (col <= 0)
			{
				limparTela();
				printf("Você não atacou ninguém\n");
				return erro;
			}
			if (i >= ptr_j->coordMax[0] && i <= ptr_j->coordMax[1] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("O guerreiro está sendo bloqueado por outro\n");
				printf("Você não atacou ninguém\n");
				erro = 1;
				break;
			}
			else if (i <= ptr_j->coordMax[0] && campo[i][col] != '.' && campo[i][col] != '~')
			{
				limparTela();
				printf("%s matou um guerreiro do tipo %c\n", ptr_j->nome, campo[i][col]);
				campo[i][col] = 'X';
				ptr_j2->guerreirosVivos--;
				break;
			}
			col--;
		}
		printCampo(campo, 0);
		delay();
		limparTela();
	}
	else
	{
		erro = 1;
	}
	return erro;
}

int ataqueEspecial(Jogador *ptr_j, Jogador *ptr_j2, char campo[12][12], char tipoGuerreiro)
{
	int erro = 0;
	int lin1, col1, lin2, col2;
	char guerreiroPos1;
	if (tipoGuerreiro == '@') // Campo de baixo
	{
		printf("Escolha 2 inimigos para que eles troquem, entre si, suas posições. Digite as coordenadas no seguinte formato: x y\nGuerreiro 1: ");
		scanf("%d %d", &col1, &lin1);
		if (lin1 < ptr_j->coordMax[0] && col1 > 0 && col1 < 11)
		{
			if (campo[lin1][col1] != '*' && campo[lin1][col1] != '~')
			{
				guerreiroPos1 = campo[lin1][col1];
				do
				{
					printf("Guerreiro 2: ");
					scanf("%d %d", &col2, &lin2);
					if (lin2 < ptr_j->coordMax[0] && col2 > 0 && col2 < 11)
					{
						if (campo[lin2][col2] != '*' && campo[lin2][col2] != '~')
						{
							campo[lin1][col1] = campo[lin2][col2];
							campo[lin2][col2] = guerreiroPos1;
							erro = 0;
							ptr_j->cooldownEspecialAtual = ptr_j->cooldownEspecialMax;
							limparTela();
						}
						else
						{
							limparTela();
							printf("Você precisa escolher um guerreiro\n");
							erro = 1;
						}
					}
					else
					{
						limparTela();
						printf("Você não pode escolher um guerreiro do seu campo\n");
						erro = 1;
					}
				} while (erro);
			}
		}
		else
		{
			limparTela();
			printf("Você não pode escolher um guerreiro do seu campo\n");
			erro = 1;
		}
	}
	else if (tipoGuerreiro == '#') // Campo de cima
	{
		printf("Entre a cordenada do inimigo que deseja \"quebrar a perna\" (Formato: x y): ");
		scanf("%d %d", &col1, &lin1);
		if (lin1 > ptr_j->coordMax[1] && col1 > 0 && col1 < 11)
		{
			if (campo[lin1][col1] != '*' && campo[lin1][col1] != '~')
			{
				ptr_j2->pernaQuebrada[0] = col1;
				ptr_j2->pernaQuebrada[1] = lin1;
				ptr_j2->pernaQuebradaMax = ptr_j2->pernaQuebradaAtual = 2;
				limparTela();
				printf("Guerreiro %c foi paralizado\n", campo[lin1][col1]);
				ptr_j->cooldownEspecialAtual = ptr_j->cooldownEspecialMax;
				erro = 0;
				printCampo(campo, 1);
				delay();
				limparTela();
			}
			else
			{
				limparTela();
				printf("Você precisa escolher um guerreiro\n");
				erro = 1;
			}
		}
		else
		{
			limparTela();
			printf("Você precisa selecionar um guerreiro no seu campo\n");
			erro = 1;
		}
	}

	return erro;
}

int menuEscolhaMovAtk(Jogador *ptr_j, Jogador *ptr_j2, char campo[12][12])
{

	int opcaoMOVouATAC;
	char tipoGuerreiro;
	int lin, col, erro = 0, direcao;
	printCampo(campo, 1);

	printf("%s, digite as coordenadas do guerreiro que deseja selecionar: ", ptr_j->nome);
	scanf("%d %d", &col, &lin);

	//checa se o jogador escolheu um lugar no seu proprio campo
	if (lin > ptr_j->coordMax[0] && lin < ptr_j->coordMax[1] && col > 0 && col < 11)
	{
		if (campo[lin][col] == '1' || campo[lin][col] == '2' || campo[lin][col] == ptr_j->especial) // checa se o jogador escolheu algum guerreiro
		{
			printf("Para movimentar digite -> 1\nPara atacar digite -> 2\n");
			printf("Opção: ");
			scanf("%d", &opcaoMOVouATAC);

			//se a opcao escolhida for movimentar:
			if (opcaoMOVouATAC == 1)
			{
				if (ptr_j->pernaQuebrada[0] == col && ptr_j->pernaQuebrada[1] == lin)
				{
					limparTela();
					printf("Você não pode mover esse guerreiro por %d rodadas\n", ptr_j->pernaQuebradaAtual);
					delay();
					return 1;
				}
				tipoGuerreiro = campo[lin][col]; // "salva" o guerreiro q estáva na posição original para poder movimentar
				while (movimentoJoao(ptr_j, campo, tipoGuerreiro, lin, col))
				{
				}
			}

			//se a opcao escolhida for atacar
			else if (opcaoMOVouATAC == 2)
			{
				//chama a funçao de ataque
				if (campo[lin][col] == '1')
				{
					erro = ataqueVertical(ptr_j, ptr_j2, campo, tipoGuerreiro, lin, col);
				}
				else if (campo[lin][col] == '2')
				{
					printf("Para qual direçao vc quer atirar? \nDireita -> 1\nEsquerda -> 2\nOpcao: ");
					scanf("%d", &direcao);
					erro = ataqueDiagonal(ptr_j, ptr_j2, campo, tipoGuerreiro, lin, col, direcao);
					// printf("ERRO: %d", erro);
				}
				else if (campo[lin][col] == ptr_j->especial)
				{
					tipoGuerreiro = campo[lin][col];
					if (ptr_j->cooldownEspecialAtual > 0)
					{
						limparTela();
						printf("Você ainda tem que esperar %d rodadas para poder atacar\n", ptr_j->cooldownEspecialAtual);
						delay();
						erro = 1;
					}
					else
					{
						erro = ataqueEspecial(ptr_j, ptr_j2, campo, tipoGuerreiro);
					}
				}
			}
			else
			{
				limparTela();
				printf("Comando inválido\n");
				erro = 1;
			}
		}
		else
		{
			printf("Você não possui guerreiros nessa posição\n");
			erro = 1;
		}
	}
	else
	{
		limparTela();
		printf("Você só pode selecionar um guerreiro que esteja dentro do seu campo\n");
		erro = 1;
	}
	return erro;
}

void meioPartida(Jogador *ptr_j1, Jogador *ptr_j2, char campo[12][12])
{
	while (1)
	{
		if (ptr_j1->vez) // Se for a vez do Jogador1 jogar vai executar isso
		{
			printf("VEZ DE %s\nVOCÊ POSSUI %d GUERREIROS VIVOS\n", ptr_j1->nome, ptr_j1->guerreirosVivos);
			while (menuEscolhaMovAtk(ptr_j1, ptr_j2, campo)) // O while vai executar a funçao para mover ou atacar vai continuar executando caso seja retornado 1 (erro)
			{
			}
			ptr_j1->vez = 0;
			ptr_j2->vez = 1; // Seta que eh a vez do jogador2 jogar
			decCooldown(ptr_j1);
			decPernaQuebrada(ptr_j1);
			if (ptr_j2->guerreirosVivos <= 0)
			{
				printf("%s GANHOU!!!\n", ptr_j1->nome);
				break;
			}
		}
		if (ptr_j2->vez)
		{
			printf("VEZ DE %s\nVOCÊ POSSUI %d GUERREIROS VIVOS\n", ptr_j2->nome, ptr_j2->guerreirosVivos);
			while (menuEscolhaMovAtk(ptr_j2, ptr_j1, campo)) // O while vai executar a funçao para mover ou atacar vai continuar executando caso seja retornado 1 (erro)
			{
			}
			ptr_j2->vez = 0;
			ptr_j1->vez = 1; // Seta que eh a vez do jogador1 jogar
			decCooldown(ptr_j2);
			decPernaQuebrada(ptr_j2);
			if (ptr_j1->guerreirosVivos <= 0)
			{
				printf("%s GANHOU!!!\n", ptr_j2->nome);
				break;
			}
		}
	}
}

// ------------------

int main()
{
	setlocale(LC_ALL, "Portuguese");

	printLogo();
	while (1)
	{
		// Declaracao de Variaveis
		char resposta;
		Jogador j1, j2, *ptr_j1, *ptr_j2;
		ptr_j1 = &j1; // Criando ponteiro para j1
		ptr_j2 = &j2; // Criando ponteiro para j2
		//--------------------------

		// !!!! PARA A APRESENTAÇÃO !!!!
		// Primeiro mostra com alocação ai dps faz isso aq
		int demo = 0; // Seta pra 1 pra pular a alocacao na hr da apresentaçao
		// Comentar isso aq
		char campo[12][12];
		// E descomentar isso aq (Caso queira pode mudar a posição de algum guerreiro pra flr alguma coisa, sla):

		// SET JOAO
		// Deixe o demo = 1 e comente os outros campos
		// char campo[12][12] = {'*','*','*','*','*','*','*','*','*','*','*','*',
		//                       '*','.','.','.','#','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','1','1','1','1','.','.','2','2','2','2','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','1','1','1','1','2','2','2','2','@','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','*','*','*','*','*','*','*','*','*','*','*'};

		// SET "ORIGINAL"
		// Deixe o demo = 1 e comente os outros campos
		// char campo[12][12] = {'*','*','*','*','*','*','*','*','*','*','*','*',
		//                       '*','2','.','.','#','.','.','.','.','1','.','*',
		//                       '*','.','.','1','.','2','.','.','1','.','.','*',
		//                       '*','.','.','2','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','1','.','.','2','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','2','.','.','.','.','.','2','.','.','.','*',
		//                       '*','.','.','2','2','.','.','.','.','1','.','*',
		//                       '*','.','.','.','.','1','.','.','1','.','.','*',
		//                       '*','@','1','.','.','.','.','.','.','.','.','*',
		//                       '*','*','*','*','*','*','*','*','*','*','*','*'};

		// SET FINAL
		int final = 0; // coloque como 1 pra falar q so tem 1 guerreiro vivo em cada campo
		// Deixe o demo = 1 e comente os outros campos
		// Pode mostrar o d cima ganhando ai dps anda pro lado e mostra o d baixo ganhando
		// char campo[12][12] = {'*','*','*','*','*','*','*','*','*','*','*','*',
		//                       '*','.','.','.','.','1','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','~','~','~','~','~','~','~','~','~','~','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','.','.','.','.','.','.','*',
		//                       '*','.','.','.','.','1','.','.','.','.','.','*',
		//                       '*','*','*','*','*','*','*','*','*','*','*','*'};

		configCampo(campo, demo);
		// -------------------------------

		getNomeJogador(ptr_j1, ptr_j2);
		limparTela();
		sorteioJogador(ptr_j1, ptr_j2);
		inicioPartida(ptr_j1, ptr_j2, campo, demo, final);
		meioPartida(ptr_j1, ptr_j2, campo);
		fflush(stdin);
		printf("Gostaria de jogar novamente? \nResponda com S para sim e N para não: ");
		scanf("%c", &resposta);
		fflush(stdin);
		if (resposta == 'S')
		{
			printf("Começando novo jogo...\n");
			delay();
			limparTela();
		}
		else if (resposta == 'N')
		{
			printf("Saindo do jogo...\n");
			break;
		}
		else
		{
			printf("Resposta Inválida, saindo do jogo...\n");
			break;
		}
	}

	return 0;
}

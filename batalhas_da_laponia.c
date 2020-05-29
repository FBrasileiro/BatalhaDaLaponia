#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	char nome[30];
	int coordMax[2];
	int qtdGuerreirosDisponiveis[3];
	int vez;
	char especial;
	int partidas[2]; // 0- Vencidas  1- Perdidas
	int selecionado;
	int totalDisponivel;
} Jogador;

// Funcoes

void limparTelaDelay() // Funcao que vai checar o sistema operacional e executar comandos para limpar a tela de acordo com ele e vai dar um delay de 4 segundos
{
#if defined(__APPLE__) || defined(__linux__)
	system("sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
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

void configCampo(char campo[12][12]) // Funçao que vai preencher os espaços da matriz com os caracteres do campo
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

void printCampo(char campo[12][12]) // Funcao que vai printar o campo e numeraçoes para auxiliar o usuario
{
	printf("0 1 2 3 4 5 6 7 8 9 10 11\n-------------------------\n");
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			printf("%c ", campo[i][j]);
		}
		printf(" | %i\n", i);
	}
}

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

int alocarGuerreiros(Jogador *ptr_j, char campo[12][12]) // Funcao que vai posicionar os guerreiros no campo
{
	if (ptr_j->totalDisponivel == 0)
	{
		return 0;
	}
	char tipoGuerreiro;
	int erro = 0;
	int lin, col;

	printCampo(campo);
	printf("Quantidade de Guerreiros disponiveis: %d\n", ptr_j->totalDisponivel);
	printf("%s, posicione suas tropas digitando o numero da linha e o da coluna, EX: 0 2\n", ptr_j->nome);
	scanf("%i %i", &lin, &col);
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
			printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[0], tipoGuerreiro);
		}
		else if (tipoGuerreiro == '2' && ptr_j->qtdGuerreirosDisponiveis[1] > 0) // Se o tipo do guerreiro for igual a '1' e ainda tiver tropas desse tipo disponiveis cai nesse if
		{
			campo[lin][col] = tipoGuerreiro;
			ptr_j->qtdGuerreirosDisponiveis[1]--;
			ptr_j->totalDisponivel--;
			limparTela();
			printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[1], tipoGuerreiro);
		}
		else if (tipoGuerreiro == ptr_j->especial && ptr_j->qtdGuerreirosDisponiveis[2] > 0) // Se o tipo do guerreiro for igual ao caractere especial e ainda tiver tropas desse tipo disponiveis cai nesse else if
		{
			campo[lin][col] = tipoGuerreiro;
			ptr_j->qtdGuerreirosDisponiveis[2]--;
			ptr_j->totalDisponivel--;
			limparTela();
			printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros (%c)\n", ptr_j->qtdGuerreirosDisponiveis[2], tipoGuerreiro);
		}
		else // vai cair nesse else caso o usuario digite um guerreiro inexistente ou tente escolher um tipo de guerreiro que ja foi todo posicionado
		{
			limparTela();
			printf("Voce nao pode fazer isso\n");
			erro = 1;
		}
	}
	else // Vai cair nesse else caso o usuario tenha digitado um valor fora do seu campo ou um valor ja ocupado por uma tropa
	{
		limparTela();
		printf("Posicao invalida, tente novamente.\n");
		erro = 1;
	}
	limparTelaDelay();

	return erro; // Esse "erro" vai ser o valor retornado pela funçao, podendo ser 1 (caso tenha ocorrido algum erro) ou 0 (sem erros)
}

void inicioPartida(Jogador *ptr_j1, Jogador *ptr_j2, char campo[12][12]) // Vai atribuir valores as variaveis necessarias para o inicio do jogo e chamar a funcao para alocar os guerreiros
{
	// Iniciando variaveis necessarias para o inicio do jogo
	ptr_j1->totalDisponivel = 9;
	ptr_j1->qtdGuerreirosDisponiveis[0] = 4; // Guerreiro tipo 1 - ataque vertical
	ptr_j1->qtdGuerreirosDisponiveis[1] = 4; // Guerreiro tipo 2 - ataque diagonal
	ptr_j1->qtdGuerreirosDisponiveis[2] = 1; // Guerreiro especial - ataque especial

	ptr_j2->totalDisponivel = 9;
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
		printf("%s comeca\n", ptr_j1->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j1->especial = '#';	 // Setando o caractere do guerreiro especial do campo de cima
		ptr_j1->coordMax[0] = 0; // Setando as coord maximas da linha que esse usuario vai poder jogar, ou seja, setando o campo
		ptr_j1->coordMax[1] = 5; // nesse caso vai ser (0, 5), entao o jogador vai poder jogar da linha 1 ate a linha 4, pq 0 é a montanha e 5 é rio
		ptr_j1->vez = 1;		 // Se o jogador1 for selecionado pelo sorteio, ele vai começar o jogo
	}
	else
	{

		printf("%s, o seu campo eh o de baixo\n", ptr_j1->nome);
		ptr_j1->especial = '@';
		ptr_j1->coordMax[0] = 6;
		ptr_j1->coordMax[1] = 11;
		ptr_j1->vez = 0;
		printf("%s comeca\n", ptr_j2->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j2->especial = '#';
		ptr_j2->coordMax[0] = 0;
		ptr_j2->coordMax[1] = 5;
		ptr_j2->vez = 1; // Se o jogador2 for selecionado pelo sorteio, ele vai começar o jogo
	}
	// --------------------------
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

// ------------------

int main()
{
	// Declaracao de Variaveis
	char campo[12][12];
	Jogador j1, j2, *ptr_j1, *ptr_j2;
	ptr_j1 = &j1; // Criando ponteiro para j1
	ptr_j2 = &j2; // Criando ponteiro para j2
	//--------------------------

	// Configurando as posicoes do campo
	configCampo(campo);
	// -------------------------------

	printCampo(campo);
	getNomeJogador(ptr_j1, ptr_j2);

	limparTelaDelay();

	sorteioJogador(ptr_j1, ptr_j2);
	inicioPartida(ptr_j1, ptr_j2, campo);

	return 0;
}

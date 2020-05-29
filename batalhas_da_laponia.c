#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	char nome[30];
	int coordMax[2];
	int qtdGuerreirosColocados[3]; // 0- Frente  1- Diagonal  2- Especial
	int vez;
	char especial;
	int partidas[2]; // 0- Vencidas  1- Perdidas
	int selecionado;
	int totalDisponivel;
} Jogador;

// Funcoes

void limparTelaDelay()
{
#if defined(__APPLE__) || defined(__linux__)
	system("sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
#endif
}
void limparTela()
{
#if defined(__APPLE__) || defined(__linux__)
	system("clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("CLS");
#endif
}

void printLogo()
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

void configCampo(char campo[12][12])
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

void printCampo(char campo[12][12])
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

void getNomeJogador(Jogador *ptr_j1, Jogador *ptr_j2)
{

	printf("Digite o nome do player 1: ");
	scanf("%s", ptr_j1->nome);

	// system("CLS");

	printf("Digite o nome do player 2: ");
	scanf("%s", ptr_j2->nome);
}

void sorteioJogador(Jogador *ptr_j1, Jogador *ptr_j2)
{
	srand(time(NULL));
	if (rand() % 2 == 0)
	{
		ptr_j1->selecionado = 1;
		ptr_j2->selecionado = 0;
	}
	else
	{
		ptr_j1->selecionado = 0;
		ptr_j2->selecionado = 1;
	}
}

int alocarGuerreiros(Jogador *ptr_j, char campo[12][12])
{
	if (ptr_j->totalDisponivel == 0)
	{
		return 0;
	}
	int qtdGuerreirosDisponiveis[] = {4, 4, 1}; // 0- Frente  1- Diagonal  2- Especial
	char tipoGuerreiro;
	int erro = 0;
	int lin, col;

	printCampo(campo);
	printf("Quantidade de Guerreiros disponiveis: %d\n", ptr_j->totalDisponivel);
	printf("%s, posicione suas tropas digitando o numero da linha e o da coluna, EX: 0 2\n", ptr_j->nome);
	scanf("%i %i", &lin, &col);
	fflush(stdin);

	//delimitando os locais possiveis para alocacao da tropa no tabuleiro
	if (lin > ptr_j->coordMax[0] && lin < ptr_j->coordMax[1] && col > 0 && col < 11 && campo[lin][col] == '.')
	{

		printf("Qual tipo de guerreiro? (1 (Ataca somente para frente) ou 2 (Ataca somente nas diagonais) ou %c (Guerreiro especial))\n", ptr_j->especial);
		printf("Escreva: ");
		scanf("%c", &tipoGuerreiro);
		fflush(stdin);
		if (tipoGuerreiro == '1' && qtdGuerreirosDisponiveis[0] > 0)
		{
			campo[lin][col] = tipoGuerreiro;
			qtdGuerreirosDisponiveis[0]--;
			ptr_j->totalDisponivel--;
			// printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[0], tipoGuerreiro);
		}
		else if (tipoGuerreiro == '2' && qtdGuerreirosDisponiveis[1] > 0)
		{
			campo[lin][col] = tipoGuerreiro;
			qtdGuerreirosDisponiveis[1]--;
			ptr_j->totalDisponivel--;
			// printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[1], tipoGuerreiro);
		}
		else if (tipoGuerreiro == ptr_j->especial && qtdGuerreirosDisponiveis[2] > 0)
		{
			campo[lin][col] = tipoGuerreiro;
			qtdGuerreirosDisponiveis[2]--;
			ptr_j->totalDisponivel--;
			// printCampo(campo);
			printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[2], tipoGuerreiro);
		}
		else
		{
			limparTela();
			printf("Voce nao pode fazer isso\n");
			erro = 1;
		}
	}
	else
	{
		limparTela();
		printf("Posicao invalida, tente novamente.\n");
		erro = 1;
	}
	limparTela();

	return erro;
}

void inicioPartida(Jogador *ptr_j1, Jogador *ptr_j2, char campo[12][12])
{
	ptr_j1->totalDisponivel = 9;
	ptr_j2->totalDisponivel = 9;
	if (ptr_j1->selecionado)
	{
		printf("%s, o seu campo eh o de baixo\n", ptr_j2->nome);
		ptr_j2->especial = '@';
		ptr_j2->coordMax[0] = 6;
		ptr_j2->coordMax[1] = 11;
		ptr_j2->vez = 0;
		printf("%s comeca\n", ptr_j1->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j1->especial = '#';
		ptr_j1->coordMax[0] = 0;
		ptr_j1->coordMax[1] = 5;
		ptr_j1->vez = 1;
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
		ptr_j2->vez = 1;
	}
	while (ptr_j1->totalDisponivel > 0 && ptr_j2->totalDisponivel > 0)
	{
		if (ptr_j1->vez)
		{

			while (alocarGuerreiros(ptr_j1, campo))
			{
			}
			ptr_j1->vez = 0;
			ptr_j2->vez = 1;
		}
		if (ptr_j2->vez)
		{

			while (alocarGuerreiros(ptr_j2, campo))
			{
			}
			ptr_j2->vez = 0;
			ptr_j1->vez = 1;
		}
	}
}

// ------------------

int main()
{
	// Declaracao de Variaveis
	char campo[12][12];
	Jogador j1, j2, *ptr_j1, *ptr_j2;
	ptr_j1 = &j1;
	ptr_j2 = &j2;
	//--------------------------

	// Configurando as posicoes do campo
	configCampo(campo);
	// -------------------------------

	printCampo(campo);
	getNomeJogador(ptr_j1, ptr_j2);

	limparTelaDelay();

	sorteioJogador(ptr_j1, ptr_j2);
	inicioPartida(ptr_j1, ptr_j2, &campo);

	return 0;
}

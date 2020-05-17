#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Jogador
{
	char nome[30];
	int coordMax[2];
	int qtdGuerreirosColocados[3]; // 0- Frente  1- Diagonal  2- Especial
	int vez;
	char especial;
	int partidas[2]; // 0- Vencidas  1- Perdidas
	int selecionado;
};

// Funcoes
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

#if defined(__APPLE__) || defined(__linux__)
	system("clear;sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("CLS");
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
#endif
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
#if defined(__APPLE__) || defined(__linux__)
	system("sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
#endif
}

void printCampo(char campo[12][12])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			printf("%c ", campo[i][j]);
		}
		printf("\n");
	}
}

void getJogador(struct Jogador *ptr_j1, struct Jogador *ptr_j2)
{

	printf("Digite o nome do player 1: ");
	scanf("%s", ptr_j1->nome);

	// system("CLS");

	printf("Digite o nome do player 2: ");
	scanf("%s", ptr_j2->nome);
}

void sorteioComeco(struct Jogador *ptr_j1, struct Jogador *ptr_j2)
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

void alocarGuerreiros(struct Jogador *ptr_j, char campo[12][12])
{
	int qtdGuerreirosDisponiveis[] = {4, 4, 1}; // 0- Frente  1- Diagonal  2- Especial
	int totalDisponivel = 9;
	char tipoGuerreiro;
	int lin, col;
	int erro = 0;

	if (ptr_j->selecionado)
	{
		printf("%s comeca\n", ptr_j->nome);
		printf("O seu campo eh o de cima\n");
		ptr_j->especial = '#';
		ptr_j->coordMax[0] = 0;
		ptr_j->coordMax[1] = 5;
	}
	else
	{
		printf("%s, o seu campo eh o de baixo\n", ptr_j->nome);
		ptr_j->especial = '@';
		ptr_j->coordMax[0] = 6;
		ptr_j->coordMax[1] = 11;
	}

	while (totalDisponivel > 0)
	{

		printf("Quantidade de Guerreiros disponiveis: %d\n", totalDisponivel);
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
				totalDisponivel--;
				printCampo(campo);
				printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[0], tipoGuerreiro);
			}
			else if (tipoGuerreiro == '2' && qtdGuerreirosDisponiveis[1] > 0)
			{
				campo[lin][col] = tipoGuerreiro;
				qtdGuerreirosDisponiveis[1]--;
				totalDisponivel--;
				printCampo(campo);
				printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[1], tipoGuerreiro);
			}
			else if (tipoGuerreiro == ptr_j->especial && qtdGuerreirosDisponiveis[2] > 0)
			{
				campo[lin][col] = tipoGuerreiro;
				qtdGuerreirosDisponiveis[2]--;
				totalDisponivel--;
				printCampo(campo);
				printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[2], tipoGuerreiro);
			}
			else
			{
				printf("Voce nao pode fazer isso\n");
			}
			// switch (tipoGuerreiro)
			// {
			// case '1':
			// 	if (qtdGuerreirosDisponiveis[0] > 0)
			// 	{
			// 		campo[lin][col] = tipoGuerreiro;
			// 		qtdGuerreirosDisponiveis[0]--;
			// 		totalDisponivel--;
			// 		printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[0], tipoGuerreiro);
			// 	}
			// 	else
			// 	{
			// 		erro = 1;
			// 	}
			// 	break;
			// case '2':
			// 	if (qtdGuerreirosDisponiveis[1] > 0)
			// 	{
			// 		campo[lin][col] = tipoGuerreiro;
			// 		qtdGuerreirosDisponiveis[1]--;
			// 		totalDisponivel--;
			// 		printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[1], tipoGuerreiro);
			// 	}
			// 	break;
			// case '':
			// 	if (qtdGuerreirosDisponiveis[2] > 0)
			// 	{
			// 		campo[lin][col] = tipoGuerreiro;
			// 		qtdGuerreirosDisponiveis[2]--;
			// 		totalDisponivel--;
			// 		printf("Voce ainda pode posiconar %d guerreiros %c\n", qtdGuerreirosDisponiveis[2], tipoGuerreiro);
			// 	}
			// default:
			// 	printf("Opçao invalida\n");
			// 	break;
			// }
			// if (erro)
			// {
			// 	printf("Voce nao pode fazer isso\n");
			// }
		}
		else
		{
			printf("Posicao invalida, tente novamente.\n");
		}
	}
}

// ------------------

int main()
{
	// Declaracao de Variaveis
	char campo[12][12];
	struct Jogador j1, j2, *ptr_j1, *ptr_j2;
	ptr_j1 = &j1;
	ptr_j2 = &j2;
	int starter, lin, col, guerreiro, tropasMax = 8;
	//--------------------------

	// Configurando as posicoes do campo
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
	// -------------------------------

	printCampo(campo);
	getJogador(ptr_j1, ptr_j2);

#if defined(__APPLE__) || defined(__linux__)
	system("sleep 4; clear");

#elif defined(_WIN32) || defined(_WIN64)
	system("ping -n 4 127.0.0.1 > NUL");
	system("CLS");
#endif

	sorteioComeco(ptr_j1, ptr_j2);
	alocarGuerreiros(ptr_j1, &campo);
	alocarGuerreiros(ptr_j2, &campo);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Jogador
{
	char nome[30];
	int campo;					   // 0- Cima    1- Baixo
	int qtdGuerreirosColocados[3]; // 0- Frente  1- Diagonal  2- Especial
	int vez;
	int partidas[2]; // 0- Vencidas  1- Perdidas
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

int sorteioComeco()
{
	srand(time(NULL));
	return (rand() % 2);
}

void alocarGuerreiros(struct Jogador *ptr_j, char campo[12][12])
{
	int qtdGuerreirosDisponiveis[] = {4, 4, 1}; // 0- Frente  1- Diagonal  2- Especial
	int totalDisponivel = 8;
	int tipoGuerreiro;
	int lin, col;

	printf("%s comeca\n", ptr_j->nome);
	printf("O seu campo eh o de cima\n");
	while (totalDisponivel < 9)
	{

		printf("%s, posicione suas tropas digitando o numero da linha e o da coluna, EX: 0 2\n", ptr_j->nome);
		scanf("%i %i", &lin, &col);
		fflush(stdin);

		//delimitando os locais possiveis para alocacao da tropa no tabuleiro
		if (lin > 0 && lin < 11 && col > 0 && col < 5 && campo[lin][col] == '.')
		{
			printf("Qual tipo de guerreiro? (1 (Ataca somente para frente) ou 2 (Ataca somente nas diagonais) ou 3(Guerreiro especial))");
			scanf("%c", &tipoGuerreiro);

			if (tipoGuerreiro == 1 + 48 && qtdGuerreirosDisponiveis[0] > 0)
			{
				campo[lin][col] = tipoGuerreiro;
				tipoGuerreiro++;
				printCampo(campo);
			}

			else if (tipoGuerreiro == 50 && guerreiro1 < 0)
			{
				campo[lin][col] = tipoGuerreiro;
				tipoGuerreiro++;
				printCampo(campo);
			}

			else if (tipoGuerreiro == 51 && guerreiro1 < 0)
			{
				campo[lin][col] = tipoGuerreiro;
				tipoGuerreiro++;
				printCampo(campo);
			}

			else
			{
				printf("Voce nao tem mais guerreiros %d", tipoGuerreiro);
			}
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

	if (sorteioComeco() == 0)
	{
		alocarGuerreiros(ptr_j1, &campo);
	}

	else
	{
		alocarGuerreiros(ptr_j2, &campo);
	}

	return 0;
}

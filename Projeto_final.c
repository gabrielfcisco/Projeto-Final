#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// defines do tamanho do banco de palavras e das cores utilizadas
#define TAM 30
#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[32m"

char *getstr();                                                                                     /// Funcao para ler string alocando dinamicamente
char **gerar_strarr();                                                                              /// Funcao para alocar dinamicamente o banco de palavras
void header(char quadro[], char **banco_palavras, int correct[], int acertos, int erros, int flag); /// Funcao que imprime o cabecalho
int validation(char *word);                                                                         /// Funcao que valida se e uma palavra ou se foi digitado um ENTER
int verify(char *word, char **banco_palavras, int correct[]);                                       // Funcao que verifica se a palavra pertence ao banco ou/e se ja foi digitada

int main()
{
    int acertos = 0, erros = 0, aux = 0, auxval = 0, saida = 0;
    int correct[TAM] = {0};
    char **banco_palavras;
    char *word;
    char quadro[TAM] = {'A', 'A', 'G', 'G', 'D', 'E', 'R', 'O', 'S', 'S', 'I', 'N', 'P', 'H', 'L', 'T', 'U', 'M', 'C', 'F', 'I', 'V', 'Q', 'M', 'B', 'C', 'D', 'T', 'R', 'E'};

    banco_palavras = gerar_strarr(); /// Alocacao das palavras do banco

    do
    {
        system("cls");
        header(quadro, banco_palavras, correct, acertos, erros, 0);
        do /// Leitura e validacao da palavra lida
        {
            word = getstr();
            auxval = validation(word);

        } while (auxval == 1);

        aux = verify(word, banco_palavras, correct);

        switch (aux)
        {
        case -1:
            if (word[0] != '\0')
            {
                erros++;
                printf(COLOR_RED "\n\tPalavra nao consta no Banco de Palavras - Erros: %d\n" COLOR_RESET, erros);
                system("pause");
            }
            break;
        case -2:
            printf(COLOR_RED "\n\tVoce ja digitou essa palavra!\n" COLOR_RESET);
            system("pause");
            break;
        default:
            acertos++;
            correct[aux] = 1;
            break;
        }

        saida = (erros < 5 && acertos < 30 && auxval != -1) ? 1 : 0; /// Condicao para saida do dowhile

    } while (saida != 0);

    if (acertos == 30)
    {
        printf(COLOR_GREEN "\n\nPARABENS, VOCE GANHOU!!!" COLOR_RESET);
        return 0;
    }

    printf("\n\nDeseja imprimir o Banco de Palavras (s/n): ");
    scanf("%c", &word[0]);

    if (word[0] == 's')
    {
        for (int i = 0; i < 30; i++)
        {
            correct[i] = 1;
        }
        header(quadro, banco_palavras, correct, acertos, erros, 1);
    }

    system("pause");
    free(banco_palavras);
    free(word);
    return 0;
}

void header(char quadro[], char **banco_palavras, int correct[], int acertos, int erros, int flag)
{

    /// Impressao do titulo e regras
    if (flag == 0)
    {
        printf("\n================================================================================\n");
        printf("\tJOGO ANAGRAMA\n\tRegras:");
        printf("\n\t > forme palavras com as letras do quadro;");
        printf("\n\t > total de %d palavras;", TAM);
        printf("\n\t > 5 tentativas erradas o jogo termina.");
        printf("\n\n\tB O A   S O R T E !");
        printf("\n================================================================================\n");
    }

    /// Impressao do quadro de letras
    printf("\n\tQuadro de letras\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\n\t");
        for (int j = i * 6; j < i * 6 + 6; j++)
        {
            printf("%c ", quadro[j]);
        }
    }

    /// Impressao da quantidade de acertos e erros e ao fim o abnco de palavras
    if (flag == 0)
    {
        printf("\n\n   >>> ");
        printf(COLOR_GREEN "Acertos (%d de 30)", acertos);
        printf(COLOR_RESET " | ");
        printf(COLOR_RED "Erros (%d de 5)" COLOR_RESET, erros);
    }
    else
    {
        printf("\n\n\t Banco de Palavras\n");
    }

    char vet[15];

    /// Impressao das palavras do banco de palavras

    for (int i = 0; i < 5; i++)
    {
        printf("\n\t");
        for (int j = i * 6; j < i * 6 + 6; j++)
        {
            if (correct[j] == 1)
            {
                printf("%13s\t", banco_palavras[j]);
            }
            else
            {
                vet[0] = banco_palavras[j][0];
                for (int k = 1; k < 15; k++)
                {
                    if (banco_palavras[j][k] != '\0')
                    {
                        vet[k] = '?';
                    }
                    else
                    {
                        vet[k] = '\0';
                    }
                }
                vet[strlen(banco_palavras[j]) - 1] = banco_palavras[j][strlen(banco_palavras[j]) - 1];
                printf("%13s", vet);
            }
        }
    }

    /// Caso ainda não tenha finalizado o jogo
    if (flag == 0)
    {
        printf("\n\n  >>> Para encerrar pressione ENTER");
    }
}

int validation(char *word)
{
    if (word[0] == '\0')
        return -1;

    for (int i = 0; i < (strlen(word)); i++)
    {
        if ((isalpha(word[i])) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int verify(char *word, char **banco_palavras, int correct[])
{
    word = strupr(word);

    for (int i = 0; i < 30; i++)
    {
        if (strcmp(word, banco_palavras[i]) == 0)
        {
            if (correct[i] == 1)
            {
                return -2;
            }
            return i;
        }
    }

    return -1;
}

char *getstr()
{

    char *frase;
    int i = 0;

    printf("\n\n>>> Digite uma palavra:\n");

    frase = NULL;

    do
    {
        if ((frase = (char *)realloc(frase, (i + 1) * sizeof(char))) == NULL)
            exit(1);
        scanf("%c", &frase[i]);
    } while (frase[i++] != '\n');

    frase[i - 1] = '\0';

    return frase;
}

char **gerar_strarr()
{
    char **auxbanco;

    if ((auxbanco = (char **)malloc(30 * sizeof(char *))) == NULL)
        exit(1);

    if ((auxbanco[0] = (char *)malloc(strlen("AGUARDE\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[0] = "AGUARDE\0";

    if ((auxbanco[1] = (char *)malloc(strlen("ESPINHOS\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[1] = "ESPINHOS\0";

    if ((auxbanco[2] = (char *)malloc(strlen("SILHUETA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[2] = "SILHUETA\0";

    if ((auxbanco[3] = (char *)malloc(strlen("PULSO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[3] = "PULSO\0";

    if ((auxbanco[4] = (char *)malloc(strlen("COMPUTADOR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[4] = "COMPUTADOR";

    if ((auxbanco[5] = (char *)malloc(strlen("DEFINIR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[5] = "DEFINIR\0";

    if ((auxbanco[6] = (char *)malloc(strlen("SAPATO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[6] = "SAPATO\0";

    if ((auxbanco[7] = (char *)malloc(strlen("SONHAR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[7] = "SONHAR\0";

    if ((auxbanco[8] = (char *)malloc(strlen("VAQUEIRO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[8] = "VAQUEIRO\0";

    if ((auxbanco[9] = (char *)malloc(strlen("DEPUTADOS\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[9] = "DEPUTADOS\0";

    if ((auxbanco[10] = (char *)malloc(strlen("MEDIDA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[10] = "MEDIDA\0";

    if ((auxbanco[11] = (char *)malloc(strlen("FUMO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[11] = "FUMO\0";

    if ((auxbanco[12] = (char *)malloc(strlen("DISQUETE\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[12] = "DISQUETE\0";

    if ((auxbanco[13] = (char *)malloc(strlen("PRAIA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[13] = "PRAIA\0";

    if ((auxbanco[14] = (char *)malloc(strlen("DADO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[14] = "DADO\0";

    if ((auxbanco[15] = (char *)malloc(strlen("VIDA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[15] = "VIDA\0";

    if ((auxbanco[16] = (char *)malloc(strlen("ALBINO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[16] = "ALBINO\0";

    if ((auxbanco[17] = (char *)malloc(strlen("DETONAR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[17] = "DETONAR\0";

    if ((auxbanco[18] = (char *)malloc(strlen("VENTO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[18] = "VENTO\0";

    if ((auxbanco[19] = (char *)malloc(strlen("SENTIDO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[19] = "SENTIDO\0";

    if ((auxbanco[20] = (char *)malloc(strlen("HARPA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[20] = "HARPA\0";

    if ((auxbanco[21] = (char *)malloc(strlen("CICLONE\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[21] = "CICLONE\0";

    if ((auxbanco[22] = (char *)malloc(strlen("METRALHADORA\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[22] = "METRALHADORA\0";

    if ((auxbanco[23] = (char *)malloc(strlen("ROER\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[23] = "ROER\0";

    if ((auxbanco[24] = (char *)malloc(strlen("COMPRIMIDO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[24] = "COMPRIMIDO\0";

    if ((auxbanco[25] = (char *)malloc(strlen("SUBMETER\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[25] = "SUBMETER\0";

    if ((auxbanco[26] = (char *)malloc(strlen("ADESIVO\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[26] = "ADESIVO\0";

    if ((auxbanco[27] = (char *)malloc(strlen("DOMADOR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[27] = "DOMADOR\0";

    if ((auxbanco[28] = (char *)malloc(strlen("TRANSPORTE\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[28] = "TRANSPORTE\0";

    if ((auxbanco[29] = (char *)malloc(strlen("PEGAR\0") * sizeof(char))) == NULL)
        exit(1);
    auxbanco[29] = "PEGAR\0";

    return auxbanco;
}
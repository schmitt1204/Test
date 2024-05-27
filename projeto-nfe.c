/******************************************************
* OS: Windows 11 Pro                                  *
* GCC: 14.1.0                                         *
* Data: 24/mai/2024                                   *
* Autor: Leandro Mengarda Schmitt                     *
*                                                     *
* Trabalho M2.                                        * 
*                                                     *
******************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int qtdMaxNF = 3;

typedef enum
{
    PR,
    RS,
    SC,
} Estados;

typedef struct
{
    char nome[20];
    float valor;
} Mercadoria;

typedef struct
{
    int numeroNF;
    char nomeEmissor[20];
    Estados estadoEmissor;
    char nomeEstadoEmissor[20];
    char nomeDestinatario[20];
    Estados estadoDestinatario;
    char nomeEstadoDestinatario[20];
    int qtdMercadoria;
    Mercadoria mercadoria[3];
    float valorTotal;
} NotaFiscal;

void inserir_dados(NotaFiscal notaFiscal[qtdMaxNF]);
void calcular_total(NotaFiscal notaFiscal[qtdMaxNF]);
void ajustar_estados(NotaFiscal notaFiscal[qtdMaxNF]);
void exibir_notas(NotaFiscal notaFiscal[qtdMaxNF]);
void buscar_nota(NotaFiscal notaFiscal[qtdMaxNF]);
void validar_numero_NF(char buscarNumeroNF[6]);
int comparar_valores(NotaFiscal notaFiscal[qtdMaxNF], char buscarNumeroNF[6]);
int realizar_nova_busca(int resultadoBusca, int novaBusca);
void salvar_dados(NotaFiscal notaFiscal[qtdMaxNF], int posicaoNF);

int main()
{
    NotaFiscal notaFiscal[qtdMaxNF];
    
    inserir_dados(notaFiscal);
    calcular_total(notaFiscal);
    ajustar_estados(notaFiscal);
    exibir_notas(notaFiscal);
    buscar_nota(notaFiscal);
    
    return 0;
}

void inserir_dados(NotaFiscal notaFiscal[qtdMaxNF])
{
    // Construir NF 100224;
    notaFiscal[0].numeroNF = 100224;
    strcpy(notaFiscal[0].nomeEmissor, "AMAZON ACOS");
    notaFiscal[0].estadoEmissor = SC;
    strcpy(notaFiscal[0].nomeDestinatario, "JOAO PAULO LTDA");
    notaFiscal[0].estadoDestinatario = PR;
    
    notaFiscal[0].qtdMercadoria = 2; // Informar a quantidade de mercadoria.
        // Inserir mercadorias.
    strcpy(notaFiscal[0].mercadoria[0].nome, "ALUMINIO");
    notaFiscal[0].mercadoria[0].valor = 1000;

    strcpy(notaFiscal[0].mercadoria[1].nome, "FERRO GALVANIZADO");
    notaFiscal[0].mercadoria[1].valor = 2000;

    notaFiscal[0].valorTotal = 0; // Atribuir o valor 'zero' ao total.

    // Construir NF 100225;
    notaFiscal[1].numeroNF = 100225;
    strcpy(notaFiscal[1].nomeEmissor, "AMAZON ACOS");
    notaFiscal[1].estadoEmissor = SC;
    strcpy(notaFiscal[1].nomeDestinatario, "JOAO PAULO LTDA");
    notaFiscal[1].estadoDestinatario = SC;

    notaFiscal[1].qtdMercadoria = 3; // Informar a quantidade de mercadoria.
        // Inserir mercadorias.
    strcpy(notaFiscal[1].mercadoria[0].nome, "ACO INOX");
    notaFiscal[1].mercadoria[0].valor = 1000;

    strcpy(notaFiscal[1].mercadoria[1].nome, "COBRE");
    notaFiscal[1].mercadoria[1].valor = 2000;

    strcpy(notaFiscal[1].mercadoria[2].nome, "PAPEL ALUMINIO");
    notaFiscal[1].mercadoria[2].valor = 3000;

    notaFiscal[1].valorTotal = 0; // Atribuir o valor 'zero' ao total.

    // Construir NF 100225;
    notaFiscal[2].numeroNF = 100226;
    strcpy(notaFiscal[2].nomeEmissor, "AMAZON ACOS");
    notaFiscal[2].estadoEmissor = SC;
    strcpy(notaFiscal[2].nomeDestinatario, "JOAO PAULO LTDA");
    notaFiscal[2].estadoDestinatario = RS;

    notaFiscal[2].qtdMercadoria = 1; // Informar a quantidade de mercadoria.
        // Inserir mercadorias.
    strcpy(notaFiscal[2].mercadoria[0].nome, "FERRO");
    notaFiscal[2].mercadoria[0].valor = 1000;

    notaFiscal[2].valorTotal = 0; // Atribuir o valor 'zero' ao total.

    return;
}

void calcular_total(NotaFiscal notaFiscal[qtdMaxNF])
{
    // Entrar em cada NF.
    for (int i = 0; i < qtdMaxNF; i++){
        // Verificar quantas mercadorias possui na NF, e somar.
        for (int j = 0; j < notaFiscal[i].qtdMercadoria; j++){
            notaFiscal[i].valorTotal += notaFiscal[i].mercadoria[j].valor;
        }
    }

    return;
}

void ajustar_estados(NotaFiscal notaFiscal[qtdMaxNF])
{
    // Modificar as Siglas dos Estados para o Nome do Estado.
    for (int i = 0; i < qtdMaxNF; i++){
        if (notaFiscal[i].estadoEmissor == PR){
            strcpy(notaFiscal[i].nomeEstadoEmissor,  "PARANA");
        }
        else if (notaFiscal[i].estadoEmissor == RS){
            strcpy(notaFiscal[i].nomeEstadoEmissor, "RIO GRANDE DO SUL");
        }
        else {
            strcpy(notaFiscal[i].nomeEstadoEmissor, "SANTA CATARINA");
        }

        if (notaFiscal[i].estadoDestinatario == PR){
            strcpy(notaFiscal[i].nomeEstadoDestinatario, "PARANA");
        }
        else if (notaFiscal[i].estadoDestinatario == RS){
            strcpy(notaFiscal[i].nomeEstadoDestinatario, "RIO GRANDE DO SUL");
        }
        else {
            strcpy(notaFiscal[i].nomeEstadoDestinatario, "SANTA CATARINA");
        }
    }

    return;
}

void exibir_notas(NotaFiscal notaFiscal[qtdMaxNF])
{
    for (int i = 0; i < qtdMaxNF; i++){
        printf("Numero: %d\n", notaFiscal[i].numeroNF);
        printf("Emissor: %s\n", notaFiscal[i].nomeEmissor);
        printf("Estado Emissor: %s\n", notaFiscal[i].nomeEstadoEmissor);
        printf("Destinatario: %s\n", notaFiscal[i].nomeDestinatario);
        printf("Estado Destinatario: %s\n", notaFiscal[i].nomeEstadoDestinatario);
        printf("Valor Total da Nota: %.2f\n", notaFiscal[i].valorTotal);
        printf("Itens da Nota Fiscal:\n");

        for (int j = 0; j < notaFiscal[i].qtdMercadoria; j++){
            printf("\tMercadoria %d: %s\n", j + 1, notaFiscal[i].mercadoria[j].nome);
            printf("\tValor Item: %.2f\n\n", notaFiscal[i].mercadoria[j].valor);
        }
        printf("\n");
    }
    return;
}

void buscar_nota(NotaFiscal notaFiscal[qtdMaxNF])
{
    char buscarNumeroNF[6];
    int resultadoBusca = 0; // Marcar como 0 (falso).
    int novaBusca = 0; // Marcar como 0 (falso).

    do {
        validar_numero_NF(buscarNumeroNF);
        resultadoBusca = comparar_valores(notaFiscal, buscarNumeroNF);
        novaBusca = realizar_nova_busca(resultadoBusca, novaBusca);

    } while(novaBusca == '1'); // Enquanto for 1 (verdadeiro) nao sai do loop.

    printf("O programa foi encerrado.");

    return;
}

void validar_numero_NF(char buscarNumeroNF[6])
{
    int numeroValido = 0;
    // Validar se foi digitado somente numeros.

    do {
        printf("Informe o numero da NF: ");
        scanf("%s", buscarNumeroNF);
        // Retorna que a NF nao e valida, se algum digito for uma letra.
        for (int i = 0; i < strlen(buscarNumeroNF); i++){
            if (isdigit(buscarNumeroNF[i])){
                numeroValido = 1;
            }
            else {
                printf("\nO numero da NF nao e valido!\n\n");
                numeroValido = 0;
                break;
            }
        }
    } while(numeroValido == 0);
    return;
}

int comparar_valores(NotaFiscal notaFiscal[qtdMaxNF], char buscarNumeroNF[6])
{
    int resultadoBusca = 0; // Marcar como 0 (falso).

    // Comparar o numero digitado com o numero das NFs salvas e retornar os dados.
    for (int i = 0; i < qtdMaxNF; i++){
        if (notaFiscal[i].numeroNF == strtol(buscarNumeroNF, NULL, 0)){
            resultadoBusca = 1; // Marcar como 1 (verdadeiro) caso ache algum resultado.
            printf("\nNumero: %d\n", notaFiscal[i].numeroNF);
            printf("Emissor: %s\n", notaFiscal[i].nomeEmissor);
            printf("Estado Emissor: %s\n", notaFiscal[i].nomeEstadoEmissor);
            printf("Destinatario: %s\n", notaFiscal[i].nomeDestinatario);
            printf("Estado Destinatario: %s\n", notaFiscal[i].nomeEstadoDestinatario);
            printf("Valor Total da Nota: %.2f\n", notaFiscal[i].valorTotal);
            printf("Itens da Nota Fiscal:\n");

            for (int j = 0; j < notaFiscal[i].qtdMercadoria; j++){
                printf("\tMercadoria %d: %s\n", j + 1, notaFiscal[i].mercadoria[j].nome);
                printf("\tValor Item: %.2f\n\n", notaFiscal[i].mercadoria[j].valor);
            }

            salvar_dados(notaFiscal, i);
        }
    }

    // Se o resultado da busca nao localizar nenhuma NF, informar ao usuario.
    if (resultadoBusca == 0){
        printf("\nO numero da NF nao foi localizado!\n"); // Ver NOTA 1.
    }
    return resultadoBusca;
}

int realizar_nova_busca(int resultadoBusca, int novaBusca)
{
    int valorValido = 0; // Marcar como 0 (falso).
    // Perguntar ao usuario se ele quer efetuar nova busca.
    do {
        printf("\nDeseja realizar nova busca?\n[0] Nao [1] Sim: ");
        scanf("%s", &novaBusca);
        // Validar o que foi digitado.
        if (novaBusca != '0' && novaBusca != '1'){ // Se for digitado algo diferente de 0 ou 1.
            printf("\nO valor informado nao e valido!");
            valorValido = 0;
        }
        else {
            valorValido = 1;
            resultadoBusca = 0; // NOTA 1: Resetar o parametro para 0 (falso).
                                // Pois no caso de uma nova busca, se nao localizar nao mostra mensagem.
        }
        printf("\n");
    } while(valorValido == 0); // Enquanto for 0 (falso) nao sai do loop.

    return novaBusca;
}

void salvar_dados(NotaFiscal notaFiscal[qtdMaxNF], int posicaoNF)
{
    // Gerar data e horario da gravacao.
    time_t t;
    struct tm *data;
    char dataCompleta[21];
    time(&t);

    data = localtime(&t);

    strftime(dataCompleta, sizeof(dataCompleta), "%d-%b-%Y-%H-%M-%S", data);

    // Criar nome do arquivo com Numero da NF e a data e hora da geracao do arquivo.
    char nomeArquivo[34];
    sprintf(nomeArquivo, "NF-%d-%s.txt", notaFiscal[posicaoNF].numeroNF, dataCompleta);

    // Criar arquivo e salvar os dados.
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "w");

    fprintf(arquivo, "\nNumero: %d\n", notaFiscal[posicaoNF].numeroNF);
    fprintf(arquivo, "Emissor: %s\n", notaFiscal[posicaoNF].nomeEmissor);
    fprintf(arquivo, "Estado Emissor: %s\n", notaFiscal[posicaoNF].nomeEstadoEmissor);
    fprintf(arquivo, "Destinatario: %s\n", notaFiscal[posicaoNF].nomeDestinatario);
    fprintf(arquivo, "Estado Destinatario: %s\n", notaFiscal[posicaoNF].nomeEstadoDestinatario);
    fprintf(arquivo, "Valor Total da Nota: %.2f\n", notaFiscal[posicaoNF].valorTotal);
    fprintf(arquivo, "Itens da Nota Fiscal:\n");

    for (int i = 0; i < notaFiscal[posicaoNF].qtdMercadoria; i++){
        fprintf(arquivo, "\tMercadoria %d: %s\n", i + 1, notaFiscal[posicaoNF].mercadoria[i].nome);
        fprintf(arquivo, "\tValor Item: %.2f\n\n", notaFiscal[posicaoNF].mercadoria[i].valor);
    }

    fclose(arquivo);

    printf("Dados salvos com sucesso!\n");

    return;
}
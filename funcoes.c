#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas.h"

void pedirdados(PRODUTO *produto)
{
    printf("ID do produto???\n");
    scanf("%d", &produto->idProduto);
    getchar(); // Consome o caractere de nova linha

    printf("Qual o nome do produto??\n");
    fgets(produto->nomeProduto, sizeof(produto->nomeProduto), stdin);
    produto->nomeProduto[strcspn(produto->nomeProduto, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Qual o preco da compra do produto??\n");
    scanf("%f", &produto->precocompraProduto);

    printf("Qual o preco da venda do produto??\n");
    scanf("%f", &produto->precovendaProduto);

    printf("Qual e a quantidade do produto??\n");
    scanf("%f", &produto->qtdProduto);

    printf("Data de registro[DD-MM-AAAA]?\n");
    scanf("%d%d%d", &produto->dataregistro.dia, &produto->dataregistro.mes, &produto->dataregistro.ano);
}

void mostardadosPRODUTO(PRODUTO produto)
{
    printf("ID do produto: %d\n", produto.idProduto);
    printf("Qual o nome do produto: %s\n", produto.nomeProduto);
    printf("Qual o preco da compra do produto: %.2f\n", produto.precocompraProduto);
    printf("Qual o preco da venda do produto: %.2f\n", produto.precovendaProduto);
    printf("Qual e a quantidade do produto: %.2f\n", produto.qtdProduto);
    printf("Data de registro: %02d-%02d-%04d\n", produto.dataregistro.dia, produto.dataregistro.mes, produto.dataregistro.ano);
}

void salvardadosPRODUTO()
{
    FILE *fp;
    PRODUTO produto;

    fp = fopen("PRODUTO.DAT", "ab");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fseek(fp, 0L, SEEK_END);

    pedirdados(&produto);

    if (fwrite(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        system("clear");
        puts("Adicionado com sucesso!");
    }
    else
    {
        perror("Erro ao escrever no arquivo");
    }

    fclose(fp);
}
void editarProduto()
{
    FILE *fp;
    PRODUTO produto;
    int idProcurado;
    int encontrado = 0;

    fp = fopen("PRODUTO.DAT", "r+b");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira o ID do produto que deseja editar:\n");
    scanf("%d", &idProcurado);

    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        if (produto.idProduto == idProcurado)
        {
            printf("Produto encontrado. Insira os novos dados:\n");
            pedirdados(&produto);
            fseek(fp, -sizeof(PRODUTO), SEEK_CUR);
            fwrite(&produto, sizeof(PRODUTO), 1, fp);
            encontrado = 1;
            printf("Produto editado com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Produto não encontrado.\n");
    }

    fclose(fp);
}
void eliminarProduto()
{
    FILE *fp;
    FILE *fpTemp;
    PRODUTO produto;
    int idProcurado;
    int encontrado = 0;

    fp = fopen("PRODUTO.DAT", "rb");
    fpTemp = fopen("TEMP.DAT", "wb");

    if (fp == NULL || fpTemp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira o ID do produto que deseja eliminar:\n");
    scanf("%d", &idProcurado);

    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        if (produto.idProduto == idProcurado)
        {
            encontrado = 1;
            printf("Produto eliminado com sucesso!\n");
        }
        else
        {
            fwrite(&produto, sizeof(PRODUTO), 1, fpTemp);
        }
    }

    if (!encontrado)
    {
        printf("Produto não encontrado.\n");
    }

    fclose(fp);
    fclose(fpTemp);

    remove("PRODUTO.DAT");
    rename("TEMP.DAT", "PRODUTO.DAT");
}
void listardadosPRODUTO()
{
    FILE *fp;
    PRODUTO produto;

    fp = fopen("PRODUTO.DAT", "rb");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fseek(fp, 0L, SEEK_SET);

    system("clear");

    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        puts("-------------------------------------");
        mostardadosPRODUTO(produto);
    }

    fclose(fp);
}

void pesquisarPRODUTOnome()
{
    FILE *fp;
    PRODUTO produto;
    char nomeProcurado[20];
    int encontrado = 0;

    fp = fopen("PRODUTO.DAT", "rb");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira o nome a pesquisar:\n");
    // Limpar o buffer do stdin
    getchar();
    fgets(nomeProcurado, sizeof(nomeProcurado), stdin);
    nomeProcurado[strcspn(nomeProcurado, "\n")] = '\0'; // Remove o caractere de nova linha
    system("clear");
    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        if (strcmp(produto.nomeProduto, nomeProcurado) == 0)
        {
            puts("-------------------------------------");
            mostardadosPRODUTO(produto);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Produto não encontrado.\n");
    }

    fclose(fp);
}
void pesquisarPRODUTOID()
{
    FILE *fp;
    PRODUTO produto;
    int IDProcurado;

    fp = fopen("PRODUTO.DAT", "rb");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fseek(fp, 0L, SEEK_SET);

    system("clear");

    puts("Insira o ID a pesquisar:");
    scanf("%d", &IDProcurado);

    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        if (produto.idProduto == IDProcurado)
        {
            puts("-------------------------------------");
            mostardadosPRODUTO(produto);
            fclose(fp);
            return;
        }
    }

    puts("Produto não encontrado.");
    fclose(fp);
}
void efectuarCompra()
{
    FILE *fp;
    FILE *fpHistorico;
    PRODUTO produto;
    HISTORICO_COMPRA compra;
    int idProcurado;
    float quantidadeComprada;
    int encontrado = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fp = fopen("PRODUTO.DAT", "r+b");
    fpHistorico = fopen("HISTORICO_COMPRAS.DAT", "ab");

    if (fp == NULL || fpHistorico == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira o ID do produto que deseja comprar:\n");
    scanf("%d", &idProcurado);

    printf("Insira a quantidade que deseja comprar:\n");
    scanf("%f", &quantidadeComprada);

    while (fread(&produto, sizeof(PRODUTO), 1, fp) == 1)
    {
        if (produto.idProduto == idProcurado)
        {
            produto.qtdProduto -= quantidadeComprada;
            fseek(fp, -sizeof(PRODUTO), SEEK_CUR);
            fwrite(&produto, sizeof(PRODUTO), 1, fp);

            // Registrar a compra no histórico
            compra.idProduto = produto.idProduto;
            strcpy(compra.nomeProduto, produto.nomeProduto);
            compra.quantidadeComprada = quantidadeComprada;
            compra.dataCompra.dia = tm.tm_mday;
            compra.dataCompra.mes = tm.tm_mon + 1;
            compra.dataCompra.ano = tm.tm_year + 1900;
            fwrite(&compra, sizeof(HISTORICO_COMPRA), 1, fpHistorico);

            encontrado = 1;
            printf("Compra efetuada com sucesso!\n");
            printf("\t------------------------------------------------\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Produto não encontrado.\n");
        printf("\t------------------------------------------------\n");
    }

    fclose(fp);
    fclose(fpHistorico);
}
void HistoricoCompras()
{
    FILE *fp;
    HISTORICO_COMPRA compra;

    fp = fopen("HISTORICO_COMPRAS.DAT", "rb");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    system("clear");

    puts("Histórico de Compras:");
    puts("-------------------------------------");

    while (fread(&compra, sizeof(HISTORICO_COMPRA), 1, fp) == 1)
    {
        printf("ID do produto: %d\n", compra.idProduto);
        printf("Nome do produto: %s\n", compra.nomeProduto);
        printf("Quantidade comprada: %.2f\n", compra.quantidadeComprada);
        printf("Data da compra: %02d-%02d-%04d\n", compra.dataCompra.dia, compra.dataCompra.mes, compra.dataCompra.ano);
        puts("-------------------------------------");
    }

    fclose(fp);
}
void pesquisarDadosDefesa()
{
    FILE *fp;
    HISTORICO_COMPRA defesa;
    char dioceseProcurada[20];
    char paroquiaProcurada[20];
    int encontrado = 0;

    fp = fopen("DEFESA.DAT", "rb");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira a Diocese a pesquisar :\n");
    getchar(); //Limpar
    fgets(dioceseProcurada, sizeof(dioceseProcurada), stdin);
    dioceseProcurada[strcspn(dioceseProcurada, "\n")] = '\0'; 

    printf("Insira a Paróquia a pesquisar:\n");
    fgets(paroquiaProcurada, sizeof(paroquiaProcurada), stdin);
    paroquiaProcurada[strcspn(paroquiaProcurada, "\n")] = '\0'; // Remove o caractere de nova linha

    system("clear");

    while (fread(&defesa, sizeof(HISTORICO_COMPRA), 1, fp) == 1)
    {
        if (strcmp(defesa.diocese, dioceseProcurada) == 0 && strcmp(defesa.paroquia, paroquiaProcurada) == 0)
        {
            puts("-------------------------------------");
            printf("Diocese: %s\n", defesa.diocese);
            printf("Paróquia: %s\n", defesa.paroquia);
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nenhum registro encontrado para a Diocese e Paróquia informadas.\n");
    }

    fclose(fp);
}

void salvarDadosDefesa()
{
    FILE *fp;
    HISTORICO_COMPRA defesa;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fp = fopen("DEFESA.DAT", "ab");

    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Insira a Diocese :\n");
    getchar(); // Limpar
    fgets(defesa.diocese, sizeof(defesa.diocese), stdin);
    defesa.diocese[strcspn(defesa.diocese, "\n")] = '\0'; 

    printf("Insira a Paróquia :\n");
    fgets(defesa.paroquia, sizeof(defesa.paroquia), stdin);
    defesa.paroquia[strcspn(defesa.paroquia, "\n")] = '\0'; 

    fwrite(&defesa, sizeof(HISTORICO_COMPRA), 1, fp);

    printf("Dados de defesa salvos com sucesso!\n");

    fclose(fp);
}
// Função para salvar as credenciais no arquivo
void salvarCredenciais (const char *username, const char *password) 
{
	FILE *fp = fopen("credenciais.dat", "w");
	if (fp == NULL) 
	{
	perror("Erro ao abrir o arquivo de credenciais");
	return;
	}
	fprintf(fp, "%s\n%s\n", username, password);
	fclose(fp);
	printf("Credenciais salvas com sucesso!\n");
}
// Função para carregar as credenciais do arquivo
int carregarCredenciais(char *username, char *password) 
{
	FILE *fp = fopen("credenciais.dat", "r");
	if (fp == NULL) 
	{
	perror("Erro ao abrir o arquivo de credenciais");
	return 0; // Retorna 0 se o arquivo não existir
	}
	fscanf(fp, "%s", username);
	fscanf(fp, "%s", password);
	fclose(fp);
	return 1; // Retorna 1 se as credenciais foram carregadas com sucesso
}
// Função de login
int login() 
{
	char username[50];
	char password[50];
	char storedUsername[50];
	char storedPassword[50];
	//Carregar as credenciais do arquivo
	if (!carregarCredenciais(storedUsername, storedPassword)) 
	{
	printf("Nenhuma credencial cadastrada. Cadastre um usuário e senha.\n");
	printf("Digite o nome de usuário: ");
	scanf("%s", storedUsername);
	printf("Digite a senha: ");
	scanf("%s", storedPassword);
	salvarCredenciais(storedUsername, storedPassword);
	return 1; // Retorna 1 após cadastrar as credenciais
	}
	// Solicitar credenciais do usuário
	printf("Nome de usuário: ");
	scanf("%s", username);printf("Senha: ");
	scanf("%s", password);
	// Veriﬁcar credenciais
	if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) 
	{
	printf("Login bem-sucedido!\n");
	return 1; // Retorna 1 se o login for bem-sucedido
	} else {
		printf("Nome de usuário ou senha incorretos. Acesso negado.\n");
	return 0; // Retorna 0 se o login falhar
	}
}
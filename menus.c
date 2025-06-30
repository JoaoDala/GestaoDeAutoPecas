#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "menus.h"
#include "funcoes.h"

#define MENU_PRODUTO 1
#define MENU_COMPRAS 2
#define MENU_ESTOQUE 3
#define MENU_DEFESA 4
#define SAIR_DA_APLICACAO 5

#define NOVO_PRODUTO 1
#define EDITAR_PRODUTO 2
#define ELIMINAR_PRODUTO 3
#define LISTAR_PRODUTO 4
#define PESQUISAR_PRODUTO 5
#define VOLTAR_PRODUTO 6

#define NOVA_COMPRA 1
#define HISTORICO_VENDAS 2
#define VOLTAR 3

#define EXIBIR_PRODUTO 1
#define ADICIONAR_PRODUTO 2
#define VOLTAR 3

#define CADASTRAR_DEFESA 1
#define PESQUISAR_DEFESA 2
#define VOLTAR 3

/*#define USERNAME "Admin"
#define PASSWORD "1234"
*/
void apresentacao()
{
	char opcao;

	printf("\t------------------------------------------------\n");
	printf("\tUNIVERSIDADE CATOLICA DE ANGOLA\n");
	printf("\tFACULDADE DE ENGENHARIA\n");
	printf("\tPROJECTO DE FUNDAMENTOS DE PROG. I ANO 24-25\n");
	printf("\tAUTOR: JOAO DALA, N. 35356\n");
	printf("\t------------------------------------------------\n");
	printf("\tTEMA: GESTAO DE UMA AUTO-PECAS\n");
	printf("\tDOCENTE: ENG. OSVALDO RAMOS\n");
	printf("\tOBS: USO EXCLUSIVO DENTRO DA UCAN\n");
	printf("\t------------------------------------------------\n");
	printf("\tSE CONCORDA COM OS TERMOS DE USO DIGITE S, N CASO CONTRARIO\n");

	scanf(" %c", &opcao);

	if (opcao == 'S' || opcao == 's')
		if (login())
		{
			menuPrincipal();
		} else
		{
			printf("Programa encerrado!\n");
			exit(0);
		}
	else
	{
		printf("Até a proxima!\n");
		return;
	}
}

void menuPrincipal()
{
	int opcao;

	system("clear");
	do
	{
		printf("\n\t\tMENU PRINCIPAL\n");
		printf("\t\t1 - MENU PRODUTO\n");
		printf("\t\t2 - MENU COMPRAS\n");
		printf("\t\t3 - MENU ESTOQUE\n");
		printf("\t\t4 - MENU DEFESA\n");
		printf("\t\t5 - SAIR DA APLICAÇÃO\n");

		printf("Digite uma opção\n:");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case MENU_PRODUTO:
			menuProduto();
			break;

		case MENU_COMPRAS:
			menuCompras();
			break;

		case MENU_ESTOQUE:
			menuEstoque();
			break;
			
		case MENU_DEFESA:
			menuDefesa();
			break;

		case SAIR_DA_APLICACAO:
			printf("Saindo...\n");
			//system("clear");
			return;
			break;

		default:
			printf("Opção inválida!\n");
		}
	} while (opcao != SAIR_DA_APLICACAO);
}
void menuProduto()
{
	int opcao;

	system("clear");
	do
	{
		printf("***MENU PRODUTO***\n");
		printf("***1 - NOVO PRODUTO***\n");
		printf("***2 - EDITAR PRODUTO***\n");
		printf("***3 - ELIMINAR PRODUTO***\n");
		printf("***4 - LISTAR PRODUTOS***\n");
		printf("***5 - PESQUISAR PRODUTO***\n");
		printf("***6 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case NOVO_PRODUTO:
			salvardadosPRODUTO();
			break;

		case EDITAR_PRODUTO:
			editarProduto();
			break;

		case ELIMINAR_PRODUTO:
			eliminarProduto();
			break;

		case LISTAR_PRODUTO:
			listardadosPRODUTO();
			break;

		case PESQUISAR_PRODUTO:
			pesquisarPRODUTOnome();
			break;

		case VOLTAR_PRODUTO:
			return;
			break;

		default:
			printf("Opcao Invalida\n");
		}
	} while (opcao != VOLTAR_PRODUTO);
}
void menuCompras()
{
	int opcao;

	system("clear");
	do
	{
		printf("***MENU COMPRAS***\n");
		printf("***1 - EFECTUAR UMA COMPRA***\n");
		printf("***2 - HISTORICO DAS VENDAS***\n");
		printf("***3 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case NOVA_COMPRA:
			efectuarCompra();
			break;

		case HISTORICO_VENDAS:
			HistoricoCompras();
			break;
			
		case VOLTAR:
			return;
			break;

		default:
			printf("Opcao Invalida\n");
		}
	} while (opcao != VOLTAR);
}
void menuEstoque()
{
	int opcao;

	system("clear");
	do
	{
		printf("***MENU ESTOQUE***\n");
		printf("***1 - EXIBIR PRODUTOS***\n");
		printf("***2 - ADICIONAR PRODUTOS***\n");
		printf("***3 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case EXIBIR_PRODUTO:
			listardadosPRODUTO();
			break;

		case ADICIONAR_PRODUTO:
			salvardadosPRODUTO();
			break;
			
		case VOLTAR:
			return;
			break;

		default:
			printf("Opcao Invalida\n");
		}
	} while (opcao != VOLTAR);
}
void menuDefesa()
{
    int opcao;

    system("clear");
    do
    {
        printf("***MENU DEFESA***\n");
        printf("***1 - CADASTRAR DEFESA***\n");
        printf("***2 - PESQUISAR DEFESA***\n");
        printf("***3 - VOLTAR***\n");
        printf("Escolha uma opcao\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case CADASTRAR_DEFESA:
            salvarDadosDefesa();
            break;

        case PESQUISAR_DEFESA:
            pesquisarDadosDefesa();
            break;

        case VOLTAR:
            return;
            break;

        default:
            printf("Opcao Invalida\n");
        }
    } while (opcao != VOLTAR);
}

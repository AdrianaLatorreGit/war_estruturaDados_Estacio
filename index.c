#include <stdio.h>
#include <string.h>

// Definindo a estrutura Territorio
struct Territorio
{
  char nome[30];
  char cor[10];
  int tropas;
};

int main()
{
  struct Territorio territorios[5]; // Vetor para armazenar até 5 territórios
  int quantidade = 0;               // Quantos territórios já foram cadastrados
  int opcao;

  do
  {
    printf("\n=== MENU DE CADASTRO DE TERRITÓRIOS ===\n");
    printf("1 - Cadastrar novo território\n");
    printf("2 - Listar territórios cadastrados\n");
    printf("3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
      if (quantidade < 5)
      {
        printf("\n--- Cadastro do Território %d ---\n", quantidade + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[quantidade].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[quantidade].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[quantidade].tropas);

        quantidade++;
        printf("✔ Território cadastrado com sucesso!\n");
      }
      else
      {
        printf("\n⚠ Você já cadastrou o máximo de 5 territórios!\n");
      }
    }
    else if (opcao == 2)
    {
      if (quantidade == 0)
      {
        printf("\n⚠ Nenhum território cadastrado ainda.\n");
      }
      else
      {
        printf("\n=== LISTA DE TERRITÓRIOS ===\n");
        for (int i = 0; i < quantidade; i++)
        {
          printf("\nTerritório %d\n", i + 1);
          printf("Nome: %s\n", territorios[i].nome);
          printf("Cor do Exército: %s\n", territorios[i].cor);
          printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        }
      }
    }
    else if (opcao == 3)
    {
      printf("\nSaindo do programa...\n");
    }
    else
    {
      printf("\n⚠ Opção inválida! Tente novamente.\n");
    }

  } while (opcao != 3);

  return 0;
}

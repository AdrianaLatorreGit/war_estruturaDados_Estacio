#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Nível AVENTUREIRO

// Definição da estrutura Territorio
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

// ---------- PROTÓTIPOS DE FUNÇÕES ----------
void cadastrarTerritorios(Territorio *mapa, int n);
void exibirTerritorios(Territorio *mapa, int n);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

// ---------- FUNÇÃO PRINCIPAL ----------
int main()
{
  srand(time(NULL)); // inicializa gerador de números aleatórios
  int n;

  printf("Digite o número de territórios a serem cadastrados: ");
  scanf("%d", &n);

  // Alocação dinâmica do vetor de territórios
  Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
  if (mapa == NULL)
  {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  // Cadastro inicial
  cadastrarTerritorios(mapa, n);

  int opcao, atacante, defensor;
  do
  {
    printf("\n=== MENU DE CADASTRO DE TERRITÓRIOS ===\n");
    printf("1 - Listar territórios\n");
    printf("2 - Atacar\n");
    printf("3 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      exibirTerritorios(mapa, n);
      break;
    case 2:
      exibirTerritorios(mapa, n);

      printf("\nDigite o número do território atacante: ");
      scanf("%d", &atacante);

      printf("Digite o número do território defensor: ");
      scanf("%d", &defensor);

      // Valida índices e cores
      if (atacante >= 0 && atacante < n &&
          defensor >= 0 && defensor < n &&
          strcmp(mapa[atacante].cor, mapa[defensor].cor) != 0)
      {

        atacar(&mapa[atacante], &mapa[defensor]);
      }
      else
      {
        printf("⚠ Escolha inválida! Não é possível atacar esse território.\n");
      }
      break;
    case 3:
      printf("\nEncerrando programa...\n");
      break;
    default:
      printf("⚠ Opção inválida!\n");
    }
  } while (opcao != 3);

  liberarMemoria(mapa);
  return 0;
}

// ---------- FUNÇÕES AUXILIARES ----------

// Cadastro inicial de territórios
void cadastrarTerritorios(Territorio *mapa, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("\n--- Cadastro do Território %d ---\n", i);

    printf("Nome: ");
    scanf(" %[^\n]", mapa[i].nome);

    printf("Cor do exército: ");
    scanf(" %s", mapa[i].cor);

    printf("Número de tropas: ");
    scanf("%d", &mapa[i].tropas);
  }
}

// Exibição de todos os territórios
void exibirTerritorios(Territorio *mapa, int n)
{
  printf("\n=== LISTA DE TERRITÓRIOS ===\n");
  for (int i = 0; i < n; i++)
  {
    printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
           i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
  }
}

// Função de ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
  if (atacante->tropas <= 1)
  {
    printf("\n⚠ O atacante precisa de pelo menos 2 tropas para atacar!\n");
    return;
  }

  int dadoAtacante = (rand() % 6) + 1; // valor entre 1 e 6
  int dadoDefensor = (rand() % 6) + 1;

  printf("\n🎲 Rolagem de dados:\n");
  printf("%s (atacante) tirou %d\n", atacante->nome, dadoAtacante);
  printf("%s (defensor) tirou %d\n", defensor->nome, dadoDefensor);

  if (dadoAtacante > dadoDefensor)
  {
    printf("\n🔥 O atacante venceu a batalha!\n");
    // Atacante conquista o território
    strcpy(defensor->cor, atacante->cor);
    defensor->tropas = atacante->tropas / 2; // metade das tropas vão para o novo território
    atacante->tropas /= 2;                   // metade das tropas ficam
  }
  else
  {
    printf("\n🛡 O defensor resistiu!\n");
    atacante->tropas--; // atacante perde uma tropa
  }
}

// Liberação da memória alocada
void liberarMemoria(Territorio *mapa)
{
  free(mapa);
}

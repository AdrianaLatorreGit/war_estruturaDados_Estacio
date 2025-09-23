#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura de Território */
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

/* Estrutura de Jogador */
typedef struct
{
  char nome[30];
  char *missao; // armazenada dinamicamente
} Jogador;

/* Protótipos */
void cadastrarUmTerritorio(Territorio *t);
void exibirTerritorios(Territorio *mapa, int total, int cadastrados);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int qtdJogadores);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void exibirMissao(char *missao);

/* ====================== MAIN ====================== */
int main()
{
  srand((unsigned)time(NULL)); // aleatoriedade

  /* Cadastro inicial dos territórios */
  int total;
  printf("Digite o número total de territórios a alocar: ");
  if (scanf("%d", &total) != 1 || total <= 0)
  {
    printf("Valor inválido.\n");
    return 1;
  }

  Territorio *mapa = (Territorio *)calloc(total, sizeof(Territorio));
  if (mapa == NULL)
  {
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  int cadastrados = 0;

  /* Cadastro inicial dos jogadores */
  int qtdJogadores = 2;
  Jogador *jogadores = (Jogador *)calloc(qtdJogadores, sizeof(Jogador));
  if (jogadores == NULL)
  {
    printf("Erro ao alocar memória.\n");
    free(mapa);
    return 1;
  }

  for (int i = 0; i < qtdJogadores; i++)
  {
    printf("Digite o nome do Jogador %d: ", i + 1);
    scanf(" %29[^\n]", jogadores[i].nome);
    jogadores[i].missao = (char *)malloc(200 * sizeof(char));
  }

  /* Missões pré-definidas */
  char *missoes[] = {
      "Conquistar 2 territórios",
      "Eliminar todas as tropas da cor vermelha",
      "Controlar pelo menos 10 tropas em um único território",
      "Conquistar qualquer território azul",
      "Manter pelo menos 3 territórios sob seu controle"};
  int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

  /* Sorteio das missões para cada jogador */
  for (int i = 0; i < qtdJogadores; i++)
  {
    atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
    printf("\n🎯 Missão do jogador %s: ", jogadores[i].nome);
    exibirMissao(jogadores[i].missao);
  }

  /* Menu principal */
  int opcao;
  do
  {
    printf("\n=== MENU ===\n");
    printf("1 - Cadastrar novo território\n");
    printf("2 - Listar territórios cadastrados\n");
    printf("3 - Atacar\n");
    printf("4 - Sair\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1)
    {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
      {
      }
      continue;
    }

    if (opcao == 1)
    {
      if (cadastrados < total)
      {
        cadastrarUmTerritorio(mapa + cadastrados);
        cadastrados++;
      }
      else
      {
        printf("⚠ Limite de territórios atingido.\n");
      }
    }
    else if (opcao == 2)
    {
      exibirTerritorios(mapa, total, cadastrados);
    }
    else if (opcao == 3)
    {
      if (cadastrados < 2)
      {
        printf("⚠ Cadastre pelo menos 2 territórios primeiro.\n");
        continue;
      }
      exibirTerritorios(mapa, total, cadastrados);

      int idxAtacante, idxDefensor;
      printf("Digite o número do atacante: ");
      scanf("%d", &idxAtacante);
      printf("Digite o número do defensor: ");
      scanf("%d", &idxDefensor);

      if (idxAtacante < 1 || idxAtacante > cadastrados ||
          idxDefensor < 1 || idxDefensor > cadastrados ||
          idxAtacante == idxDefensor)
      {
        printf("⚠ Escolha inválida.\n");
        continue;
      }

      Territorio *atacante = mapa + (idxAtacante - 1);
      Territorio *defensor = mapa + (idxDefensor - 1);

      if (strcmp(atacante->cor, defensor->cor) == 0)
      {
        printf("⚠ Não pode atacar territórios da mesma cor.\n");
        continue;
      }

      atacar(atacante, defensor);

      /* Verificação de missões */
      for (int i = 0; i < qtdJogadores; i++)
      {
        if (verificarMissao(jogadores[i].missao, mapa, cadastrados))
        {
          printf("\n🏆 O jogador %s venceu! Missão cumprida: %s\n",
                 jogadores[i].nome, jogadores[i].missao);
          liberarMemoria(mapa, jogadores, qtdJogadores);
          return 0;
        }
      }
    }
    else if (opcao == 4)
    {
      printf("Encerrando...\n");
    }
    else
    {
      printf("Opção inválida.\n");
    }
  } while (opcao != 4);

  liberarMemoria(mapa, jogadores, qtdJogadores);
  return 0;
}

/* ====================== FUNÇÕES ====================== */

void cadastrarUmTerritorio(Territorio *t)
{
  printf("Nome do território: ");
  scanf(" %29[^\n]", t->nome);
  printf("Cor do exército: ");
  scanf(" %9s", t->cor);
  printf("Quantidade de tropas: ");
  scanf("%d", &t->tropas);
}

void exibirTerritorios(Territorio *mapa, int total, int cadastrados)
{
  printf("\n=== LISTA DE TERRITÓRIOS ===\n");
  for (int i = 0; i < total; i++)
  {
    if (i < cadastrados)
    {
      Territorio *t = mapa + i;
      printf("[%d] %s | Cor: %s | Tropas: %d\n",
             i + 1, t->nome, t->cor, t->tropas);
    }
    else
    {
      printf("[%d] -- vazio --\n", i + 1);
    }
  }
}

void atacar(Territorio *atacante, Territorio *defensor)
{
  if (atacante->tropas <= 1)
  {
    printf("⚠ O atacante precisa de ao menos 2 tropas.\n");
    return;
  }

  int dadoAtac = (rand() % 6) + 1;
  int dadoDef = (rand() % 6) + 1;

  printf("🎲 %s rolou %d | %s rolou %d\n",
         atacante->nome, dadoAtac, defensor->nome, dadoDef);

  if (dadoAtac > dadoDef)
  {
    printf("🔥 Ataque bem-sucedido!\n");
    strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
    int transferidas = atacante->tropas / 2;
    defensor->tropas = transferidas;
    atacante->tropas -= transferidas;
  }
  else
  {
    printf("🛡 Defesa bem-sucedida!\n");
    atacante->tropas--;
  }
}

void atribuirMissao(char *destino, char *missoes[], int totalMissoes)
{
  int sorteio = rand() % totalMissoes;
  strcpy(destino, missoes[sorteio]);
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho)
{
  // lógica simples inicial: só confere se há pelo menos 2 territórios
  if (strstr(missao, "2 territórios"))
  {
    return (tamanho >= 2);
  }
  if (strstr(missao, "vermelha"))
  {
    for (int i = 0; i < tamanho; i++)
    {
      if (strcmp(mapa[i].cor, "vermelha") == 0)
        return 0;
    }
    return 1; // não restam tropas vermelhas
  }
  if (strstr(missao, "10 tropas"))
  {
    for (int i = 0; i < tamanho; i++)
    {
      if (mapa[i].tropas >= 10)
        return 1;
    }
    return 0;
  }
  // outras missões podem ser expandidas
  return 0;
}

void exibirMissao(char *missao)
{
  printf("%s\n", missao);
}

void liberarMemoria(Territorio *mapa, Jogador *jogadores, int qtdJogadores)
{
  free(mapa);
  for (int i = 0; i < qtdJogadores; i++)
  {
    free(jogadores[i].missao);
  }

  free(jogadores);
}

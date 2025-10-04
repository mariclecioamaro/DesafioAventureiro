/*
  mochila_comparacao.c

  Programa que implementa duas versões de uma "mochila" (inventário):
   - Versão com vetor (lista sequencial)
   - Versão com lista encadeada (dinâmica)

  Funcionalidades:
   - inserir, remover, listar, busca sequencial (ambas estruturas)
   - ordenar vetor (Selection Sort) e busca binária (apenas no vetor)
   - contadores de comparações para busca sequencial (vetor/lista) e busca binária (vetor)
   - menu para o usuário escolher operações e comparar resultados

  Bibliotecas usadas: stdio.h, stdlib.h, string.h, time.h (medição opcional)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 100    // capacidade do vetor (ajustável)
#define NOME_TAM 30
#define TIPO_TAM 20

/* ---------- Definição das structs ---------- */

// Estrutura básica de um Item
typedef struct {
    char nome[NOME_TAM];
    char tipo[TIPO_TAM];
    int quantidade;
} Item;

// Nó para a lista encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

/* ---------- Contadores de comparações (globais) ---------- */
long long seqComparacoesVetor = 0;
long long binComparacoesVetor = 0;
long long seqComparacoesLista = 0;

/* ---------- Funções utilitárias ---------- */

// Remove trailing newline de strings lidas por fgets
void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

// Limpa o buffer de stdin (quando usar scanf seguido de fgets)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* ---------- Funções para vetor (lista sequencial) ---------- */

// Lista os itens do vetor
void listarVetor(Item vetor[], int n) {
    if (n == 0) {
        printf("Vetor: mochila vazia.\n");
        return;
    }
    printf("\n--- Itens na mochila (vetor) ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

// Verifica se já existe item com mesmo nome no vetor
int existeNoVetor(Item vetor[], int n, const char *nome) {
    for (int i = 0; i < n; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) return 1;
    }
    return 0;
}

// Inserir item no final do vetor
void inserirItemVetor(Item vetor[], int *n) {
    if (*n >= MAX_ITENS) {
        printf("Nao ha espaco no vetor (capacidade %d).\n", MAX_ITENS);
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    trim_newline(novo.nome);

    if (strlen(novo.nome) == 0) {
        printf("Nome invalido. Operacao cancelada.\n");
        return;
    }

    if (existeNoVetor(vetor, *n, novo.nome)) {
        printf("Ja existe um item com esse nome no vetor. Nomes devem ser unicos.\n");
        return;
    }

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    trim_newline(novo.tipo);

    printf("Digite a quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Quantidade invalida. Operacao cancelada.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    vetor[*n] = novo;
    (*n)++;
    printf("Item adicionado ao vetor com sucesso.\n");
}

// Remove item do vetor por nome (desloca elementos)
void removerItemVetor(Item vetor[], int *n) {
    if (*n == 0) {
        printf("Vetor vazio. Nada a remover.\n");
        return;
    }
    char nome[NOME_TAM];
    printf("Digite o nome do item a ser removido (vetor): ");
    fgets(nome, sizeof(nome), stdin);
    trim_newline(nome);
    if (strlen(nome) == 0) {
        printf("Nome invalido. Operacao cancelada.\n");
        return;
    }

    int encontrado = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            encontrado = 1;
            // desloca para a esquerda
            for (int j = i; j < *n - 1; j++) vetor[j] = vetor[j + 1];
            (*n)--;
            printf("Item '%s' removido do vetor.\n", nome);
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado no vetor.\n");
}

// Busca sequencial no vetor (retorna índice ou -1). Atualiza seqComparacoesVetor.
int buscarSequencialVetor(Item vetor[], int n, const char *nome) {
    seqComparacoesVetor = 0;
    for (int i = 0; i < n; i++) {
        seqComparacoesVetor++;
        if (strcmp(vetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

// Ordena o vetor por nome (Selection Sort) - O(n^2)
void ordenarVetor(Item vetor[], int n) {
    if (n <= 1) {
        printf("Vetor com menos de 2 itens; nao e necessario ordenar.\n");
        return;
    }
    // Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(vetor[j].nome, vetor[menor].nome) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Item tmp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = tmp;
        }
    }
    printf("Vetor ordenado por nome.\n");
}

// Busca binaria no vetor assumindo que esta ordenado.
// Retorna índice ou -1. Conta comparações em binComparacoesVetor.
int buscarBinariaVetor(Item vetor[], int n, const char *nome) {
    binComparacoesVetor = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        binComparacoesVetor++;
        int cmp = strcmp(nome, vetor[mid].nome);
        if (cmp == 0) return mid;
        else if (cmp < 0) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

/* ---------- Funções para lista encadeada ---------- */

// Criar novo nó (aloca e inicializa)
No* criarNo(const Item *it) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro alocacao memoria.\n");
        exit(EXIT_FAILURE);
    }
    novo->dados = *it;
    novo->proximo = NULL;
    return novo;
}

// Verifica se existe item com mesmo nome na lista
int existeNaLista(No *head, const char *nome) {
    No *p = head;
    while (p) {
        if (strcmp(p->dados.nome, nome) == 0) return 1;
        p = p->proximo;
    }
    return 0;
}

// Inserir no inicio da lista (poderia inserir no fim, mas inicio e simples)
void inserirItemLista(No **head) {
    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    trim_newline(novo.nome);
    if (strlen(novo.nome) == 0) {
        printf("Nome invalido. Operacao cancelada.\n");
        return;
    }
    if (existeNaLista(*head, novo.nome)) {
        printf("Ja existe um item com esse nome na lista. Nomes devem ser unicos.\n");
        return;
    }
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    trim_newline(novo.tipo);
    printf("Digite a quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Quantidade invalida. Operacao cancelada.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    No *node = criarNo(&novo);
    node->proximo = *head;
    *head = node;
    printf("Item adicionado na lista encadeada com sucesso.\n");
}

// Remover item da lista por nome
void removerItemLista(No **head) {
    if (*head == NULL) {
        printf("Lista vazia. Nada a remover.\n");
        return;
    }
    char nome[NOME_TAM];
    printf("Digite o nome do item a ser removido (lista): ");
    fgets(nome, sizeof(nome), stdin);
    trim_newline(nome);
    if (strlen(nome) == 0) {
        printf("Nome invalido. Operacao cancelada.\n");
        return;
    }

    No *atual = *head, *ant = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL) { // remover head
                *head = atual->proximo;
            } else {
                ant->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido da lista.\n", nome);
            return;
        }
        ant = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado na lista.\n");
}

// Listar itens da lista
void listarLista(No *head) {
    if (!head) {
        printf("Lista: mochila vazia.\n");
        return;
    }
    printf("\n--- Itens na mochila (lista encadeada) ---\n");
    No *p = head;
    int idx = 1;
    while (p) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               idx, p->dados.nome, p->dados.tipo, p->dados.quantidade);
        idx++;
        p = p->proximo;
    }
}

// Busca sequencial na lista (retorna ponteiro para nó ou NULL). Atualiza seqComparacoesLista.
No* buscarSequencialLista(No *head, const char *nome) {
    seqComparacoesLista = 0;
    No *p = head;
    while (p) {
        seqComparacoesLista++;
        if (strcmp(p->dados.nome, nome) == 0) return p;
        p = p->proximo;
    }
    return NULL;
}

/* ---------- Funções de interface / menus ---------- */

// Sub-menu para operações no vetor
void menuVetor(Item vetor[], int *n) {
    int opc;
    do {
        printf("\n--- MENU VETOR ---\n");
        printf("1. Inserir item (vetor)\n");
        printf("2. Remover item (vetor)\n");
        printf("3. Listar itens (vetor)\n");
        printf("4. Buscar sequencial (vetor)\n");
        printf("5. Ordenar vetor por nome\n");
        printf("6. Buscar binaria (vetor) - exige vetor ordenado\n");
        printf("7. Mostrar comparadores de busca (vetor)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) {
            limpar_buffer();
            opc = -1;
        } else limpar_buffer();

        if (opc == 1) inserirItemVetor(vetor, n);
        else if (opc == 2) removerItemVetor(vetor, n);
        else if (opc == 3) listarVetor(vetor, *n);
        else if (opc == 4) {
            if (*n == 0) { printf("Vetor vazio.\n"); continue; }
            char nome[NOME_TAM];
            printf("Digite o nome a buscar (sequencial - vetor): ");
            fgets(nome, sizeof(nome), stdin);
            trim_newline(nome);
            clock_t inicio = clock();
            int idx = buscarSequencialVetor(vetor, *n, nome);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (idx >= 0) {
                printf("Item encontrado no indice %d: Nome: %s | Tipo: %s | Quantidade: %d\n",
                       idx, vetor[idx].nome, vetor[idx].tipo, vetor[idx].quantidade);
            } else printf("Item nao encontrado (sequencial - vetor).\n");
            printf("Comparacoes (sequencial - vetor): %lld | Tempo: %.6f s\n", seqComparacoesVetor, tempo);
        }
        else if (opc == 5) {
            clock_t inicio = clock();
            ordenarVetor(vetor, *n);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo ordenacao: %.6f s\n", tempo);
        }
        else if (opc == 6) {
            if (*n == 0) { printf("Vetor vazio.\n"); continue; }
            char nome[NOME_TAM];
            printf("Digite o nome a buscar (binaria - vetor, vetor deve estar ordenado): ");
            fgets(nome, sizeof(nome), stdin);
            trim_newline(nome);
            clock_t inicio = clock();
            int idx = buscarBinariaVetor(vetor, *n, nome);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (idx >= 0) {
                printf("Item encontrado no indice %d: Nome: %s | Tipo: %s | Quantidade: %d\n",
                       idx, vetor[idx].nome, vetor[idx].tipo, vetor[idx].quantidade);
            } else printf("Item nao encontrado (binaria - vetor).\n");
            printf("Comparacoes (binaria - vetor): %lld | Tempo: %.6f s\n", binComparacoesVetor, tempo);
        }
        else if (opc == 7) {
            printf("Comparacoes acumuladas:\n");
            printf(" - Busca sequencial (vetor) ultima exec: %lld\n", seqComparacoesVetor);
            printf(" - Busca binaria (vetor) ultima exec: %lld\n", binComparacoesVetor);
        }
        else if (opc == 0) { /* voltar */ }
        else printf("Opcao invalida.\n");

    } while (opc != 0);
}

// Sub-menu para operações na lista encadeada
void menuLista(No **head) {
    int opc;
    do {
        printf("\n--- MENU LISTA ENCADEADA ---\n");
        printf("1. Inserir item (lista)\n");
        printf("2. Remover item (lista)\n");
        printf("3. Listar itens (lista)\n");
        printf("4. Buscar sequencial (lista)\n");
        printf("5. Mostrar comparador de busca (lista)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) {
            limpar_buffer();
            opc = -1;
        } else limpar_buffer();

        if (opc == 1) inserirItemLista(head);
        else if (opc == 2) removerItemLista(head);
        else if (opc == 3) listarLista(*head);
        else if (opc == 4) {
            if (*head == NULL) { printf("Lista vazia.\n"); continue; }
            char nome[NOME_TAM];
            printf("Digite o nome a buscar (sequencial - lista): ");
            fgets(nome, sizeof(nome), stdin);
            trim_newline(nome);
            clock_t inicio = clock();
            No *res = buscarSequencialLista(*head, nome);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            if (res) {
                printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                       res->dados.nome, res->dados.tipo, res->dados.quantidade);
            } else printf("Item nao encontrado (lista).\n");
            printf("Comparacoes (sequencial - lista): %lld | Tempo: %.6f s\n", seqComparacoesLista, tempo);
        }
        else if (opc == 5) {
            printf("Comparacoes (ultima busca sequencial - lista): %lld\n", seqComparacoesLista);
        }
        else if (opc == 0) { /* voltar */ }
        else printf("Opcao invalida.\n");

    } while (opc != 0);
}

/* ---------- Limpeza final da lista ---------- */
void limparLista(No **head) {
    No *p = *head;
    while (p) {
        No *aux = p->proximo;
        free(p);
        p = aux;
    }
    *head = NULL;
}

/* ---------- Menu principal ---------- */
int main() {
    Item vetor[MAX_ITENS];
    int nVetor = 0;
    No *head = NULL;

    printf("=== Comparacao: Vetor x Lista Encaedada (Mochila) ===\n");
    int opc;
    do {
        printf("\nMenu principal:\n");
        printf("1. Operar na mochila (VETOR)\n");
        printf("2. Operar na mochila (LISTA ENCADEADA)\n");
        printf("3. Mostrar ambos (listar vetor e lista)\n");
        printf("4. Comparar contadores de comparacoes entre estruturas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) {
            limpar_buffer();
            opc = -1;
        } else limpar_buffer();

        if (opc == 1) {
            menuVetor(vetor, &nVetor);
        } else if (opc == 2) {
            menuLista(&head);
        } else if (opc == 3) {
            printf("\n-- Conteudo do vetor (%d itens) --\n", nVetor);
            listarVetor(vetor, nVetor);
            printf("\n-- Conteudo da lista encadeada --\n");
            listarLista(head);
        } else if (opc == 4) {
            printf("\n--- Comparacao de contadores ---\n");
            printf("Busca sequencial (vetor) ultima exec: %lld comparacoes\n", seqComparacoesVetor);
            printf("Busca binaria (vetor) ultima exec: %lld comparacoes\n", binComparacoesVetor);
            printf("Busca sequencial (lista) ultima exec: %lld comparacoes\n", seqComparacoesLista);
            printf("\nDica: busca binaria e geralmente muito mais eficiente em vetores ordenados.\n");
        } else if (opc == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opc != 0);

    limparLista(&head);
    return 0;
}
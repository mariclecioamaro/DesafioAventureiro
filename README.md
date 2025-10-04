# 🎒 Sistema de Mochila em C (Vetores x Listas Encadeadas)

Este projeto implementa duas versões de um **sistema de inventário (mochila)** para jogos de sobrevivência, comparando o uso de **vetores (listas sequenciais)** e **listas encadeadas**.  

O objetivo é mostrar na prática como a escolha da estrutura de dados afeta o desempenho em operações comuns, como inserção, remoção, listagem e busca.  

---

## 🚀 Funcionalidades

As operações implementadas em **ambas as estruturas** são:  
- **Inserção de itens** (nome, tipo, quantidade).  
- **Remoção de itens por nome**.  
- **Listagem dos itens** da mochila.  
- **Busca sequencial por nome**.  

Funções **exclusivas do vetor**:  
- **Ordenação** dos itens por nome (Bubble Sort).  
- **Busca binária** para localizar rapidamente um item crítico.  
- **Contador de comparações** em buscas (sequencial e binária).  

---

## 📂 Estruturas de Dados

### Estrutura do Item
```c
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;
```
- Estrutura da Lista Encadeada
```
typedef struct No {
    Item dados;
    struct No* proximo;
} No;
```
# 🛠️ Tecnologias Utilizadas

- Linguagem: C

- Bibliotecas:

- <stdio.h> → Entrada e saída

- <stdlib.h> → Alocação dinâmica

- <string.h> → Manipulação de strings

- <time.h> → Medição opcional de tempo

# 📖 Como Executar

- Salve o código como mochila.c.

- Compile com:

- gcc mochila.c -o mochila


- Execute:

- ./mochila

# 📋 Exemplo de Uso
- Menu principal
- ==== Sistema de Mochila ====
- Inserir item
- Remover item
- Listar itens
- Buscar sequencial
- Ordenar (apenas vetor)
- Buscar binária (apenas vetor)
- Sair
- Escolha uma opção:

- Inserção
- Digite o nome do item: Rifle
- Digite o tipo do item: arma
- Digite a quantidade: 1
- Item inserido com sucesso!

- Busca sequencial
- Digite o nome do item a buscar: KitMedico
- Item encontrado! Comparações: 3
- Nome: KitMedico | Tipo: cura | Quantidade: 2

- Busca binária (apenas vetor)
- Digite o nome do item a buscar: Rifle
- Item encontrado! Comparações: 2
- Nome: Rifle | Tipo: arma | Quantidade: 1

# 📊 Comparação de Estruturas
- Operação	Vetor (lista sequencial)	Lista encadeada
- Inserção	O(1) no final (se houver espaço) / O(n) no meio	O(1) no início / O(n) no meio/final
- Remoção	O(n) (deslocamentos necessários)	O(n) (ajuste de ponteiros)
- Listagem	O(n)	O(n)
- Busca sequencial	O(n)	O(n)
- Ordenação	O(n²) (Bubble Sort)	Não implementada
- Busca binária	O(log n) (após ordenação)	Não aplicável
# 🎯 Objetivo Educacional

- Este projeto reforça conceitos de:

- Comparação entre estruturas de dados (vetores vs listas encadeadas).

- Análise de desempenho empírica (quantidade de comparações em buscas).

- Ordenação e busca binária como ferramentas para otimizar acessos.

- Modularização em C com funções separadas para cada estrutura.

# 📌 Próximos Passos

- Implementar alocação dinâmica no vetor.

- Testar outros algoritmos de ordenação (QuickSort, MergeSort).

- Adicionar persistência em arquivo (salvar/carregar inventário).

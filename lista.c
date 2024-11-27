// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular


// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Definição da interface do TAD - NÃO ALTERAR

/* estrutura de um item da lista
struct item_t
{
  int valor ;			// valor do item
  struct item_t *ant ;		// item anterior
  struct item_t *prox ;	// próximo item
} ;

// estrutura de uma lista
struct lista_t
{
  struct item_t *prim ;	// primeiro item
  struct item_t *ult ;		// último item
  int tamanho ;		// número de itens da lista
} ;*/
// Nas operações insere/retira/consulta/procura, a lista inicia na
// posição 0 (primeiro item) e termina na posição TAM-1 (último item).

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
struct lista_t *lista_cria ()
{
  struct lista_t *f;
 
  f = malloc (sizeof(struct lista_t));

  if (!f) 
    return (NULL);

  f->prim = NULL;
  f->ult = NULL;
  f->tamanho = 0;

  return f;
}

// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi (struct lista_t *lst)
{
  long pos = 0;
  int item;

  if (!lst)
    return NULL;

  if (lst->tamanho != 0)
    while (lst->tamanho > 0)
      lista_retira(lst, &item, pos);
      
  free(lst);

  return NULL;
}

// Insere o item na lista na posição indicada;
// se a posição for além do fim da lista ou for -1, insere no fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_insere (struct lista_t *lst, int item, int pos)
{
  struct item_t *novo, *aux;
  long i;

  if (!lst)
    return -1;

  novo = malloc(sizeof(struct item_t));
  if (!novo)
    return -1;
  novo->valor = item;

  if (lst->tamanho == 0)
  {
    novo->prox = NULL;
    novo->ant = NULL;
    lst->ult = novo;
    lst->prim = novo;
    lst->tamanho = lst->tamanho + 1;
    return lista_tamanho(lst);
  }
  
  if (lst->tamanho <= pos || pos == -1) 
  {
    novo->prox = NULL; 
    novo->ant = lst->ult;
    lst->ult->prox = novo;
    lst->ult = novo;
    lst->tamanho = lst->tamanho + 1;
    return lista_tamanho(lst);
  }

  if (pos == 0)
  {
    novo->ant = NULL;
    novo->prox = lst->prim;
    lst->prim->ant = novo;
    lst->prim = novo;
    lst->tamanho = lst->tamanho + 1;
    return lista_tamanho(lst);
  }
  
  i = 0;
  aux = lst->prim;
  while (aux)
  {
    if (i == pos-1)
    {
      novo->ant = aux;
      novo->prox = aux->prox;
      novo->valor = item;
      aux->prox->ant = novo;
      aux->prox = novo;
      lst->tamanho = lst->tamanho + 1;
      return lista_tamanho(lst);
    }
    i++;
    aux = aux->prox;
  }
  return -1;
}

// Retira o item da lista da posição indicada.
// se a posição for -1, retira do fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_retira (struct lista_t *lst, int *item, int pos)
{
  struct item_t *aux;
  long i;

  if (!lst)
    return -1;
  
  if (lst->tamanho <= 0)
    return -1;

  lista_consulta(lst, &*item, pos);
 
  if (lst->tamanho == 1 && pos == 0)
  {
    lst->prim->prox = NULL;
    lst->ult->ant = NULL;
    free(lst->prim);
    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;
    return 0;
  }

  if (pos == 0)
  {
    aux = lst->prim;
    aux->prox->ant = NULL;
    lst->prim = aux->prox;
    aux->prox = NULL;
    free(aux);
    lst->tamanho = lst->tamanho - 1;
    return lista_tamanho(lst);
  }

  if (lst->tamanho <= pos || pos == -1)
  {
    aux = lst->ult;
    aux->ant->prox = NULL;
    lst->ult = aux->ant;
    aux->ant = NULL;
    free(aux);
    lst->tamanho = lst->tamanho - 1;
    return lista_tamanho(lst);
  }
  
  i = 1;
  aux = lst->prim->prox;
  while (aux)
  {
    if (pos == i)
    {
      aux->ant->prox = aux->prox;
      aux->prox->ant = aux->ant;
      aux->prox = NULL;
      aux->ant = NULL;
      free(aux);
      lst->tamanho = lst->tamanho - 1;
      return lista_tamanho(lst);
    }
    i++;
    aux = aux->prox;
  }

  return -1;
}

// Informa o valor do item na posição indicada, sem retirá-lo.
// se a posição for -1, consulta do fim.
// Retorno: número de itens na lista ou -1 em erro.
int lista_consulta (struct lista_t *lst, int *item, int pos)
{
  struct item_t *aux;
  long i;

  if (!lst)
    return -1;

  if (pos == -1)
  {
    *item = lst->ult->valor;
    return (lst->tamanho);
  }
  
  aux = lst->prim;
  i = 0;
  while (aux)
  {
    if (i == pos)
    {
      *item = aux->valor;
      return (lst->tamanho);
    }
    i++;
    aux = aux->prox;
  }
  return -1;
}

// Informa a posição da 1ª ocorrência do valor indicado na lista.
// Retorno: posição do valor ou -1 se não encontrar ou erro.
int lista_procura (struct lista_t *lst, int valor)
{
  struct item_t *aux;
  long posicao;
  
  if (!lst)
    return -1;
  
  posicao = 0;
  aux = lst->prim;
  while (aux)
  {
    if (aux->valor == valor)
      return posicao;
    posicao++;
    aux = aux->prox;
  }
  return -1; 
}

// Informa o tamanho da lista (o número de itens presentes nela).
// Retorno: número de itens na lista ou -1 em erro.
int lista_tamanho (struct lista_t *lst)
{ 
  if (!lst)
    return -1;

  return (lst->tamanho);
}

// Imprime o conteúdo da lista do inicio ao fim no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois, sem newline.
void lista_imprime (struct lista_t *lst)
{
  struct item_t *aux;

  if (!lst)
    return;

  if (lst->tamanho <= 0) 
    return;

  aux = lst->prim;
  if (aux)
    printf("%d", aux->valor);
  aux = aux->prox;
  while (aux)
  {
    printf(" %d", aux->valor);
    aux = aux->prox;
  }
  return;
}


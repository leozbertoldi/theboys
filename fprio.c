// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR
// descreve um nodo da fila de prioridades
/*struct fpnodo_t
{
  void *item ;                  // item associado ao nodo
  int   tipo ;                  // tipo do item
  int   prio ;                  // prioridade do item
  struct fpnodo_t *prox;        // próximo nodo
};*/

/*  descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;       // primeiro nodo da fila
  int num ;                     // número de itens na fila
} ;*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria ()
{
  struct fprio_t *f;

  f = malloc(sizeof(struct fprio_t));

  if (!f)
    return NULL;

  f->prim = NULL;
  f->num = 0;

  return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f)
{
  struct fpnodo_t *aux;
  
  if (!f)
    return NULL;

  aux = f->prim;
  while (aux)
  {
    f->prim = aux->prox;
    aux->prox = NULL;
    free(aux->item);
    aux->item = NULL;
    free(aux);
    aux = NULL;
    f->num--;
    aux = f->prim;
  }

  free(f);
  return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
  struct fpnodo_t *novo;
  struct fpnodo_t *aux;

  if (!f || !item)
    return -1;
  
  novo = malloc(sizeof(struct fpnodo_t));
  if (!novo)
    return -1;

  novo->tipo = tipo;
  novo->prio = prio;
  novo->item = item;
  novo->prox = NULL;

  if (f->num == 0)
  {
    f->prim = novo;
    f->num++;
    return fprio_tamanho(f);
  }

  aux = f->prim;
  while (aux)
  {
    if (aux->item == item)
    {
      free(novo);
      return -1;
    }
    aux = aux->prox;
  }

  if (prio < f->prim->prio)
  {
    novo->prox = f->prim;
    f->prim = novo;
    f->num++;
    return fprio_tamanho(f);
  }

  aux = f->prim;
  for (long i = 1; i < f->num; i++)
    aux = aux->prox;
  if (aux->prio <= prio)
  {
    aux->prox = novo;
    f->num++;
    return fprio_tamanho(f);
  }

  aux = f->prim;
  while (aux)
  {
    novo->prox = aux->prox;
    aux->prox = novo;
    if (prio < novo->prox->prio)
    {
      f->num++;
      return fprio_tamanho(f);
    }
    aux->prox = novo->prox;
    aux = aux->prox;
  }

  return -1;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
  struct fpnodo_t *aux;
  void *item;

  if (!f || !f->prim || !tipo || !prio)
    return NULL;

  aux = f->prim;
  
  *tipo = aux->tipo;
  *prio = aux->prio;
  item = aux->item;

  if (f->num == 1)
    f->prim = NULL;
  else
    f->prim = aux->prox;
  aux->prox = NULL;
  f->num--;

  free(aux);
  
  return item;       
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f)
{
  if (!f)
    return -1;

  return f->num;  
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
  struct fpnodo_t *aux;

  if (!f || !f->prim)
    return;

  aux = f->prim;
  printf("(%d %d)", aux->tipo, aux->prio);
  aux = aux->prox;
  while (aux)
  {
    printf(" (%d %d)", aux->tipo, aux->prio);
    aux = aux->prox;
  }
 
  return;
}


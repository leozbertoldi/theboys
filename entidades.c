#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "entidades.h"
#include "auxiliares.h"
#include "lista.h"
#include "fprio.h"

struct mundo *inicializa_mundo(struct mundo *w)  
{
  int i;
  struct heroi *h;
  struct base *b;
  struct missao *m;

  for (i = 0; i < N_HEROIS; i++)
    w->herois[i] = inicializa_heroi(h, i);

  for (i = 0; i < N_BASES; i++)
    w->bases[i] = inicializa_base(b, i);

  for (i = 0; i < N_MISSOES; i++)
    w->missoes[i] = inicializa_missao(m, i);

  w->tamanho.x = N_TAMANHO_MUNDO;
  w->tamanho.y = N_TAMANHO_MUNDO;

  w->lef = fprio_cria();
  w->clock = T_INICIO;

  return w;
}

struct heroi *inicializa_heroi(struct heroi *h, int i)
{
  h = malloc(sizeof(struct heroi));
  if (!h)
    return NULL;

  h->ID = i;
  h->experiencia = 0;
  h->paciencia = aleat(0,100); 
  h->velocidade = aleat(50,5000);  
  h->habilidades = cjto_aleat(aleat(1,3),N_HABILIDADES);
  h->base_heroi = NULL;
  h->vivo = true;

  return h;
}

struct base *inicializa_base(struct base *b, int i)
{
  b = malloc(sizeof(struct base));
  if (!b)
    return NULL;

  b->ID = i;
  b->local.x = aleat(0,N_TAMANHO_MUNDO-1);
  b->local.y = aleat(0,N_TAMANHO_MUNDO-1);
  b->lotacao = aleat(3,10); 
  b->presentes = cjto_cria(b->lotacao);
  b->espera = lista_cria();

  return b;
}

struct missao *inicializa_missao(struct missao *m, int i)
{
  m = malloc(sizeof(struct missao));
  if (!m)
    return NULL;

  m->ID = i;
  m->local.x = aleat(0,N_TAMANHO_MUNDO-1);
  m->local.y = aleat(0,N_TAMANHO_MUNDO-1);
  m->habilidades = cjto_aleat(aleat(6,10),N_HABILIDADES);
  m->perigo = aleat(0,100);
  m->cumprida = false;
  m->tentativas = 0;

  return m;
}
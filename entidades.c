#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "entidades.h"
#include "auxiliares.h"
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

struct mundo *inicializa_mundo()  
{
  int i;
  struct mundo *w;

  w = malloc(sizeof(struct mundo));
  if (!w)
    return NULL;
  
  for (i = 0; i < N_HEROIS; i++)
    w->herois[i] = inicializa_heroi(i);

  for (i = 0; i < N_BASES; i++)
    w->bases[i] = inicializa_base(i);
    
  for (i = 0; i < N_MISSOES; i++)
    w->missoes[i] = inicializa_missao(i);

  w->tamanho.x = N_TAMANHO_MUNDO;
  w->tamanho.y = N_TAMANHO_MUNDO;

  w->lef = fprio_cria();
  w->clock = T_INICIO;
  w->eventos_tratados = 0;

  return w;
}

struct heroi *inicializa_heroi(int i)
{
  struct heroi *h;

  h = malloc(sizeof(struct heroi));
  if (!h)
    return NULL;   

  h->ID = i;
  h->experiencia = 0;
  h->paciencia = aleat(0,100); 
  h->velocidade = aleat(50,5000);  
  h->habilidades = cjto_aleat(aleat(1,3),N_HABILIDADES);
  h->ID_base = -1;
  h->vivo = true;

  return h;
}

struct base *inicializa_base(int i)
{
  struct base *b;

  b = malloc(sizeof(struct base));
  if (!b)
    return NULL;   

  b->local = malloc(sizeof(struct local));
  
  b->ID = i;
  b->local->x = aleat(0,N_TAMANHO_MUNDO-1);
  b->local->y = aleat(0,N_TAMANHO_MUNDO-1);
  b->lotacao = aleat(3,10); 
  b->presentes = cjto_cria(N_HEROIS);
  b->espera = lista_cria();
  b->max_espera = 0;
  b->missoes_participadas = 0;

  return b;
}

struct missao *inicializa_missao(int i)
{
  struct missao *m;

  m = malloc(sizeof(struct missao));
  if (!m)
    return NULL;   

  m->local = malloc(sizeof(struct local));

  m->ID = i;
  m->local->x = aleat(0,N_TAMANHO_MUNDO-1);
  m->local->y = aleat(0,N_TAMANHO_MUNDO-1);
  m->habilidades = cjto_aleat(aleat(6,10),N_HABILIDADES);
  m->perigo = aleat(0,100);
  m->cumprida = false;
  m->tentativas = 1;

  return m;
}
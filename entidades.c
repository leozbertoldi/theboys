#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "entidades.h"

struct mundo *inicializa_mundo(struct mundo *w)  
{
  int i;
  struct heroi h;
  struct base b;
  struct missao m;

  w.Nherois = N_HEROIS;
  for (i = 0; i < N_HEROIS; i++)
    w.herois[i] = inicializa_heroi(h, i);

  w.Nbases = N_BASES;
  for (i = 0; i < N_BASES; i++)
    w.bases[i] = inicializa_base(b, i);

  w.Nmissoes = N_MISSOES;
  for (i = 0; i < N_MISSOES; i++)
    w.missoes[i] = inicializa_missao(m, i);

  w.tamanho->x = N_TAMANHO_MUNDO;
  w.tamanho->y = N_TAMANHO_MUNDO;

  w.relogio = 0;

  return w;
}

struct heroi *inicializa_heroi(struct heroi *h, int i)
{
  int j, habilidade;

  h.ID = i;
  h.experiencia = 0;
  h.paciencia = rand() % 101; //aleat entre 0 e 100
  h.velocidade = rand() % 4951 + 50;  //aleat entre 50 e 5000
  h.habilidades = cjto_cria(3);
  if (!h.habilidades)
    return NULL;
  for (j = 0; j < 3; j++)
  {
    habilidade = rand() % N_HABILIDADES; 
    cjto_insere(h.habilidades, habilidade);
  }
  h.base_heroi = NULL;
  h.vivo = true;

  return h;
}

struct base *inicializa_base(struct base *b, int i)
{
  b.ID = i;
  b.local->x = rand() % N_TAMANHO_MUNDO;
  b.local->y = rand() % N_TAMANHO_MUNDO;
  b.lotacao = rand() % 8 + 3; //aleat entre 3 e 10
  b.presentes = cjto_cria(b.lotacao);
  b.espera = lista_cria();

  return b;
}

struct missao *inicializa_missao(struct missao *m, int i)
{
  int j, habilidade, tamanho;

  m.ID = i;
  m.local->x = rand() % N_TAMANHO_MUNDO;
  m.local->y = rand() % N_TAMANHO_MUNDO;
  tamanho = rand() % 5 + 6; //aleat entre 6 e 10;
  m.habilidades = cjto_cria(tamanho);
  for (j = 0; j < tamanho; j++)
  {
    habilidade = rand() % N_HABILIDADES;
    cjto_insere(m.habilidades, habilidade);
  }
  m.perigo = rand() % 101;
  m.cumprida = false;
  m.tentativas = 0;

  return m;
}
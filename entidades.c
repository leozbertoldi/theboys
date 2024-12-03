#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "entidades.h"

struct mundo *inicializa_mundo(struct mundo *m)  
{
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
  h.base = NULL;
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
}

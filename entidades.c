#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"

struct mundo *inicializa_mundo(struct mundo *m)  
{
  struct heroi h;

  if (!m)
    return NULL;
 
  for (i = 0; i < m->nherois; i++)
  { 
    h = malloc(sizeof(struct heroi));
    
    if (!h)
      return NULL;

    inicializa_heroi(h, i);
    m->herois[i] = h;
  }
}

struct heroi *inicializa_heroi(struct heroi *h, int i)
{
  h->ID = i;
  h->experiencia = 0;
  h->paciencia = rand() % 101; //aleat entre 0 e 100
  h->velocidade = rand() % 4951 + 50;  //aleat entre 50 e 5000
  return h;
}

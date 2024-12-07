// programa principal do projeto "The Boys - 2024/2"
// Autor: Leonardo Zandonai Bertoldi, GRR20240476

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"
#include "auxiliares.h"

// programa principal
int main ()
{
  struct mundo *w;
  struct evento_t *ev;
  bool end = false;
  int tipo, tempo, i;

  srand(0);

  w = inicializa_mundo();
  
  base_aleatoria(w);

  agenda_missao(w);

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;
  ev->tipo = EV_FIM;
  ev->tempo = T_FIM_DO_MUNDO;
  ev->dado1 = 0;
  ev->dado2 = 0;
  fprio_insere(w->lef, ev, EV_FIM, T_FIM_DO_MUNDO);
  
  while (!end)
  {
    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;
    
    ev = fprio_retira(w->lef, &tipo, &tempo);
    w->clock = tempo;
    w->eventos_tratados++;
    
    switch(tipo)
    {
      case EV_CHEGA: chega(w, ev);
      break;

      case EV_ESPERA: espera(w, ev);
      break;

      case EV_DESISTE: desiste(w, ev);
      break;

      case EV_AVISA: avisa(w, ev);
      break;

      case EV_ENTRA: entra(w, ev);
      break;

      case EV_SAI: sai(w, ev);
      break;

      case EV_VIAJA: viaja(w, ev);
      break;

      case EV_MORRE: morre(w, ev);
      break;

      case EV_MISSAO: missao(w, ev);
      break;

      //possível leak
      case EV_FIM: fim(w);
      end = true;
      break;

      free(ev);
    }
    
  }

  for (i = 0; i < N_HEROIS; i++)
  {
    free(w->herois[i]->habilidades);
    free(w->herois[i]);
  }

  for (i = 0; i < N_BASES; i++)
  {
    free(w->bases[i]->local);
    free(w->bases[i]->espera);
    free(w->bases[i]->presentes);
    free(w->bases[i]);
  }

  for (i = 0; i < N_MISSOES; i++)
  {
    free(w->missoes[i]->local);
    free(w->missoes[i]->habilidades);
    free(w->missoes[i]);
  }

  free(w->lef);
  free(w);

  return (0);
}

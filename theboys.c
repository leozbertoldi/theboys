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
  bool fim = false;
  int tipo, prioridade;

  w = malloc(sizeof(struct mundo));
  w = inicializa_mundo(w);
 
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

  srand(0);
  
  while (!fim)
  {
    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;
    
    ev = fprio_retira(w->lef, &tipo, &tempo);
    w->clock = ev->tempo;
    
    switch(ev->tipo)
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
      case EV_FIM: fim(w, ev);
      fim = true;
      break;

      free(ev);
    }
    
  }

  


  /*printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", t, heroi, base, presentes, lotacao);
  printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", t, heroi, base, presentes, lotacao);

  printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", t, heroi, base, espera);
  
  printf("%6d: DESISTE HEROI %2d BASE %d\n", t, heroi, base);

  printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA ", t, base, presentes, lotacao);
  lista_imprime(b.espera);
  printf("\n");
  printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", t, base, heroi);
  
  printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", t, heroi, base, presentes, lotacao, t);

  printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", t, heroi, base, presentes, lotacao);

  printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", t, heroi, base, base, distancia, velocidade, t);

  printf("%6d: MORRE HEROI %2d MISSAO %d\n", t, heroi, missao);

  printf("%6d: MISSAO %d TENT %d HAB REQ: ", t, missao, tentativas);
  cjto_imprime(m.habilidades);
  printf("\n");
  printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", t, missao, base);
  cjto_imprime(habilidades dos herois);
  printf("\n");
  printf("%6d: MISSAO %d IMPOSSIVEL\n", t, missao);
  printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ", t, missao, base, distancia);
  cjto_imprime(b.presentes);
  printf("\n");
  printf("%6d: MISSAO %d HAB HEROI %2d: ", t, missao, heroi);
  cjto_imprime(h.habilidades);
  printf("\n");
  printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", t, missao, base);
  cjto_imprime(habilidades dos herois);
  printf("\n");


  // destruir o mundo

  return (0) ;
}

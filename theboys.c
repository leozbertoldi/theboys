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
  struct fprio_t *lef;

  w = inicializa_mundo(w);
  lef = fprio_cria();
  base_aleatoria(w);
  agenda_missao(w);
  lef = evento fim(T_FIM_DO_MUNDO);

  srand(0);

  for (w.relogio = 0; w.relogio < T_FIM_DO_MUNDO; w.relogio++)
  {
    
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

  printf("EVENTOS TRATADOS: %d\n", eventos);
  printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS ");
  printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS ");
  cjto_imprime(habilidades dos herois);
  printf("\n");
  printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", base, lotacao, maximodeheroisnaespera, missoes);
  printf("MISSOES CUMRPIDAS: %d/%d (%.1f%%)\n", cumpridas, geradas, porcentagem);
  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tentativas, max_tentativas, media);
  printf("TAXA MORTALIDADE: %.1f%%", mortes porcentagem);*/



  // destruir o mundo

  return (0) ;
}

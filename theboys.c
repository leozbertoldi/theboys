// programa principal do projeto "The Boys - 2024/2"
// Autor: Leonardo Zandonai Bertoldi, GRR20240476

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"

#define

// programa principal
int main ()
{
  // iniciar o mundo
  struct mundo m;
  struct heroi h;
  int t_inicial, t_final, i;
  
  srand(0);

  t_inicial = 0;
  t_final = 525600;
  m->tamanho = 20000;
  m->nhabilidades = 10;
  m->nherois = m->nhabilidades*5;
  m->nbases = m->nherois/5;
  m->nmissoes = t_final/100;

  for (i = 0; i < m->nherois; i++)
  {
    h->ID = i;
    h->experiencia = 0;
    h->paciencia = rand() % 101; //aleat entre 0 e 100
    h->velocidade = rand() % 4951 + 50;  //aleat entre 50 e 5000
    
    m->herois[i] = h;

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

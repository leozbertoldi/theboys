#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"
#include "auxiliares.h"

//EVENTOS INICIAIS
//=======================================================================================
int base_aleatoria(struct mundo *w)
{
  int i, base, tempo;
  struct evento_t *ev;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  ev->tipo = EV_CHEGA;
  ev->dado2 = 0;

  for (i = 0; i < N_HEROIS; i++)
  {
    base = aleat(0,N_BASES-1);
    tempo = aleat(0,4320);
    ev->tempo = tempo;
    ev->dado1 = base;

    fprio_insere(w->lef, ev, EV_CHEGA, tempo);
  }

  return 0;
}

int agenda_missao(struct mundo *w)
{
  int i, tempo;
  struct evento_t *ev;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  ev->tipo = EV_MISSAO;
  ev->dado1 = 0;
  ev->dado2 = 0;

  for (i = 0; i < N_MISSOES; i++)
  {
    tempo = aleat(0,T_FIM_DO_MUNDO-1);
    ev->tempo = tempo;
    fprio_insere(w->lef, ev, EV_MISSAO, tempo); 
  }

  return 0;
}
//=======================================================================================


//evento CHEGA
int chega(struct mundo *w, struct evento_t *ev)
{
  int i;
  bool espera, vagas, espera_vazia;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  heroi->ID_base = ev->dado1;
  
  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];

  vagas = (base->lotacao > cjto_card(base->presentes));
  espera_vazia = (lista_tamanho(base->espera) == 0);
  if (vagas && espera_vazia)
    espera = true;
  else
    espera = ((heroi->paciencia) > (10 * lista_tamanho(base->espera)));

  if (espera)
    ev->tipo = EV_ESPERA;
  else 
    ev->tipo = EV_DESISTE;

  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento ESPERA
int espera(struct mundo *w, struct evento_t *ev)
{
  int i;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];

  lista_insere(base->espera, heroi->ID, -1);
  
  ev->tipo = EV_AVISA;
  ev->tempo = w->clock;
  ev->dado1 = base->ID;
  ev->dado2 = 0;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento DESISTE
int desiste(struct mundo *w, struct evento_t *ev)
{
  int i, D;
  struct evento_t *ev;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  D = aleat(0,N_BASES-1);

  ev->tipo = EV_VIAJA;
  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = D;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento AVISA
int avisa(struct mundo *w, struct evento_t *ev)
{
  int i;
  bool vagas, espera;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];
  
  vagas = (base->lotacao >= cjto_card(base->presentes));
  espera = (lista_tamanho(base->espera) > 0);
  while (vagas && espera)
  {
    lista_retira(base->espera, heroi->ID, 0);
    cjto_insere(base->presentes, heroi->ID);

    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;

    ev->tipo = EV_ENTRA;
    ev->tempo = w->clock;
    ev->dado1 = heroi->ID;
    ev->dado2 = base->ID;
    fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

    vagas = (base->lotacao >= cjto_card(base->presentes));
    espera = (lista_tamanho(base->espera) > 0);
  }

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento ENTRA
int entra(struct mundo *w, struct evento_t *ev)
{
  int i;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];
}

//--------------------------------------- 

//----------------------------------------

//evento SAI
int sai(struct mundo *w, struct evento_t *ev)
{
  int i;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];
}

//--------------------------------------- 

//----------------------------------------

//evento VIAJA
int viaja(struct mundo *w, struct evento_t *ev)
{
  int i;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];
}

//--------------------------------------- 

//----------------------------------------

//evento MORRE
int morre(struct mundo *w, struct evento_t *ev)
{
  int i;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == w->herois[i]->ID)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado1)
      base = w->bases[i];
}

//--------------------------------------- 

//----------------------------------------

//evento MISSÃO
int missao(struct mundo *w, struct evento_t *ev)
{
  int i, tamanho, distancia, menor, risco;
  struct base BMP;
  menor = w->tamanho;

  for (i = 0; i < w->Nbases; i++)
  {
    //a trabalhar: conferir se a base tem as habilidades certas
    if cjto_inter
    {
      distancia = distancia_cartesiana(m.local, w->bases[i]);
      if (distancia < menor)
        menor = distancia;
        BMP = w->bases[i];
    }    
  }

  if (BMP)
  {
    m.cumprida = true;
    for (i = 0; i < N_HEROIS; i++)
    {
      if (cjto_pertence(BMP.presentes, i) == 1)
      {
        risco = m.perigo/(w.herois[i]->paciencia + w.herois[i]->experiencia + 1.0);
        if (risco > rand() % 30)
          proximo da lef = morre(agora, w.herois[i]);
        else 
          w.herois[i]->experiencia++;
      }
    }
  }
  else 
  {
   proximo da lef = missao(t + 24*60, m);
   m.tentativas++;
  }

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento FIM
void fim(struct mundo *w, struct evento_t *ev) 
{
  printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS ", );
  printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS ", );
  cjto_imprime(habilidades dos herois);
  printf("\n");
  printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", base, lotacao, maximodeheroisnaespera, missoes);
  printf("EVENTOS TRATADOS: %d\n", eventos);
  printf("MISSOES CUMRPIDAS: %d/%d (%.1f%%)\n", cumpridas, geradas, porcentagem);
  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tentativas, max_tentativas, media);
  printf("TAXA MORTALIDADE: %.1f%%", mortes porcentagem);*/ //div 1.0
}





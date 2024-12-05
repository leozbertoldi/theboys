#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"
#include "auxiliares.h"
#include "lista.h"
#include "fprio.h"

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
  ev->dado1 = 0;

  for (i = 0; i < N_HEROIS; i++)
  {
    base = aleat(0,N_BASES-1);
    tempo = aleat(0,4320);
    ev->tempo = tempo;
    ev->dado2 = base;

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
  ev->dado2 = 0;

  for (i = 0; i < N_MISSOES; i++)
  {
    tempo = aleat(0,T_FIM_DO_MUNDO-1);
    ev->tempo = tempo;
    ev->dado1 = i;
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
    if (i == ev->dado1)
      heroi = w->herois[i];

  heroi->ID_base = ev->dado2;
  
  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];

  vagas = (base->lotacao > cjto_card(base->presentes));
  espera_vazia = (lista_tamanho(base->espera) == 0);
  if (vagas && espera_vazia)
    espera = true;
  else
    espera = ((heroi->paciencia) > (10 * lista_tamanho(base->espera)));

  if (espera)
  {
    ev->tipo = EV_ESPERA;
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", w->clock, ev->dado1, ev->dado2, cjto_card(base->presentes), base->lotacao);
  }
  else 
  {
    ev->tipo = EV_DESISTE;
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", w->clock, ev->dado1, ev->dado2, cjto_card(base->presentes), base->lotacao);
  }

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
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];

  printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", w->clock, heroi->ID, base->ID, lista_tamanho(base->espera));
  
  lista_insere(base->espera, heroi->ID, -1);

  if (lista_tamanho(base->espera) > base->max_espera)
    base->max_espera = lista_tamanho(base->espera);

  ev->tipo = EV_AVISA;
  ev->tempo = w->clock;
  ev->dado1 = 0;
  ev->dado2 = base->ID;
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
    if (i == ev->dado1)
      heroi = w->herois[i];

  D = aleat(0,N_BASES-1);

  printf("%6d: DESISTE HEROI %2d BASE %d\n", w->clock, heroi->ID, base->ID);

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
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];

  printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA ", w->clock, base->ID, cjto_card(base->presentes), base->lotacao);
  lista_imprime(base->espera);
  printf("\n");
 
  vagas = (base->lotacao >= cjto_card(base->presentes));
  espera = (lista_tamanho(base->espera) > 0);
  while (vagas && espera)
  {
    lista_retira(base->espera, heroi->ID, 0);
    printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", w->clock, base->ID, heroi->ID);
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
  int i, TPB;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];

  TPB = 15 + heroi->paciencia * aleat(1,20);

  ev->tipo = EV_SAI;
  ev->tempo = w->clock + TPB;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", w->clock, heroi->ID, base->ID, cjto_card(base->presentes), base->lotacao, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento SAI
int sai(struct mundo *w, struct evento_t *ev)
{
  int i, D;
  struct evento_t *ev, *ev2;
  struct base *base;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];
  
  cjto_retira(base->presentes, heroi);
  D = aleat(0,N_BASES-1);

  printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", w->clock, heroi->ID, base->ID, cjto_card(base->presentes), base->lotacao);
  
  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  ev->tipo = EV_VIAJA;
  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = D;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  ev2 = malloc(sizeof(struct evento_t));
  if (!ev2)
    return -1;

  ev2->tipo = EV_AVISA;
  ev2->tempo = w->clock;
  ev2->dado1 = 0;
  ev2->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento VIAJA
int viaja(struct mundo *w, struct evento_t *ev)
{
  int i, distancia, duracao;
  struct evento_t *ev;
  struct base *base, *base_atual;
  struct heroi *heroi;

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  for (i = 0; i < N_HEROIS; i++)
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_HEROIS; i++)
    if (heroi->ID_base == i)
      base_atual = w->bases[i];  

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];
  
  distancia = distancia_cartesiana(base->local, base_atual->local);
  duracao = distancia/heroi->velocidade;

  printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", w->clock, heroi->ID, base_atual->ID, base->ID, distancia, heroi->velocidade, w->clock + duracao);

  ev->tipo = EV_CHEGA;
  ev->tempo = w->clock + duracao;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
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
    if (i == ev->dado1)
      heroi = w->herois[i];

  for (i = 0; i < N_BASES; i++)
    if (i == ev->dado2)
      base = w->bases[i];

  cjto_retira(base->presentes, heroi->ID);
  heroi->vivo = false;
  heroi->ID_base = -1;

  printf("%6d: MORRE HEROI %2d MISSAO %d\n", w->clock, heroi->ID, missao->ID);

  ev->tipo = EV_AVISA;
  ev->tempo = w->clock;
  ev->dado1 = 0;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento MISSÃO
int missao(struct mundo *w, struct evento_t *ev)
{
  int i, j, BMP_ID, risco;
  struct evento_t *ev, *ev2;
  struct missao *missao;
  struct base *BMP;
  struct cjto_t uniao;
  int distancia_bases[N_BASES];

  if (!w || !ev)
    return -1;

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;
  
  for (i = 0; i < N_MISSOES; i++)
    if (ev->dado1 == i)
      missao = w->missoes[i];

  printf("%6d: MISSAO %d TENT %d HAB REQ: ", w->clock, missao->ID, missao->tentativas);
  cjto_imprime(missao->habilidades);
  printf("\n");

  for (i = 0; i < N_BASES; i++)
  {
    for (j = 0; j < N_HEROIS; j++) 
      if (cjto_pertence(w->bases[i]->presentes, w->herois[j]->ID)) //acha se o heroi esta na base
      {
        uniao = cjto_uniao(uniao, w->herois[j]->habilidades);  //une as habilidades do heroi com resto

        printf("%6d: MISSAO %d HAB HEROI %2d: ", w->clock, missao->ID, w->herois[j]->ID);
        cjto_imprime(w->herois[j]->habilidades);
        printf("\n");
      }
  
    distancia_bases[i] = distancia_cartesiana(w->bases[i]->local, missao->local); //distancia entra no vetor

    printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ", w->clock, missao->ID, base->ID, distancia_bases[i]);
    cjto_imprime(w->bases[i]->presentes);
    printf("\n");

    if (!cjto_contem(uniao, missao->habilidades)) //se a uniao das habilidades não contem as da missao
    {
      distancia_bases[i] = -1;
      printf("%6d: MISSAO %d UNIAO HAB BASE %d: INSUFICIENTES", w->clock, missao->ID, w->bases[i]->ID);
    }
  }
  
  sort(distancia_bases);

  BMP_ID = -1;
  i = 0;
  while (BMD_ID == -1 && i != N_BASES) 
  {
    BMD_ID = distancia_bases[i];
    i++;
  }

  if (BMD_ID != -1)
  {
    missao->cumprida = true;

    for (i = 0; i < N_BASES; i++)
      if (i == BMD_ID)
        BMD = w->bases[i];

    BMD->missoes_participadas++;

    for (i = 0; i < N_HEROIS; i++)
    {
      if (cjto_pertence(BMP->presentes, w->herois[i]->ID))
      {
        risco = missao->perigo/(w->herois[i]->paciencia + w->herois[i]->experiencia + 1.0);
        if (risco > (aleat(0,30)))
        {
          ev2 = malloc(sizeof(struct evento_t));
          if (!ev)
            return -1; 

          ev2->tipo = EV_MORRE;
          ev2->tempo = w->clock;
          ev2->dado1 = w->herois[i]->ID;
          ev2->dado2 = BMP->ID;
          fprio_insere(w->lef, ev, ev->tipo, ev->tempo);
        }
        else
          w->herois[i]->experiencia++;
      } 

      printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", w->clock, missao->ID, base->ID);
      cjto_imprime(uniao);
      printf("\n");

    }
  }
  else 
  {
    printf("%6d: MISSAO %d IMPOSSIVEL\n", w->clock, missao->ID);

    missao->tentativas++;
    ev->tipo = EV_MISSAO;
    ev->tempo = w->clock + 24*60;
    ev->dado1 = missao->ID;
    ev->dado2 = 0;
    fprio_insere(w->lef, ev, ev->tipo, ev->tempo);
  }

  return 0;
}  

//--------------------------------------- 

//----------------------------------------

//evento FIM
void fim(struct mundo *w, struct evento_t *ev) 
{
  int i, j, missoes_cumpridas, min, max, media, total, vivos, mortos;
  struct heroi *h;
  struct base *b;

  missoes_cumpridas = 0;
  min = 0;
  max = 0;
  total = 0;
  media = 0;
  vivos = 0;
  mortos = 0;

  for (i = 0; i < N_HEROIS; i++)
  {
    h = w->herois[i];
    if (h->vivo)
    {
      printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS ", h->ID, h->paciencia, h->velocidade, h->EXP);
      cjto_imprime(h->habilidades);
      printf("\n");
    }
    else 
    {
      printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS ", h->ID, h->paciencia, h->velocidade, h->EXP);
      cjto_imprime(h->habilidades);
      printf("\n");
    }
  }

  for (i = 0; i < N_BASES; i++)
  {
    b = w->bases[i];
    printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", b->ID, b->lotacao, b->max_espera, b->missoes_participadas);
  }
  
  printf("EVENTOS TRATADOS: %d\n", w->eventos_tratados);

  for (i = 0; i < N_MISSOES; i++)
  {
    if (w->missoes[i]->cumprida)
      missoes_cumpridas++;
  }
  printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", missoes_cumpridas, N_MISSOES, missoes_cumpridas/N_MISSOES*100);

  for (i = 0; i < N_MISSOES; i++)
  {
    if (w->missoes[i]->tentativas < min)
      min = w->missoes[i]->tentativas;
    if (w->missoes[i]->tentativas > max)
      max = w->missoes[i]->tentativas;

    total = total + w->missoes[i]->tentativas;
  }
  media = total/N_BASES;
  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min, max, media);

  for (i = 0; i < N_HEROIS; i++)
  {
    if (w->herois[i]->vivo)
      vivos++;
    else
      mortos++;
  }
  printf("TAXA MORTALIDADE: %.1f%%", vivos/mortos*100);*/ //div 1.0
}





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"
#include "auxiliares.h"

//EVENTOS INICIAIS
//=======================================================================================
void base_aleatoria(struct mundo *w)
{
  int i, j, base, tempo;
  j = 0;

  for (i = 0; i < N_HEROIS; i++)
  {
    base = aleat(0,N_BASES-1);
    tempo = aleat(0,4320);
    proximo lef = chega(tempo, w->herois[i], w->bases[base]);
  }
//dica maziero para insrir evento
    struct evento_t *ev;
    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return erro;
    ev->tipo: CHEGA;
    ev->tempo: aleat(0,60*24*3);
    ev->dado1 = x;
    ev->dado2 = aleat;

    fprio_insere(lef, ev, ev->tipo, ev->tempo)

  return;
}

void agenda_missao(struct mundo *w)
{
  int i, tempo;

  for (i = 0; i < N_MISSOES; i++)
  {
    tempo = aleat(0,T_FIM_DO_MUNDO-1);
    proximo lef = missao(tempo, w.missoes[i]);
  }


  return;
}
//=======================================================================================


//evento CHEGA
void chega(struct mundo *w, struct evento_t *ev)
{
  bool espera;

  if (!h || !b)
    return -1;

  h.base_heroi = b;

  // confere se o número de presentes é maior q a capacidade
  if (b.lotacao < cjto_card(b.presentes))
    espera = ( h.paciencia > 10*fprio_tamanho(b.espera) );
  else 
    espera = true;

  if (espera)
    proximo da lef = evento espera
  else
    proximo da lef = evento desiste

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento ESPERA
void espera(struct mundo *w, struct evento_t *ev)
{
  
  lista_insere(b.espera, h, -1);

  proximo da lef = evento avisa

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento DESISTE
void desiste(struct mundo *w, struct evento_t *ev)
{
  int D;

  D = aleat(0,N_BASES-1);

  proximo da lef = evento viaja(agora, h, D);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento AVISA
void avisa(struct mundo *w, struct evento_t *ev)
{
  struct heroi aux;

  while ( (cjto_card(b.presentes) < b.lotacao) && (lista_tamanho(b.espera) > 0) )
  {
    aux = b.espera->prim;
    lista_retira(b.presentes, aux->valor, 0);
    cjto_insere(b.presentes, aux->valor);
    proximo da lef = evento entra(agora, aux, b);
  }

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento ENTRA
void entra(struct mundo *w, struct evento_t *ev)
{
  int TPB;

  TPB = 15 + h.paciencia * aleat(0,20);

  proximo da lef = evento sai(agora + TPB, h, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento SAI
void sai(struct mundo *w, struct evento_t *ev)
{
  int D;
  
  lista_retira(b.presentes, h, lista_consulta(h));

  D = aleat(0,N_BASES-1);

  proximo da lef = viaja(agora, h, D);
  proximo da lef = avisa(agora, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento VIAJA
void viaja(struct mundo *w, struct evento_t *ev)
{
  float distancia;

  distancia = distancia_cartesiana(h.base_heroi->local, d.local);
  duracao = distancia / h.velocidade;

  proximo da lef = chega(agora + duracao, h, d);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento MORRE
void morre(struct mundo *w, struct evento_t *ev)
{
  cjto_retira(h, h.ID);
  h.vivo = false;

  proximo da lef = avisa(agora, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento MISSÃO
void missao(struct mundo *w, struct evento_t *ev)
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





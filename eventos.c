#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"
#include "auxiliares.h"
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

//EVENTOS INICIAIS
//=======================================================================================

// escolhe base e tempo de chegada aleatório para cada herói
int base_aleatoria(struct mundo *w)
{
  int i, base, tempo;
  struct evento_t *ev;

  for (i = 0; i < N_HEROIS; i++)
  {
    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;

    ev->tipo = EV_CHEGA;
    base = aleat(0,N_BASES-1);
    tempo = aleat(0,4320);
    ev->tempo = tempo;
    ev->dado1 = i;
    ev->dado2 = base;
    fprio_insere(w->lef, ev, EV_CHEGA, tempo);
  }

  return 0;
}


// agenda as missões durante a simulação
int agenda_missao(struct mundo *w)
{
  int i, tempo;
  struct evento_t *ev;

  for (i = 0; i < N_MISSOES; i++)
  {
    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;

    ev->tipo = EV_MISSAO;
    ev->dado2 = 0;
    tempo = aleat(0,T_FIM_DO_MUNDO-1);
    ev->tempo = tempo;
    ev->dado1 = i;
    fprio_insere(w->lef, ev, EV_MISSAO, tempo); 
  }

  return 0;
}
//=======================================================================================


//evento CHEGA
int chega(struct mundo *w, struct evento_t *evento)
{
  bool espera, vagas, espera_vazia;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  base = w->bases[evento->dado2];

  heroi->ID_base = evento->dado2;

  //analisa as vagas da base e a lista de espera
  vagas = (base->lotacao > cjto_card(base->presentes));
  espera_vazia = (lista_tamanho(base->espera) == 0);
  if (vagas && espera_vazia)
    espera = true;
  else
    espera = ((heroi->paciencia) > (10 * lista_tamanho(base->espera)));

  if (espera)
  {
    ev->tipo = EV_ESPERA;
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", w->clock, evento->dado1, evento->dado2, cjto_card(base->presentes), base->lotacao);
  }
  else 
  {
    ev->tipo = EV_DESISTE;
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", w->clock, evento->dado1, evento->dado2, cjto_card(base->presentes), base->lotacao);
  }

  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento ESPERA
int espera(struct mundo *w, struct evento_t *evento)
{
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  base = w->bases[evento->dado2];

  printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", w->clock, heroi->ID, base->ID, lista_tamanho(base->espera));
  
  //insere heroi na lista de espera
  lista_insere(base->espera, heroi->ID, -1);


  //para calcular num max de herois na lista de espera
  if (lista_tamanho(base->espera) > base->max_espera)
    base->max_espera = lista_tamanho(base->espera);

  ev->tipo = EV_AVISA;
  ev->tempo = w->clock;
  ev->dado1 = 0;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento DESISTE
int desiste(struct mundo *w, struct evento_t *evento)
{
  int D;
  struct evento_t *ev;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  D = aleat(0,N_BASES-1);

  printf("%6d: DESISTE HEROI %2d BASE %d\n", w->clock, heroi->ID, evento->dado2);

  ev->tipo = EV_VIAJA;
  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = D;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento AVISA
int avisa(struct mundo *w, struct evento_t *evento)
{
  bool vagas, espera;
  struct evento_t *ev;
  struct base *base;
  struct heroi heroi;

  if (!w || !evento)
    return -1;

  base = w->bases[evento->dado2];

  printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", w->clock, base->ID, cjto_card(base->presentes), base->lotacao);
  lista_imprime(base->espera);
  printf(" ]\n");
 
  //analisa vagas da base e lista de espera
  vagas = (base->lotacao > cjto_card(base->presentes));
  espera = (lista_tamanho(base->espera) > 0);
  //enquanto existir vaga na base e existir heroi na espera
  while (vagas && espera)
  {
    lista_retira(base->espera, &heroi.ID, 0);
    printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", w->clock, base->ID, heroi.ID);
    cjto_insere(base->presentes, heroi.ID);

    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;

    ev->tipo = EV_ENTRA;
    ev->tempo = w->clock;
    ev->dado1 = heroi.ID;
    ev->dado2 = base->ID;
    fprio_insere(w->lef, ev, ev->tipo, ev->tempo);
 
    //atualiza o booleano de vagas e lista de espera com os novos valores adicionados/retirados
    vagas = (base->lotacao > cjto_card(base->presentes));
    espera = (lista_tamanho(base->espera) > 0);
  }

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento ENTRA
int entra(struct mundo *w, struct evento_t *evento)
{
  int TPB;
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  base = w->bases[evento->dado2];

  //TPB = tempo de permanência na base
  TPB = 15 + heroi->paciencia * aleat(1,20);

  ev->tipo = EV_SAI;
  ev->tempo = w->clock + TPB;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", w->clock, heroi->ID, base->ID, cjto_card(base->presentes), base->lotacao, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento SAI
int sai(struct mundo *w, struct evento_t *evento)
{
  int D;
  struct evento_t *ev, *ev2;
  struct base *base;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;
  
  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  heroi = w->herois[evento->dado1];

  base = w->bases[evento->dado2];
  
  //retira heroi dos presentes da base
  cjto_retira(base->presentes, heroi->ID);
  D = aleat(0,N_BASES-1);

  printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", w->clock, heroi->ID, base->ID, cjto_card(base->presentes), base->lotacao);
  
  //agenda o evento viagem do herói
  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  ev->tipo = EV_VIAJA;
  ev->tempo = w->clock;
  ev->dado1 = heroi->ID;
  ev->dado2 = D;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  //agenda o evento avisa ao porteiro
  ev2 = malloc(sizeof(struct evento_t));
  if (!ev2)
    return -1;

  ev2->tipo = EV_AVISA;
  ev2->tempo = w->clock;
  ev2->dado1 = 0;
  ev2->dado2 = base->ID;
  fprio_insere(w->lef, ev2, ev2->tipo, ev2->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento VIAJA
int viaja(struct mundo *w, struct evento_t *evento)
{
  int distancia, duracao;
  struct evento_t *ev;
  struct base *base, *base_atual;
  struct heroi *heroi;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  base = w->bases[evento->dado2];

  base_atual = w->bases[heroi->ID_base];  
  
  //calcula distancia entre base destino e base atual
  distancia = distancia_cartesiana(base->local, base_atual->local);
  duracao = distancia/heroi->velocidade;

  printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", w->clock, heroi->ID, base_atual->ID, base->ID, distancia, heroi->velocidade, w->clock + duracao);

  ev->tipo = EV_CHEGA;
  ev->tempo = w->clock + duracao;
  ev->dado1 = heroi->ID;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento MORRE
int morre(struct mundo *w, struct evento_t *evento)
{
  struct evento_t *ev;
  struct base *base;
  struct heroi *heroi;
  struct missao *missao;

  if (!w || !evento)
    return -1;

  if (!w->herois[evento->dado1]->vivo)
  {
    free(evento);
    return 0;
  }

  ev = malloc(sizeof(struct evento_t));
  if (!ev)
    return -1;

  heroi = w->herois[evento->dado1];

  base = w->bases[heroi->ID_base];

  missao = w->missoes[evento->dado2];

  //retira heroi da base presente
  cjto_retira(base->presentes, heroi->ID);
  heroi->vivo = false;
  heroi->ID_base = -1;

  printf("%6d: MORRE HEROI %2d MISSAO %d\n", w->clock, heroi->ID, missao->ID);

  ev->tipo = EV_AVISA;
  ev->tempo = w->clock;
  ev->dado1 = 0;
  ev->dado2 = base->ID;
  fprio_insere(w->lef, ev, ev->tipo, ev->tempo);

  free(evento);

  return 0;
}

//--------------------------------------- 

//----------------------------------------

//evento MISSÃO
int missao(struct mundo *w, struct evento_t *evento)
{
  int i, j, BMP_ID, risco;
  struct evento_t *ev, *ev2;
  struct missao *missao;
  struct base *BMP;
  struct cjto_t *uniao, *aux;
  int distancia_bases[N_BASES], indices_bases[N_BASES];
  bool impossivel;

  if (!w || !evento)
    return -1;
  
  missao = w->missoes[evento->dado1];

  printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", w->clock, missao->ID, missao->tentativas);
  cjto_imprime(missao->habilidades);
  printf(" ]\n");

  //organiza dois vetore, um para as distancias de cada base ao local da missão
  //e uma com os índices das bases que serão ordenados paralelamente às distancias 
  for (i = 0; i < N_BASES; i++)
  {
    distancia_bases[i] = distancia_cartesiana(missao->local, w->bases[i]->local);
    indices_bases[i] = i;

    printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", w->clock, missao->ID, w->bases[i]->ID, distancia_bases[i]);
    cjto_imprime(w->bases[i]->presentes);
    printf(" ]\n");
  }

  heap_sort(distancia_bases, indices_bases, N_BASES);

  //analisa todas as bases em ordem crescente de distancia 
  impossivel = true;
  j = 0;
  while (impossivel && j < N_BASES)
  {
    BMP_ID = indices_bases[j];
    uniao = cjto_cria(N_HABILIDADES);

    //analisa quais herois estao presentes na base
    for (i = 0; i < N_HEROIS; i++)
    {
      if (cjto_pertence(w->bases[BMP_ID]->presentes, i))
      {
        printf("%6d: MISSAO %d HAB HEROI %2d: [ ", w->clock, missao->ID, w->herois[i]->ID);
        cjto_imprime(w->herois[i]->habilidades);
        printf(" ]\n");

        //une as habilidades do heroi com todos da base
        aux = cjto_uniao(uniao, w->herois[i]->habilidades);
        cjto_destroi(uniao);
        uniao = aux;
      }
    }

    printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", w->clock, missao->ID, w->bases[j]->ID);
    cjto_imprime(uniao);
    printf(" ]\n");

    //se as habilidades dos herois presentes suprem as necessidades da missao
    if (cjto_contem(uniao, missao->habilidades))
    {
      BMP = w->bases[BMP_ID];
      missao->cumprida = true;

      //para todo herói pertencente à base
      for (i = 0; i < N_HEROIS; i++)
      {
        if (cjto_pertence(BMP->presentes, i))
        {
          risco = missao->perigo/(w->herois[i]->paciencia+w->herois[i]->experiencia+1.0);
          if (risco > aleat(0,30))
          {
            ev2 = malloc(sizeof(struct evento_t));
            if (!ev2)
              return -1; 

            ev2->tipo = EV_MORRE;
            ev2->tempo = w->clock;
            ev2->dado1 = w->herois[i]->ID;
            ev2->dado2 = missao->ID;
            fprio_insere(w->lef, ev2, ev2->tipo, ev2->tempo);
          }
          else
            w->herois[i]->experiencia++;
        }
      }
      impossivel = false;

      BMP->missoes_participadas++;

      printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", w->clock, missao->ID, BMP->ID);
      cjto_imprime(uniao);
      printf(" ]\n");
    }
    //faz as alterações necessárias para o caso de a próxima base do vetor precisar ser analisada
    cjto_destroi(uniao);
    j++;
  }

  //se a missão não pôde ser cumprida
  if (impossivel)
  {
    printf("%6d: MISSAO %d IMPOSSIVEL\n", w->clock, missao->ID);

    ev = malloc(sizeof(struct evento_t));
    if (!ev)
      return -1;

    missao->tentativas++;
    ev->tipo = EV_MISSAO;
    ev->tempo = w->clock + 24*60;
    ev->dado1 = missao->ID;
    ev->dado2 = 0;
    fprio_insere(w->lef, ev, ev->tipo, ev->tempo);
  }

  free(evento);

  return 0;
}  

//--------------------------------------- 

//----------------------------------------

//evento FIM
void fim(struct mundo *w, struct evento_t *evento) 
{
  int i, min, max, total, missoes_cumpridas;
  float media, mortos;
  struct heroi *h;
  struct base *b;

  missoes_cumpridas = 0;
  min = 1;
  max = 1;
  total = 0;
  media = 0;
  mortos = 0;

  //relatório heróis + vivo ou morto
  for (i = 0; i < N_HEROIS; i++)
  {
    h = w->herois[i];
    if (h->vivo)
    {
      printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ ", h->ID, h->paciencia, h->velocidade, h->experiencia);
      cjto_imprime(h->habilidades);
      printf(" ]\n");
    }
    else 
    {
      printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ", h->ID, h->paciencia, h->velocidade, h->experiencia);
      cjto_imprime(h->habilidades);
      printf(" ]\n");
    }
  }

  //relatório bases
  for (i = 0; i < N_BASES; i++)
  {
    b = w->bases[i];
    printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", b->ID, b->lotacao, b->max_espera, b->missoes_participadas);
  }
  
  //eventos tratados
  printf("EVENTOS TRATADOS: %d\n", w->eventos_tratados);

  //relatório missões
  for (i = 0; i < N_MISSOES; i++)
  {
    if (w->missoes[i]->cumprida)
      missoes_cumpridas++;
  }                                                                             
  printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", missoes_cumpridas, N_MISSOES, (float)missoes_cumpridas/N_MISSOES*100);

  for (i = 0; i < N_MISSOES; i++)
  {
    if (w->missoes[i]->tentativas < min)
      min = w->missoes[i]->tentativas;
    if (w->missoes[i]->tentativas > max)
      max = w->missoes[i]->tentativas;

    total = total + w->missoes[i]->tentativas;
  }
  media = total/N_MISSOES;
  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min, max, media);

  for (i = 0; i < N_HEROIS; i++)
    if (!w->herois[i]->vivo)
      mortos++;
  
  printf("TAXA MORTALIDADE: %.1f%%\n", mortos/N_HEROIS*100);

  free(evento);
}





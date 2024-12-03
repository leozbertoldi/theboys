#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "eventos.h"

//evento CHEGA
void chega(int t, struct heroi h, struct base b)
{
  bool espera;

  if (!h || !b)
    return -1;

  h.base_heroi= b;

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
void espera(int t, struct heroi h, struct base b)
{
  
  lista_insere(b.espera, h, -1);

  proximo da lef = evento avisa

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento DESISTE
void desiste(int t, struct heroi h, struct base b)
{
  int D;

  D = rand() % 10;

  proximo da lef = evento viaja(agora, h, D);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento AVISA
void avisa(int t, struct base b)
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
void entra(int t, struct heroi h, struct base b)
{
  int TPB;

  TPB = 15 + h.paciencia * (rand() % 20);

  proximo da lef = evento sai(agora + TPB, h, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento SAI
void sai(int t, struct heroi h, struct base b)
{
  int D;
  
  lista_retira(b.presentes, h, lista_consulta(h));

  D = rand() % 10;

  proximo da lef = viaja(agora, h, D);
  proximo da lef = avisa(agora, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento VIAJA
void viaja(int t, struct heroi h, struct base d)
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
void morre(int t, struct heroi h, struct base b)
{
  cjto_retira(h, h.ID);
  h.vivo = false;

  proximo da lef = avisa(agora, b);

  return;
}

//--------------------------------------- 

//----------------------------------------

//evento MISSÃO
void missao(int t, struct missao m, struct mundo w)
{
  int i, tamanho;
  int distancias[w.Nbases];

  for (i = 0; i < w.Nbases; i++)
  {
    //a trabalhar: conferir se a base tem as habilidades certas
    if cjto_inter
      distancias[i] = distancia_cartesiana(m.local, w.bases[i]);
      tamanho++;
  }
  
  heap_sort(distancias, tamanho);
    
}

//--------------------------------------- 

//----------------------------------------

//evento FIM
void fim(int t)
{
}





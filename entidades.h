#ifndef ENTIDADES
#define ENTIDADES

struct local
{
  int x;
  int y;
};

struct heroi
{
  int ID;
  struct cjnt_t *habilidades;
  int paciencia;
  int velocidade;
  int experiencia;
  struct base *base_heroi;
};

struct base
{
  int ID;
  int lotacao;
  struct cjnt_t *presentes;
  struct lista_t *espera;
  struct local *local;  
};

struct missao
{
  int ID;
  struct cjnt_t *habilidades;
  int perigo;
  struct local *local;
};

struct mundo
{
  int nherois;
  struct heroi herois[];
  int nbases;
  struct base bases[];
  int nmissoes;
  struct missao missoes[];
  int nhabilidades;
  int tamanho;
  int relogio;
};

#endif
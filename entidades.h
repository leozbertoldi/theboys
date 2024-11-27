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
  struct base;
};

struct base
{
  int ID;
  int lotacao;
  struct cjnt_t *presentes;
  struct fprio_t *espera;
  struct local;  
};

struct missao
{
  int ID;
  struct cjnt_t *habilidades;
  int perigo;
  struct local;
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
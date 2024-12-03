#ifndef ENTIDADES
#define ENTIDADES

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES*5)
#define N_BASES  (N_HEROIS/5)
#define N_MISSOES  (T_FIM_DO_MUNDO/100)

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
  bool vivo;
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
  bool cumprida;
};

struct mundo
{
  int Nherois;
  struct heroi herois[];
  int Nbases;
  struct base bases[];
  int Nmissoes;
  struct missao missoes[];
  int Nhabilidades;
  int tamanho;
  int relogio;
};

struct mundo *inicializa_mundo(struct mundo *m);

struct heroi *inicializa_heroi(struct heroi *h, int i);

struct base *inicializa_base(struct base *b, int i);  


#endif
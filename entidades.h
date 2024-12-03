#ifndef ENTIDADES
#define ENTIDADES

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES*5)
#define N_BASES  (N_HEROIS/5)
#define N_MISSOES  (T_FIM_DO_MUNDO/100)

#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MORRE 8
#define EV_MISSAO 9
#define EV_FIM 10

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
  int tentativas;
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
  struct local tamanho;
  int relogio;
  struct fprio_t *lef;
};

struct evento_t
{
  int tipo;
  int tempo;
  int dado1;
  int dado2;
};

struct mundo *inicializa_mundo(struct mundo *m);

struct heroi *inicializa_heroi(struct heroi *h, int i);

struct base *inicializa_base(struct base *b, int i);  

struct missao *inicializa_missao(struct missao *m, int i);

#endif
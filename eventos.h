#ifndef EVENTOS
#define EVENTOS

#include "entidades.h"

int base_aleatoria(struct mundo *w);

int agenda_missao(struct mundo *w);

//evento CHEGA
int chega(struct mundo *w, struct evento_t *evento);

//evento ESPERA
int espera(struct mundo *w, struct evento_t *evento);

//evento DESISTE
int desiste(struct mundo *w, struct evento_t *evento);

//evento AVISA
int avisa(struct mundo *w, struct evento_t *evento);

//evento ENTRA
int entra(struct mundo *w, struct evento_t *evento);

//evento SAI
int sai(struct mundo *w, struct evento_t *evento);

//evento VIAJA
int viaja(struct mundo *w, struct evento_t *evento);

//evento MORRE
int morre(struct mundo *w, struct evento_t *evento);

//evento MISSÃO
int missao(struct mundo *w, struct evento_t *evento);

//evento FIM
void fim(struct mundo *w);

#endif
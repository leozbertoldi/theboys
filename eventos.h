#ifndef EVENTOS
#define EVENTOS

int base_aleatoria(struct mundo *w);

int agenda_missao(struct mundo *w);

//evento CHEGA
int chega(struct mundo *w, struct evento_t *ev);

//evento ESPERA
int espera(struct mundo *w, struct evento_t *ev);

//evento DESISTE
int desiste(struct mundo *w, struct evento_t *ev);

//evento AVISA
int avisa(struct mundo *w, struct evento_t *ev);

//evento ENTRA
int entra(struct mundo *w, struct evento_t *ev);

//evento SAI
int sai(struct mundo *w, struct evento_t *ev);

//evento VIAJA
int viaja(struct mundo *w, struct evento_t *ev);

//evento MORRE
int morre(struct mundo *w, struct evento_t *ev);

//evento MISSÃO
int missao(struct mundo *w, struct evento_t *ev);

//evento FIM
void fim(struct mundo *w, struct evento_t *ev);

#endif
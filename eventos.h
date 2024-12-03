#ifndef EVENTOS
#define EVENTOS

//evento CHEGA
void chega(struct mundo *w, struct evento_t *ev);

//evento ESPERA
void espera(struct mundo *w, struct evento_t *ev);

//evento DESISTE
void desiste(struct mundo *w, struct evento_t *ev);

//evento AVISA
void avisa(struct mundo *w, struct evento_t *ev);

//evento ENTRA
void entra(struct mundo *w, struct evento_t *ev);

//evento SAI
void sai(struct mundo *w, struct evento_t *ev);

//evento VIAJA
void viaja(struct mundo *w, struct evento_t *ev);

//evento MORRE
void morre(struct mundo *w, struct evento_t *ev);

//evento MISSÃO
void missao(struct mundo *w, struct evento_t *ev);

//evento FIM
void fim(struct mundo *w, struct evento_t *ev);

#endif
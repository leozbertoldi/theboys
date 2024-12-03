#ifndef EVENTOS
#define EVENTOS

//evento CHEGA
void chega(int t, struct heroi h, struct base b);

//evento ESPERA
void espera(int t, struct heroi h, struct base b);

//evento DESISTE
void desiste(int t, struct heroi h, struct base b);

//evento AVISA
void avisa(int t, struct base b);

//evento ENTRA
void entra(int t, struct heroi h, struct base b);

//evento SAI
void sai(int t, struct heroi h, struct base b);

//evento VIAJA
void viaja(int t, struct heroi h, struct base b);

//evento MORRE
void morre(int t, struct heroi h, struct base b);

//evento MISSÃO
void missao(int t, struct missao m, struct mundo w);

//evento FIM
void fim(int t);

#endif
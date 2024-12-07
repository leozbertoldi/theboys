#ifndef AUXILIARES
#define AUXILIARES

#include "entidades.h"

float distancia_cartesiana(struct local *a, struct local *b);

long aleat (long min, long max);

void troca(int *a, int *b);

void build_heap(int v[], int a[], int n, int i);

void heap_sort(int v[], int a[], int n);

#endif

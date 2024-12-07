#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "entidades.h"
#include "auxiliares.h"

float distancia_cartesiana(struct local *a, struct local *b)
{
  int prim, seg;

  if (!a || !b)
    return -1;

  prim = a->x - b->x;
  seg = a->y - b->y;

  return sqrt(prim*prim + seg*seg);
}

long aleat(long min, long max)
{
  return ((rand() % (max - min + 1)) + min);
}

void troca(int *a, int *b) 
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void build_heap(int v[], int a[], int n, int i) 
{
  int max = i; 
  int esquerda = 2 * i + 1; 
  int direita = 2 * i + 2; 

  if (esquerda < n && v[esquerda] > v[max])
    max = esquerda;

  if (direita < n && v[direita] > v[max])
    max = direita;

  if (max != i) 
  {
    troca(&v[i], &v[max]);
    troca(&a[i], &a[max]);
    build_heap(v, a, n, max);
  }
}

void heap_sort(int v[], int a[], int n) 
{
  int i;

  for (i = n / 2 - 1; i >= 0; i--)
    build_heap(v, a, n, i);

  for (int i = n - 1; i >= 0; i--)
  {
    troca(&v[0], &v[i]);
    troca(&a[0], &a[i]);

    build_heap(v, a, i, 0);
  }
}

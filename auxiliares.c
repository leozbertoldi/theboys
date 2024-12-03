#include <stdbool.h>
#include <math.h>

float distancia_cartesiana(struct local a, struct local b)
{
  int prim, seg;

  prim = a->x - b->x;
  seg = a->y - b->y;

  return sqrt(prim*prim + seg*seg);
}

int heap_sort(int v[], int tam)
{
  if (!v || tam <= 0)
    return -1;

  n = build_max_heapify(v, tam);
  for (int i = n; n > 0; i--)
  { 
    troca(&v[i], &v[1]);
    n = n - 1;
    heapify(v[], 1);
  }

  return 1;
}

int build_max_heapify(int v[], int tam)
{
  n = tam;
  for (i = floor(n/2); i > 0; i--)
    heapify(v, i, n);

  return n;
}

void heapify(int v[], int i, int n)
{
  int direita, esquerda, max;

  esquerda = 2*i;
  direita = 2*i + 1;

  if (esquerda <= n && v[esquerda] > v[i])
    max = esquerda;
  else 
    max = direita;

  if (direita <= n && v[direita] > v[max])
    max = direita;

  if (max != i)
  {
    troca(&v[max], &v[i]);
    heapify(v, max);
  }

  return 0;
}

void troca(int *a, int *b)
{
    int aux = a;
    a = b;
    b = aux;

    return;
}
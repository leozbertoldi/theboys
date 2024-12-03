#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

float distancia_cartesiana(struct local a, struct local b)
{
  int prim, seg;

  prim = a.x - b.x;
  seg = a.y - b.y;

  return sqrt(prim*prim + seg*seg);
}

long aleat (long min, long max)
{
  return ((rand() % (max - min + 1)) + min);
}

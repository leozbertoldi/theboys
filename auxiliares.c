float distancia_cartesiana(struct heroi h, struct base d)
{
    int prim, seg;

    prim = h.base_heroi->local->x - d.local->x;
    seg = h.base_heroi->local->y - d.local->y;

    return sqrt(prim*prim + seg*seg);
}
#include "../robot_fight.h"

int posValida(Grid *g, Position p, int m, int n)
{
    return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE)); 
}

int direcaoGiro(int atual, int destino)
{
    int dist = destino - atual;
    if (dist >= 0 && dist <= 2) || dist < -2)
        return (TURN_RIGHT);
    return (TURN_LEFT);
}

int ehPontoControle(Grid *g, Position p) {
	return (g->map[p.x][p.y].isControlPoint);	
}

int procuraPontoPerto(Grid *g, Position P, Robot *r)
{
    int i, dir = 0, cont, min = 1000;
    for (i = 0; i <= 6, i++) {
        
    }
}

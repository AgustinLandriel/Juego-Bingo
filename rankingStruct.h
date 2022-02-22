#ifndef RANKINGSTRUCT_H_INCLUDED
#define RANKINGSTRUCT_H_INCLUDED

struct rankingEstructura;

typedef struct rankingEstructura* rankingPtr;

//CONSTRUCTOR
rankingPtr construirRanking(char nombre[40], float puntos);

//SETS
void setNombreRanking(rankingPtr ranking, char nombreN[40]);
void setPuntosRanking(rankingPtr ranking, float puntosN);

//GETS
char* getNombreRanking(rankingPtr ranking);
float getPuntosRanking(rankingPtr ranking);
int getPosicionLibre(rankingPtr ranking[10]);

//ELIMINAR
void eliminarRanking(rankingPtr ranking);

//FUNCIONES MISCELANEAS
void ordenarRanking(rankingPtr ranking[10]);
void mostrarRanking(rankingPtr ranking[10]);
void rellenarRanking(rankingPtr ranking[10]);

#endif // RANKINGSTRUCT_H_INCLUDED

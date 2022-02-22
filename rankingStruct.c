#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "rankingStruct.h"

struct rankingEstructura
{

    char nombre[40];
    float puntos;


};

//CONSTRUIR
rankingPtr construirRanking(char nombre[40], float puntos)
{
    rankingPtr r = malloc(sizeof(struct rankingEstructura));
    setNombreRanking(r, nombre);
    setPuntosRanking(r, puntos);
    return r;

}



//GETS
char* getNombreRanking(rankingPtr ranking)
{
    return ranking->nombre;
}
float getPuntosRanking(rankingPtr ranking)
{
    return ranking->puntos;
}

//SETS
void setNombreRanking(rankingPtr ranking, char nombreN[40])
{

    strcpy(ranking->nombre, nombreN);
}
void setPuntosRanking(rankingPtr ranking, float puntosN)
{
    ranking->puntos = puntosN;
}

//DESTRUIR
void eliminarRanking(rankingPtr ranking){
    free(ranking);
}




/*
    FUNCIONES
            MISCELANEAS
*/


void rellenarRanking(rankingPtr ranking[10])
{

    for(int i =0; i<10; i++)
    {
        ranking[i] = construirRanking(" ", -1.0);

    }
}



void copiaStruct(rankingPtr destino, rankingPtr origen)
{

    destino->puntos = origen->puntos;
    strcpy(destino->nombre, origen->nombre);

}


void ordenarRanking(rankingPtr ranking[10])
{

    rankingPtr rankingLocalAux = malloc(sizeof(struct rankingEstructura));
    for(int i=0; i<10; i++)
    {
        for(int j = 0; j<10 -1; j++)
        {


            if(ranking[j]->puntos < ranking[j+1]->puntos)
            {

                copiaStruct(rankingLocalAux, ranking[j]);

                copiaStruct(ranking[j], ranking[j+1]);

                copiaStruct(ranking[j+1], rankingLocalAux);
            }

        }


    }
    free(rankingLocalAux);
}


void mostrarRanking(rankingPtr ranking[10])
{

    for(int i = 0 ; i<10; i++)
    {
        if(ranking[i] ->puntos != -1.00f)
        {


            printf("JUGADOR: %s\nPUNTOS: %.2f \n\n", getNombreRanking(ranking[i]), getPuntosRanking(ranking[i]));
        }

    }


}

int getPosicionLibre(rankingPtr ranking[10])
{
    for(int i = 0; i<10; i++)
    {
        if(ranking[i]->puntos < 0)
        {

            return i;
        }

    }

}

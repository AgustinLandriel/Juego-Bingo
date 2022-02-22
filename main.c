#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "jugadorStruct.h"
#include "procedimientos.h"
#include "rankingStruct.h"

#define FILAS 3
#define COLUMNAS 5


int main()
{
    srand(time(0));
    //VARIABLES
    int bolillero[90];
    jugadorPtr jugadores[2];
    rankingPtr topPosiciones[10];

    //JUEGO
    menuJuego(jugadores, bolillero, topPosiciones);
    system("pause");

    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "jugadorStruct.h"

struct jugadorEstructura
{

    char nombre[40];
    char apellido[40];
    char dni[40];
    int carton[3][3][5];
    float puntos;
    int sacoBingo;
    int sacoLinea;
    int sacoColumna;
    int cantidadDeCartones;

};


//CONSTRUCTOR
jugadorPtr construirPersona(char nombre[40], char apellido[40], char dni[40], int cantCartones)
{

    jugadorPtr j = malloc(sizeof(struct jugadorEstructura));
    setNombre(j, nombre);
    setApellido(j, apellido);
    setDni(j, dni);
    for (int p=0; p<3 ; p++)
    {
        for (int b=0; b<3; b++)
        {
            for (int k=0; k<5; k++)
            {
                setNumeroCarton(j, p,b,k, -1);
            }
        }
    }
    setSacoBingo(j, 0);
    setSacoLinea(j, 0);
    setSacoColumna(j, 0);
    setPuntos(j, 0.0f);
    setCantidadDeCartones(j, cantCartones);
    return j;
}

//SETS
void setNombre(jugadorPtr j, char nuevoNombre[40])
{
    strcpy(j->nombre, nuevoNombre);
}
void setApellido(jugadorPtr j, char nuevoApellido[40])
{
    strcpy(j->apellido, nuevoApellido);
}
void setDni(jugadorPtr j, char dni[40])
{
    strcpy(j->dni, dni);
}
void setNumeroCarton(jugadorPtr j, int numeroDeCarton, int fila, int columna, int nuevoNumero)
{
    j->carton[numeroDeCarton][fila][columna] = nuevoNumero;
}
void setSacoBingo(jugadorPtr j, int numero)
{
    j->sacoBingo = numero;
}
void setSacoLinea(jugadorPtr j, int numero)
{
    j->sacoLinea = numero;
}
void setSacoColumna(jugadorPtr j, int numero)
{
    j->sacoColumna = numero;
}
void setCantidadDeCartones(jugadorPtr j, int numero)
{
    j->cantidadDeCartones = numero;
}
void setPuntos(jugadorPtr j, float puntos)
{
    j->puntos = puntos;
}

//GETS
char* getNombre(jugadorPtr j)
{
    return j->nombre;
}
char* getApellido(jugadorPtr j)
{
    return j->apellido;
}
char* getDni(jugadorPtr j)
{
    return j->dni;
}
int getNumeroCarton(jugadorPtr j, int carton, int fila, int columna)
{
    return j->carton[carton][fila][columna];
}
int getSacoBingo(jugadorPtr j)
{
    return j->sacoBingo;
}
int getSacoLinea(jugadorPtr j)
{
    return j->sacoLinea;
}
int getSacoColumna(jugadorPtr j)
{
    return j->sacoColumna;
}
int getCantidadDeCartones(jugadorPtr j)
{
    return j->cantidadDeCartones;
}
float getPuntos(jugadorPtr j)
{
    return j->puntos;
}

//DESTRUCTOR
void eliminarJugador(jugadorPtr j)
{
    free(j);
}
/*
    FUNCIONES
            MISCELANEAS

*/
//MOSTRAR
void mostrarDatosJugador(jugadorPtr j)   //Muestro los datos
{

    printf("\nEl jugador es %s %s con numero de DNI %s, con %.2f \n\n\n",j->nombre, j->apellido, j->dni, j->puntos);

}

//RELLENADOR
void rellenar(jugadorPtr j)
{

    j = construirPersona("alb", "c", "dede", 2);

}

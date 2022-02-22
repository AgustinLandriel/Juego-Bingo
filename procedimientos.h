#ifndef PROCEDIMIENTOS_H_INCLUDED
#define PROCEDIMIENTOS_H_INCLUDED
#include "rankingStruct.h"


//MENU DE JUEGO
void menuJuego(jugadorPtr jugadores[2], int vBolillero[90], rankingPtr ranking[10]);

//---------- ETAPAS ----------
void preJuego(jugadorPtr j[2], int vBolillero[90]);
void juego(jugadorPtr jugador[], int vBolillero[90], rankingPtr ranking[10]);


//---------- DATOS DEL JUGADOR ----------
void pedirDatosJugador(jugadorPtr j[2]);

//---------- BOLILLERO ----------
void generacionBolilero(int v[90]);
void muestroBolilero(int v[90]);
void rellenarBolillero(int vBolillero[90], int numero);


//---------- NUMEROS REPETIDOS ----------
int BusquedaBinariaBolillas(int v[],int buscar);
int busquedaDeRepetidos(jugadorPtr jugador,int t, int buscar);
void buscarNumeroEnCartonYsetear(jugadorPtr jugador, int numeroABuscar);


//---------- CARTONES ----------
void armadoDeCartones(jugadorPtr j[2]);
void crearCartonAleatorio(jugadorPtr j, int cantidadCartones);
void cargarCartonPersonalizado(jugadorPtr jugador, int cantidadDeCartones);

void mostrarAvanceCarton(jugadorPtr jugador, int vBolillasSalidas[90], char cartonDeQuien[15]);
void mostrarCarton(jugadorPtr jugador);

void verificarLinea(jugadorPtr jugador, int bolillasYaSalidas[90]);
void verificaColumna(jugadorPtr jugador, int bolillasYaSalidas[90]);
void cantarBingo(jugadorPtr jugador);
void calcularPuntajeFinal(jugadorPtr j, int c);


//---------- ARCHIVOS ----------
void ganadorARanking(jugadorPtr j[2], rankingPtr ranking[10]);
void txtAStruct(rankingPtr ranking[10]);

#endif // PROCEDIMIENTOS_H_INCLUDED

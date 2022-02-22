#ifndef JUGADORSTRUCT_H_INCLUDED
#define JUGADORSTRUCT_H_INCLUDED



struct jugadorEstructura;

typedef struct jugadorEstructura* jugadorPtr;

//CONSTRUCTOR
jugadorPtr construirPersona(char nombre[40], char apellido[40], char dni[40], int cantCartones);

//SETS
void setNombre(jugadorPtr j, char nuevoNombre[40]);
void setApellido(jugadorPtr j, char nuevoApellido[40]);
void setDni(jugadorPtr j, char dni[40]);
void setNumeroCarton(jugadorPtr j, int numeroDeCarton, int fila, int columna, int nuevoNumero);
void setSacoBingo(jugadorPtr j, int numero);
void setSacoLinea(jugadorPtr j, int numero);
void setSacoColumna(jugadorPtr j, int numero);
void setCantidadDeCartones(jugadorPtr j, int numero);
void setPuntos(jugadorPtr j, float puntos);


//GETS
char* getNombre(jugadorPtr j);
char* getApellido(jugadorPtr j);
char* getDni(jugadorPtr j);
int getNumeroCarton(jugadorPtr j, int carton, int fila, int columna);
int getSacoBingo(jugadorPtr j);
int getSacoLinea(jugadorPtr j);
int getSacoColumna(jugadorPtr j);
int getCantidadDeCartones(jugadorPtr j);
float getPuntos(jugadorPtr j);

//DESTRUCTOR
void eliminarJugador(jugadorPtr j);

//MOSTRAR
void mostrarDatosJugador(jugadorPtr j);

//RELLENADOR
void rellenar(jugadorPtr j);
#endif // JUGADORSTRUCT_H_INCLUDED

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

//MENU
void menuJuego(jugadorPtr jugadores[2], int vBolillero[90], rankingPtr ranking[10])
{
    int yaJugo = 0;
    int opcion;
    rellenarBolillero(vBolillero, -1); // usado para asegurar que el usuario no arranque el juego sin haber llenado los datos
    rellenarRanking(ranking);
    do
    {
        printf("\n\n -------Bienvenidos al juego del Bingo-------\n");
        printf("\n 1 -----> Cargar datos del Jugador\n");
        printf("\n 2 -----> Empezar Juego\n");
        printf("\n 3 -----> Mostrar las puntuaciones de cada jugador\n");

        printf("\n Elige una opcion para continuar -----> ");
        scanf("%d",&opcion);

        while (opcion >3 || opcion<1)
        {
            printf("Error..Elige una opcion del menu porfavor..\n"); //Si no elige un numero del menu lo pide de nuevo.
            scanf("%d",&opcion);
        }

        switch(opcion)
        {
        case 1:
            system("cls");
            preJuego(jugadores, vBolillero);
            break;

        case 2: //Empezar Juego
            if(vBolillero[0] != -1)
            {
                juego(jugadores, vBolillero, ranking);
                yaJugo = 1;

            }
            else
            {
                system("cls");
                printf("\n\nRellene primero los datos del jugador\n\n");
                break;
            }

        case 3:
            if(yaJugo == 1 )
            {
                txtAStruct(ranking);
                ganadorARanking(jugadores, ranking);
                ordenarRanking(ranking);
                mostrarRanking(ranking);
                structATxt(ranking);

            }
            else
            {
                system("cls");
                txtAStruct(ranking);
                ordenarRanking(ranking);
                mostrarRanking(ranking);

            }
            break;
        }
    }
    while(1 != 2);


}



//ETAPAS
void preJuego(jugadorPtr j[2], int vBolillero[90])
{
    pedirDatosJugador(j);
    generacionBolilero(vBolillero);
    armadoDeCartones(j);


}
void juego(jugadorPtr jugador[], int vBolillero[90], rankingPtr ranking[10])
{
    //SISTEMA DE TURNOS
    int bolillasQueSalieronPc[90];
    int bolillasQueSalieronJ[90];
    int posicionEnJ, posicionEnPc;
    rellenarBolillero(bolillasQueSalieronJ, -1);
    rellenarBolillero(bolillasQueSalieronPc, -1);
    int cantCartones = getCantidadDeCartones(jugador[0]);
    int i, t = 90;
    system("cls");

    for(i = 0; i<t; i++)
    {
        printf("Turno: %d\n", i+1);
        printf("Salio el: %d \n", vBolillero[i]);

        posicionEnJ = busquedaDeRepetidos(jugador[0], cantCartones, vBolillero[i]);
        posicionEnPc = busquedaDeRepetidos(jugador[1], cantCartones, vBolillero[i]);

        if(posicionEnJ != -1)
        {
            bolillasQueSalieronJ[i] = posicionEnJ;
            buscarNumeroEnCartonYsetear(jugador[0], posicionEnJ);
        }
        if(posicionEnPc != -1)
        {
            bolillasQueSalieronPc[i] = posicionEnPc;
            buscarNumeroEnCartonYsetear(jugador[1], posicionEnPc);
        }

        cantarBingo(jugador[0]);
        cantarBingo(jugador[1]);

        if(getSacoColumna(jugador[0]) != 1 && getSacoColumna(jugador[1]) != 1)
        {
            verificaColumna(jugador[0], bolillasQueSalieronJ);
            verificaColumna(jugador[1], bolillasQueSalieronPc);
        }
        if(getSacoLinea(jugador[0]) != 1 && getSacoLinea(jugador[1]) != 1)
        {
            verificarLinea(jugador[0], bolillasQueSalieronJ);
            verificarLinea(jugador[1], bolillasQueSalieronPc);
        }
        if(getSacoBingo(jugador[0]) == 1 || getSacoBingo(jugador[1]) == 1)
        {
            break;
        }

        mostrarAvanceCarton(jugador[0], bolillasQueSalieronJ, "jugador");
        mostrarAvanceCarton(jugador[1], bolillasQueSalieronPc, "PC");

        system("pause");
        system("cls");
    }
    calcularPuntajeFinal(jugador[0], i);
    calcularPuntajeFinal(jugador[1], i);

    mostrarDatosJugador(jugador[0]);
    mostrarDatosJugador(jugador[1]);



}


//     ----------- DATOS DEL JUGADOR-------------

void pedirDatosJugador(jugadorPtr j[2])
{
    char nombre[40]=" ";
    char apellido[40]=" ";
    char dni[40]=" ";
    int cantCartones = -1;

    printf("\nNombre del jugador:\n");
    fflush(stdin);
    gets(nombre);


    printf("\nApellido del jugador:\n");
    fflush(stdin);
    gets(apellido);


    printf("\nDNI del jugador:\n");
    fflush(stdin);
    gets(dni);

    do
    {
        printf("\nCantidad de cartones con los que desea jugar:\n");
        scanf("%d", &cantCartones);
    }
    while(cantCartones < 1 || cantCartones >3);

    j[0] = construirPersona(nombre, apellido, dni, cantCartones);
    j[1] = construirPersona("PC", " ", " ", cantCartones);
}




// ---------------FUNCIONES DEL BOLILLERO-----------------

void rellenarBolillero(int vBolillero[90], int numero)
{
    for(int i=0; i<90; i++)
    {
        vBolillero[i] = numero;
    }
}


int BusquedaBinariaBolillas(int v[90],int buscar)  //BUSQUEDA DE REPETIDO DEL BOLILLERO
{

    int pos=-1;
    for (int i=0; i<90; i++)
    {
        if(v[i]==buscar)
        {
            pos=v[i];
        }
    }
    return pos;
}



void generacionBolilero (int v[90])  //GENERO LOS NUMEROS DEL BOLILLERO
{

    int numeroNuevo = 0;
    int resultadoBusqueda = 0;

    for (int i=0; i<90; i++)
    {
        do
        {
            numeroNuevo= 1+ rand()%90;
            resultadoBusqueda= BusquedaBinariaBolillas(v, numeroNuevo);
        }
        while (resultadoBusqueda!=-1);
        v[i]=numeroNuevo;
    }
}

void muestroBolilero(int v[90])  //MUESTRO BOLILLERO
{


    for (int i=0; i<90; i++)
    {

        printf(" %d ",v[i]);
    }

}


//-----------FUNCIONES DE LOS CARTONES-------------------

void armadoDeCartones(jugadorPtr j[2])
{

    printf("\nYa elegido la cantidad de cartones tenes que comprar los cartones.\n1 ---> comprar un CARTON PERSONALIZADO\n2 ---> comprar un CARTON ALEATORIO.\n");
    int option = 0;
    do
    {

        scanf("%d",&option);


        // ZONA DE CARGA Y MUESTRA DE CARTONES
        switch (option)
        {

        // CASO 1 carton PERSONALIZADO JUGADOR
        case 1:
            cargarCartonPersonalizado(j[0],getCantidadDeCartones(j[0]));
            printf("\n-----CARTONES CARGADOS DEL JUGADOR----\n");
            mostrarCarton(j[0]);

            //carton PC
            crearCartonAleatorio(j[1], getCantidadDeCartones(j[1]));
            printf("\n-----CARTONES CARGADOS DE LA PC------\n");
            mostrarCarton(j[1]);
            break;


        case 2:  // CASO 2 carton ALEATORIO JUGADOR
            system("cls");
            crearCartonAleatorio(j[0],getCantidadDeCartones(j[0]));
            printf("\n-----CARTONES CARGADOS DEL JUGADOR----\n");
            mostrarCarton(j[0]);

            //carton  PC
            crearCartonAleatorio(j[1],getCantidadDeCartones(j[1]));
            printf("\n-----CARTONES CARGADOS DE LA PC------\n");
            mostrarCarton(j[1]);
            break;
        }
        option =0;

    }
    while(option != 0);

}



void crearCartonAleatorio(jugadorPtr j, int cantidadCartones)   //CARGO CARTON ALEATORIO
{
    int numeroNuevo = 0;
    int resultadoBusqueda= 0 ;

    for (int p=0; p<cantidadCartones ; p++)
    {
        for (int b=0; b<3; b++)
        {
            for (int k=0; k<5; k++)
            {

                do
                {
                    numeroNuevo =1 + rand()%90;
                    resultadoBusqueda = busquedaDeRepetidos(j,cantidadCartones,numeroNuevo);
                }
                while(resultadoBusqueda != -1);

                setNumeroCarton(j, p,b,k, numeroNuevo);
            }
        }
    }
}


void mostrarAvanceCarton(jugadorPtr jugador, int vBolillasSalidas[90], char cartonDeQuien[15])  //MUESTRO CARTON
{

    int cantidadDeCartones = getCantidadDeCartones(jugador);

    if(strcmp(getNombre(jugador), "PC") == 0){

        printf("\nCARTONES PC\n");
    }else{
        printf("\nCARTONES JUGADOR\n");
    }
    printf("-------------------\n");
    for (int p=0; p<cantidadDeCartones; p++)
    {

        for(int i =0; i<FILAS; i++)
        {

            for(int j=0; j<COLUMNAS; j++)
            {

                if(getNumeroCarton(jugador, p,i,j) != -1)
                {

                    if (getNumeroCarton(jugador, p, i, j)<=9)   //Si es un numero de una cifra (del 1 al 9) hago que me escriba un espacio vacio asi quedan los numeros alineados.
                    {
                        printf(" %d  ",getNumeroCarton(jugador, p, i, j));
                    }
                    else printf(" %d ",getNumeroCarton(jugador, p, i, j));
                }
                else
                {

                    printf(" -  ");


                }
            }

            printf("\n");
        }
        printf("-------------------\n");
    }
    printf("Numeros que saco el %s: \n", cartonDeQuien);
    for(int w = 0; w<90; w++)
    {
        if(vBolillasSalidas[w] != -1)
        {
            printf("%d ", vBolillasSalidas[w]);

        }

    }
    if(getSacoBingo(jugador) == 0){
        printf("\nBINGO: NO\n");
    }else{
        printf("\nBINGO: SI\n");
    }
    if(getSacoLinea(jugador) == 0){
        printf("LINEA: NO\n");
    }else{
        printf("LINEA: SI\n");
    }
    if(getSacoColumna(jugador) == 0){
        printf("COLUMNA: NO\n");
    }else{
        printf("COLUMNA: SI\n");
    }

    printf("\n");
}


void mostrarCarton(jugadorPtr jugador)  //MUESTRO CARTON
{

    int cantidadDeCartones = getCantidadDeCartones(jugador);

    printf("------------------------------------------------\n");
    for (int p=0; p<cantidadDeCartones; p++)
    {

        for(int i =0; i<FILAS; i++)
        {

            for(int j=0; j<COLUMNAS; j++)
            {

                if (getNumeroCarton(jugador, p, i, j)<=9)   //Si es un numero de una cifra (del 1 al 9) hago que me escriba un espacio vacio asi quedan los numeros alineados.
                {
                    printf(" %d  ",getNumeroCarton(jugador, p, i, j));
                }
                else printf(" %d ",getNumeroCarton(jugador, p, i, j));
            }

            printf("\n");
        }

        printf("------------------------------------------------\n");
    }
}




void cargarCartonPersonalizado(jugadorPtr jugador, int cantidadDeCartones)  //CARGO CARTON PERSONALIZADO
{


    int resultadoBusqueda=0;
    int numero_nuevo=0;
    int p,i,j;
    for ( p=0; p<cantidadDeCartones; p++) //lleno la matriz en  0 para sacar la basura.
    {
        for( i=0; i<3; i++)
        {
            for( j=0; j<5; j++)
                setNumeroCarton(jugador, p, i,j, 0);
        }
    }

    for ( p=0; p<cantidadDeCartones; p++)    //Usuario carga manualmente
    {



        for( i =0; i<3; i++)
        {

            for( j=0; j<5; j++)
            {


                do
                {

                    printf("\nUsted esta llenando el CARTON %d",p+1);
                    printf("\nEn la fila %d, columna %d\n",i, j);
                    printf("Ingrese su numero del 1 al 90: ");
                    printf("\n");
                    scanf("%d",&numero_nuevo);
                    //consigo un numero

                    while(numero_nuevo < 1 || numero_nuevo > 90)   //Si ese numero es menor a 0 o mayor a 90 lo pido de vuelta.
                    {
                        printf("\nTiene que ingresar un numero del 1 al 90...Intente nuevamente\n");
                        scanf("%d",&numero_nuevo);
                    }

                    resultadoBusqueda = busquedaDeRepetidos(jugador,cantidadDeCartones,numero_nuevo); //busco si se repite.

                    if (resultadoBusqueda != -1)
                    {
                        printf("\n!!! NUMERO REPETIDO!!! Ingrese un numero que no haya ingresado anteriormente:\n");
                    }
                }
                while (resultadoBusqueda != -1);   //Sale del bucle cuando no lo encuentra osea cuando es -1

                setNumeroCarton(jugador, p, i, j, numero_nuevo);
                system("cls");
                mostrarCarton(jugador);

            }
        }
    }
}


//-----------     FUNCION DE BUSCAR REPETIDOS     ----------------

int busquedaDeRepetidos(jugadorPtr jugador,int t, int buscar)
{

    int pos=-1;

    for(int p=0; p<t ; p++)
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<5; j++)
            {
                if (getNumeroCarton(jugador, p, i, j) == buscar)
                {
                    pos = getNumeroCarton(jugador, p, i, j);
                }
            }
        }
    }
    return pos;

}

void buscarNumeroEnCartonYsetear(jugadorPtr jugador, int numeroABuscar)
{
    int t = getCantidadDeCartones(jugador);

    for(int p=0; p<t ; p++)
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<5; j++)
            {
                if (getNumeroCarton(jugador, p, i, j) == numeroABuscar)
                {
                    setNumeroCarton(jugador, p,i,j,-1);
                }
            }
        }
    }

}


//-----------     FUNCIONES PARA VERIFICAR CONDICIONES DE VICTORIA     ----------------
// VERIFICAR LINEA COLUMNA Y BINGO
void verificarLinea(jugadorPtr jugador, int bolillasYaSalidas[90])
{
    int chances = 0;

    for(int p=0; p<getCantidadDeCartones(jugador) ; p++)
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<5; j++)
            {
                if(getNumeroCarton(jugador, p, i,j) == -1)
                {
                    chances++;
                }

                if(chances == 5)
                {
                    setSacoLinea(jugador, 1);
                }
            }

            chances = 0;
        }
    }
}

void verificaColumna(jugadorPtr jugador, int bolillasYaSalidas[90])
{
    int chances = 0;

    for(int p=0; p<getCantidadDeCartones(jugador) ; p++)
    {
        for (int i=0; i<5; i++)
        {
            for (int j=0; j<3; j++)
            {

                if(getNumeroCarton(jugador, p, j,i) == -1)
                {
                    chances++;
                }

                if(chances == 3)
                {
                    setSacoColumna(jugador, 1);

                }

            }
            chances = 0;

        }
    }

}


void cantarBingo(jugadorPtr jugador)
{

    int cont=0;

    for(int p=0; p<getCantidadDeCartones(jugador) ; p++)
    {

        for (int i=0; i<3; i++)
        {

            for (int j=0; j<5; j++)
            {
                if(getNumeroCarton(jugador, p, i, j)==-1)
                    cont++;
            }

        }
        if(cont==15)
        {

            printf(" \nBINGO VERIFICADO!!! SUMASTE 70 PUNTOS!!!\n");
            setSacoBingo(jugador, 1);

        }

        cont=0;
    }

}


void calcularPuntajeFinal(jugadorPtr j, int c)
{
    float multiplicador;
    float puntajeFinal = 0.0f;

    if (c<30)
    {
        multiplicador = 2;
    }
    if (c<50 && c>30 )
    {
        multiplicador = 1.7;
    }
    if (c<70 && c>50)
    {
        multiplicador = 1.5;
    }
    if(c > 70)
    {
        multiplicador = 1;

    }

    if(getSacoColumna(j) == 1)
    {
        puntajeFinal = puntajeFinal + 10;
    }
    if(getSacoLinea(j) == 1)
    {
        puntajeFinal = puntajeFinal + 20;
    }
    if(getSacoBingo(j) == 1)
    {
        puntajeFinal = puntajeFinal + 70;
    }

    puntajeFinal = puntajeFinal * multiplicador;
    setPuntos(j, puntajeFinal);
}

//  -------------------------    ARCHIVOS      -------------------------
void ganadorARanking(jugadorPtr j[2], rankingPtr ranking[10])
{
    for(int w = 0; w<2; w++)
    {
        int posLibre = getPosicionLibre(ranking);
        setPuntosRanking(ranking[posLibre], getPuntos(j[w]));
        setNombreRanking(ranking[posLibre], getNombre(j[w]));


    }

}

void txtAStruct(rankingPtr ranking[10])
{

    FILE *fptr = fopen("Ranking.txt", "a+");

    int vUbicacional;
    char puntos[100] = " ";

    char vectortxt[80] = " ";
    int contadorInterno = 0;
    char nombreJugador[100] = " ";


    while(!feof(fptr))
    {
        //EXTRACCION DE SEPARADORES
        strcpy(vectortxt, " ");

        fgets(vectortxt,80, fptr);
        for(int i =0; i<80; i++)
        {
            if(vectortxt[i] == ';')
            {
                vUbicacional = i;
            }

        }

        strcpy(puntos, " ");
        for(int i = 0; i<vUbicacional; i++)
        {
            puntos[i] = vectortxt[i];
        }
        strcpy(nombreJugador, " ");
        for(int i = vUbicacional + 1; i<80; i++)
        {
            nombreJugador[i - 1-vUbicacional] = vectortxt[i];

        }

        float puntosFinal = atof(puntos);

        //VARIABLES A STRUCT
        setPuntosRanking(ranking[contadorInterno], puntosFinal);
        setNombreRanking(ranking[contadorInterno], nombreJugador);
        contadorInterno++;
    }



    //CIERRE DE ARCHIVO
    fclose(fptr);
}


void structATxt(rankingPtr ranking[10])
{

    FILE*PunteroRanking;
    PunteroRanking=fopen("Ranking.txt","w");
    for(int i =0; i<10; i++)
    {



        fprintf(PunteroRanking, "%.2f;%s",getPuntosRanking(ranking[i]),getNombreRanking(ranking[i]));
    }
    fclose(PunteroRanking);


}




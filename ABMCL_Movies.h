#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idPelicula;
    char nombrePelicula[30];
    char director[20];
    char genero[20];
    char pais[20];
    int anio;
    int valoracion;
    int pm;      // (0: si es ATP / 13: mayor de trece /16: mayor de 16 / 18: mayor de 18
    int eliminado;   // indica 1 o 0 si la película fue eliminada
} stPelicula;


stPelicula cargaPelicula(int id);
int creaArchivoPeliculas(char archivoPeliculas[]);
int consultaExistenciaArchivo(char archivoPeliculas[]);
void cargaArchivoPeliculas(char archivoPeliculas[]);
int devuelveUltimoID(char archivoPeliculas[]);
int consultaExistenciaPelicula(char archivoPeliculas[], char nombre[]);



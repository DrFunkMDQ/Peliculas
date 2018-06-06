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
    int eliminado;   // indica 1 o 0 si la pel�cula fue eliminada
} stPelicula;

///FUNCIONES UTILES PARA CUALQUIER OPERACI�N
int creaArchivoPeliculas(char archivoPeliculas[]);///Crea el archivo. Retorna 1 si se cre� con �xito, 0 si fall�.
int consultaExistenciaArchivo(char archivoPeliculas[]);///Consulta si el archivo est� creado. Retorna 1 existe, 0 si no existe.
int devuelveUltimoID(char archivoPeliculas[]);///Retorna el ID de la �ltima pel�cula agregada.
int consultaExistenciaPelicula(char archivoPeliculas[], char nombre[]);///Si la pel�cula existe, retorna la posici�n. Si no existe, retorna 0.

///FUNCIONES DE ALTA
stPelicula cargaPelicula(int id);///Retorna una variable tipo stPelicula cargada. Es necesario enviar el ID correspondiente.
void cargaArchivoPeliculas(char archivoPeliculas[]);///Carga el archivo de pel�culas mediante la intervenci�n del usuario.

///FUNCIONES DE BAJA
void bajaPelicula(char archivoPeliculas[]);


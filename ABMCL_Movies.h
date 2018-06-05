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

///FUNCIONES UTILES PARA CUALQUIER OPERACIÓN
int creaArchivoPeliculas(char archivoPeliculas[]);///Crea el archivo. Retorna 1 si se creó con éxito, 0 si falló.
int consultaExistenciaArchivo(char archivoPeliculas[]);///Consulta si el archivo está creado. Retorna 1 existe, 0 si no existe.
int devuelveUltimoID(char archivoPeliculas[]);///Retorna el ID de la última película agregada.
int consultaExistenciaPelicula(char archivoPeliculas[], char nombre[]);///Si la película existe, retorna la posición. Si no existe, retorna 0.

///FUNCIONES DE ALTA
stPelicula cargaPelicula(int id);///Retorna una variable tipo stPelicula cargada. Es necesario enviar el ID correspondiente.
void cargaArchivoPeliculas(char archivoPeliculas[]);///Carga el archivo de películas mediante la intervención del usuario.

///FUNCIONES DE BAJA
void bajaPelicula(char archivoPeliculas[]);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "ABMCL_Movies.h"

int creaArchivoPeliculas(char archivoPeliculas[])
{
    int validacion;
    FILE *peliculas;
    peliculas=fopen(archivoPeliculas, "rb");
    if(peliculas==NULL)
    {
        peliculas=fopen(archivoPeliculas, "wb");
    }
    if (peliculas!=NULL)
        validacion=1;
    else
        validacion=0;
    fclose(peliculas);
    return validacion;
}

int consultaExistenciaArchivo(char archivoPeliculas[])
{
    int valor;
    FILE *peliculas;
    peliculas=fopen(archivoPeliculas, "ab");
    if(peliculas!=NULL)
        valor=1;
    else
        valor=0;
    fclose(peliculas);
    return valor;
}


void cargaArchivoPeliculas(char archivoPeliculas[])
{
    int validacion, id, existe, cant, i;
    char c='s';
    stPelicula nuevaPelicula;
    FILE *peliculas;
    validacion=consultaExistenciaArchivo(archivoPeliculas);
    if(validacion==0)
        creaArchivoPeliculas(archivoPeliculas);
    peliculas=fopen(archivoPeliculas, "ab");
    if(peliculas!=NULL)
    {
        while(c=='s')
        {
            printf("Ingrese la cantidad de peliculas a cargar\n");
            scanf("%d", &cant);
            for(i=0; i<cant; i++)
            {
                id=devuelveUltimoID(archivoPeliculas);
                nuevaPelicula=cargaPelicula(id);
                existe=consultaExistenciaPelicula(archivoPeliculas, nuevaPelicula.nombrePelicula);
                if(existe==0)
                    fwrite(&nuevaPelicula, sizeof(stPelicula), 1, peliculas);
                else
                    printf("La pelicula ya existe dentro del listado\n");
            }
        }
        fclose(peliculas);
    }
    else
    {
        printf("El archivo no se abrió correctamente.\n");
    }
}

int devuelveUltimoID(char archivoPeliculas[])
{
    FILE *peliculas;
    stPelicula aux;
    int id;
    peliculas=fopen(archivoPeliculas, "rb");
    fseek(peliculas, 0, SEEK_END);
    fseek(peliculas, (-1*sizeof(stPelicula)), SEEK_CUR);
    if (ftell(peliculas)==0)
    {
        id=1;
    }
    else
    {
        fread(&aux, sizeof(stPelicula),1,peliculas);
        id=aux.idPelicula;
    }
    return id;
}

int consultaExistenciaPelicula(char archivoPeliculas[], char nombre[])
{
    FILE *peliculas;
    stPelicula aux;
    int existe;
    peliculas=fopen(archivoPeliculas, "rb");
    while(!feof(peliculas) && (strcmpi(nombre, aux.nombrePelicula)!=0))
    {
        fread(&aux, sizeof(stPelicula),1, peliculas);
    }
    if(strcmpi(nombre, aux.nombrePelicula)!=0)
        existe=0;
    else
        existe=1;
    fclose(peliculas);
    return existe;
}


stPelicula cargaPelicula(int id)
{
    stPelicula peliculaVacia;
    peliculaVacia.idPelicula=id;
    printf("Ingrese el nombre:\n");
    fflush(stdin);
    gets(peliculaVacia.nombrePelicula);
    printf("Ingrese el director:\n");
    fflush(stdin);
    gets(peliculaVacia.director);
    printf("Ingrese el genero:\n");
    fflush(stdin);
    gets(peliculaVacia.genero);
    printf("Ingrese el pais de origen:\n");
    fflush(stdin);
    gets(peliculaVacia.pais);
    printf("Ingrese el anio:\n");
    scanf("%d",&peliculaVacia.anio);
    printf("Ingrese la valoracion:\n");
    scanf("%d",&peliculaVacia.valoracion);
    printf("Apta para mayores de:\n");
    scanf("%d",&peliculaVacia.pm);
    printf("¿Esta disponible?:\n");
    scanf("%d",&peliculaVacia.eliminado);
    return peliculaVacia;
}

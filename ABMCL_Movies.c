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
        existe=ftell(peliculas)/sizeof(stPelicula);
    fclose(peliculas);
    return existe;
}

int devuelveUltimoID(char archivoPeliculas[])
{
    FILE *peliculas;
    stPelicula aux;
    int id;
    peliculas=fopen(archivoPeliculas, "rb");
    fseek(peliculas, 0, SEEK_END);

    if (ftell(peliculas)==0)
    {
        id=1;
    }
    else
    {
        fseek(peliculas, -1*sizeof(stPelicula), SEEK_END);
        fread(&aux, sizeof(stPelicula),1,peliculas);
        id=(aux.idPelicula)+1;
    }
    return id;
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
            id=devuelveUltimoID(archivoPeliculas);
            for(i=0; i<cant; i++)
            {
                nuevaPelicula=cargaPelicula(id);
                existe=consultaExistenciaPelicula(archivoPeliculas, nuevaPelicula.nombrePelicula);
                if(existe==0)
                    fwrite(&nuevaPelicula, sizeof(stPelicula), 1, peliculas);
                else
                    printf("La pelicula ya existe dentro del listado\n");
                id++;
            }
            printf("Desea cargar mas peliculas? s/n \n");
            fflush(stdin);
            scanf("%c", &c);
        }
        fclose(peliculas);
    }
    else
    {
        printf("El archivo no se abrió correctamente.\n");
    }
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
    printf("Ingrese la valoracion (de 1 a 5):\n");
    scanf("%d",&peliculaVacia.valoracion);
    while((peliculaVacia.valoracion<1) & (peliculaVacia.valoracion>5))
    {
        printf("Valoración incorrecta. Solo valores enteros entre 1 y 5\n");
        scanf("%d",&peliculaVacia.valoracion);
    }
    printf("Apta para mayores de:\n");
    scanf("%d",&peliculaVacia.pm);
    while((peliculaVacia.pm !=0) & (peliculaVacia.pm !=13) & (peliculaVacia.pm !=16) & (peliculaVacia.pm !=18))
    {
        printf("Calificación incorrecta, vuelva a ingresar (0, 13, 16 o 18)\n");
        scanf("%d",&peliculaVacia.pm);
    }
    printf("¿Esta disponible?:\n");
    scanf("%d",&peliculaVacia.eliminado);
    while((peliculaVacia.eliminado !=1) & (peliculaVacia.eliminado !=0))
    {
        printf("Error. Está Disponible? 1/0\n");
        scanf("%d",&peliculaVacia.eliminado);
    }
    return peliculaVacia;
}

void bajaPelicula(char archivoPeliculas[])
{
    FILE *peliculas;
    stPelicula PeliculaAEliminar;
    char peliculaBuscada[30];
    long posicion, a;

    printf("Ingrese la película buscada\n");
    fflush(stdin);
    gets(peliculaBuscada);
    posicion=consultaExistenciaPelicula(archivoPeliculas, peliculaBuscada);
    posicion--;///PARA POSICIONARME EN EL BLOQUE, YA QUE DEL OTRO MODO ESTOY AL FINAL DEL MISMO Y LEE EL SIGUIENTE
    if(posicion!=0)
    {
        peliculas=fopen(archivoPeliculas, "r+b");
        fseek(peliculas, (posicion*sizeof(stPelicula)), SEEK_SET);
        fread(&PeliculaAEliminar, sizeof(stPelicula), 1, peliculas);
        PeliculaAEliminar.eliminado=1;
        //fwrite(&PeliculaAEliminar, sizeof(stPelicula), 1, archivoPeliculas);
    }
    else
    {
        printf("La película no existe dentro del listado\n");
    }
    fclose(peliculas);
}

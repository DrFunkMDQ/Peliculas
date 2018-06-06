#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABMCL_Movies.h"

const char archivoPeliculas[30]={"movies.dat"};

int main()
{
    stPelicula peliculita;
    int posicion;
    FILE *peliculas;

    cargaArchivoPeliculas(archivoPeliculas);
    peliculas=fopen(archivoPeliculas, "rb");
    while(!feof(peliculas))
    {
        fread(&peliculita, sizeof(stPelicula), 1 , peliculas);
        if(!feof(peliculas))
            printf("%d\n %s\n %s\n %s\n %s\n %d\n %d\n %d\n %d\n", peliculita.idPelicula, peliculita.nombrePelicula, peliculita.director, peliculita.genero, peliculita.pais, peliculita.anio, peliculita.valoracion, peliculita.pm, peliculita.eliminado);
    }
    posicion=consultaExistenciaPelicula(archivoPeliculas, "yy");
    printf("\n%d", posicion);
    bajaPelicula(archivoPeliculas);
    /*int n, j;
    FILE *nums;
    nums=fopen("numeros.dat", "ab");
    scanf("%d", &n);
    fwrite(&n, sizeof(int), 1, nums);
    scanf("%d", &n);
    fwrite(&n, sizeof(int), 1, nums);
    scanf("%d", &n);
    fwrite(&n, sizeof(int), 1, nums);
    scanf("%d", &n);
    fwrite(&n, sizeof(int), 1, nums);
    fclose(nums);
    nums=fopen("numeros.dat","rb");
    fseek(nums, 0, SEEK_END);
    fread(&j, sizeof(int), 1, nums);
    printf("//////%d\n", j);
    fseek(nums, -1*sizeof(int), SEEK_END);
    fread(&j, sizeof(int), 1, nums);
    printf("//////%d\n", j);
    fclose(nums);*/


    return 0;
}



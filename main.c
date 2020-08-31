#include <stdio.h>
#include <stdlib.h>
#include "normalizar.h"

#define ARG_ARCH_ENT 1
#define ARG_ARCH_SAL 2

#define TAM_LINEA 501

#define ERROR_ARCH 1

///Clase_2020-05-15_normalizar ANormalizar.txt Normalizado.txt

int main(int argc, char* argv[])
{
/*  FILE* cadenaOrigen = fopen(argv[ARG_ARCH_ENT], "rt");

    if(!cadenaOrigen)
    {
        puts("Error abriendo archivo.");
        return ERROR_ARCH;
    }

    FILE* cadenaDestino = fopen(argv[ARG_ARCH_SAL], "wt");

    if(!cadenaDestino)
    {
        puts("Error abriendo archivo.");
        return ERROR_ARCH;
    }

    char linea[TAM_LINEA];
    char lineaNorm[TAM_LINEA];

    while(fgets(linea, TAM_LINEA, cadenaOrigen))
    {
        normalizar(linea, lineaNorm);
        fputs(lineaNorm, cadenaDestino);
        fputc('\n', cadenaDestino);
    }

    fclose(cadenaOrigen);
    fclose(cadenaDestino);
*/

/*    char cad1[]= {"hoLa %$%&(        *&/'qUe*-++*&* TaL$#^\n#$   ComO %$%#&(         *&/TE*-++-*&*  vA"}, cad2[TAM_LINEA];

    puts("Que texto quiere escribir");
    puts(cad1);
    normalizar(cad1,cad2);
    puts(cad2);
*/

    char cad3[]= {"$%#&CesPEDes  %)%(/$TOmaS&&$niCOlaS"};
    char cad5[TAM_LINEA];

    printf("La cadena a normalizar es: %s\n", cad3);
    normalizarApyn(cad3, cad5, ',', 1);
    printf("Cadena normalizada: %s\n", cad5);

    system("pause");

    return 0;

}

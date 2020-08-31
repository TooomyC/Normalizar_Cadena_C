#include <stdio.h>
#include <string.h>
#include "normalizar.h"

#define TODO_OK 0
#define ERROR_TAM_BUF 1

#define TAM_LINEA 501

#define FALSO 0
#define VERDADERO 1


char* normalizar(const char* cadenaOrigen, char* cadenaDestino)
{
    SecuenciaPal secOrig, secDest;

    crearSecuencia(&secOrig, (char*)cadenaOrigen, ",");
    crearSecuencia(&secDest, cadenaDestino, ",");

    Palabra palabra, palabraDest;

    leerPalabra(&secOrig, &palabra);
    while(!finSecuencia(&secOrig))
    {
        escribirPalabra(&secDest, &palabra, &palabraDest);
        formatearPalabra(&palabraDest);
        escribirCaracter(&secDest, ' ');
        leerPalabra(&secOrig, &palabra);
    }

    reposicionarCursor(&secDest, -1);
    escribirCaracter(&secDest, '\0');

    return cadenaDestino;
}

void crearSecuencia(SecuenciaPal* sec, char* cad, char* car)
{
    sec->cursor = cad;
    sec->finSecuencia = FALSO;
    sec->inicioVec = cad;
    sec->caracterSeparador = car;
    //sec->contPal = 0;
    sec->cvpc = 0;
}

Palabra* leerPalabra(SecuenciaPal* sec, Palabra* palabra) //Lee la palabra hasta no encontrar una letra, devolviendo la posicion anterior donde esta la ultima letra
{
    while(*sec->cursor && !esLetra(*sec->cursor))
        sec->cursor ++;

    if(!*sec->cursor)
    {
        sec->finSecuencia = VERDADERO; //Si encuentra el fin de cadena, retorna nulo
        return NULL;
    }

    palabra->ini = sec->cursor;

    while(*sec->cursor && esLetra(*sec->cursor))
    {
        sec->cursor ++;
        palabra->contCar ++;
    }

    palabra->fin = sec->cursor - 1;
    palabra->numpal++; //Cuenta palabras

    return palabra;
}

Palabra* escribirPalabra(SecuenciaPal* sec, Palabra* palabraOrig, Palabra* palabraDest)
{
    palabraDest->ini = sec->cursor;

    for(char* cursorOrig = palabraOrig->ini; cursorOrig <= palabraOrig->fin; cursorOrig++, sec->cursor ++)
    {
        *sec->cursor = *cursorOrig;
        palabraDest->contCar ++;
    }

    palabraDest->fin = sec->cursor - 1;
    palabraDest->numpal ++;

    return palabraDest;
}

void formatearPalabra(Palabra* palabra) //Convierte a Mayus. y Minus.
{
    *palabra->ini = AMayuscula(*palabra->ini);

    for(char* cursorOrig = palabra->ini + 1; cursorOrig <= palabra->fin; cursorOrig++)
        *cursorOrig = AMinuscula(*cursorOrig);
}

int finSecuencia(const SecuenciaPal* sec)
{
    return sec->finSecuencia;
}

void escribirCaracter(SecuenciaPal* sec, char car)
{
    *sec->cursor = car;
    if((sec->cursor + 1) - (sec->inicioVec) < TAM_LINEA)
        sec->cursor++;
}

int reposicionarCursor(SecuenciaPal* sec, int offset)
{
    if((sec->cursor + 1) - (sec->inicioVec) < TAM_LINEA)
        return ERROR_TAM_BUF;

    sec->cursor += offset;
    return TODO_OK;
}

char AMayuscula (char car)
{
    if(car < 'a' || car > 'z') ///VALIDA CON FUERA DE RANGO
        return car;

    return car - ('a' - 'A');
}

char AMinuscula (char car)
{
    if(car < 'A' || car > 'Z') ///VALIDA DENTRO DEL RANGO
        return car;

    return car + ('a' - 'A');
}

int esLetra (char car)
{
    return (car >= 'a' && car <= 'z') || (car >= 'A' && car <= 'Z');
}

char* normalizarApyn(const char* cadenaOrigen, char* cadenaDestino, char carSeparador, int cantPalPorDefecto)
{
    SecuenciaPal secOrig, secDest;

    crearSecuencia(&secOrig, (char*)cadenaOrigen, &carSeparador);
    crearSecuencia(&secDest, cadenaDestino, &carSeparador);

    Palabra palabraOrig, palabraDest;

    crearPalabra(&palabraOrig);
    crearPalabra(&palabraDest);

    secDest.cvpc = buscarCaracter(&secOrig);

    leerPalabraApyn(&secOrig, &palabraOrig);
    while(!finSecuencia(&secOrig))
    {
        escribirPalabraApyn(&secDest, &palabraOrig, &palabraDest);
        secDest.cvpc == 0? formatearPalApynPalabra(&palabraDest, cantPalPorDefecto, &secDest) : formatearPalApynCaracteres(&palabraDest, secDest.cvpc, &secDest);
        escribirCaracter(&secDest, ' ');
        leerPalabraApyn(&secOrig, &palabraOrig);
    }

   reposicionarCursor(&secDest, -1);
   escribirCaracter(&secDest, '\0');

    return cadenaDestino;
}

void crearPalabra(Palabra* palabra)
{
    palabra->contCar = 0;
    palabra->numpal = 0;
}

int buscarCaracter(SecuenciaPal* secOrig)
{
    int cont = 0;

    while(!finSecuencia(secOrig))
        cont += cantCar(secOrig);

    if(!*secOrig->cursor)
        cont = 0;

    //Reseteo la secuencia
    secOrig->cursor = secOrig->inicioVec;
    secOrig->finSecuencia = FALSO;

    return cont;
}

int cantCar(SecuenciaPal* sec) //Cantidad de caracteres validos
{
    int cont = 0;

    while(!esLetra(*sec->cursor) && *sec->cursor != *sec->caracterSeparador && *sec->cursor)
        sec->cursor ++;

    if(*sec->cursor == *sec->caracterSeparador)
    {
        sec->finSecuencia = VERDADERO; //A moodo de corte del While
        return cont;
    }

    while(esLetra(*sec->cursor) && *sec->cursor)
    {
        sec->cursor ++;
        cont ++;
    }

    if(!*sec->cursor) //Valor nulo
        sec->finSecuencia = VERDADERO;

    return cont;
}

Palabra* leerPalabraApyn(SecuenciaPal* sec, Palabra* palabra) //Contar cantidad de caracteres
{
     while(*sec->cursor && !esLetra(*sec->cursor))
        sec->cursor ++;

    if(!*sec->cursor)
    {
        sec->finSecuencia = VERDADERO; //Si encuentra el fin de cadena, retorna nulo
        return NULL;
    }

    palabra->ini = sec->cursor;

    while(*sec->cursor && esLetra(*sec->cursor))
    {
        sec->cursor ++;
        palabra->contCar ++; //Incrementa cuando hay letra/caracter valido
    }

    palabra->fin = sec->cursor - 1;
    palabra->numpal++; //Cuenta palabras

    return palabra;
}

Palabra* escribirPalabraApyn(SecuenciaPal* sec, Palabra* palabraOrig, Palabra* palabraDest)
{
   palabraDest->ini = sec->cursor;

    for(char* cursorOrig = palabraOrig->ini; cursorOrig <= palabraOrig->fin; cursorOrig++, sec->cursor ++)
    {
        *sec->cursor = *cursorOrig;
        palabraDest->contCar ++;
    }

    palabraDest->fin = sec->cursor - 1;
    palabraDest->numpal ++;

    return palabraDest;
}

void formatearPalApynCaracteres(Palabra* palabra, int numCar, SecuenciaPal* sec)
{
    if(numCar >= palabra->contCar) ///INDICA EL APELLIDO
    {
        char* cursorOrig;

        for(cursorOrig = palabra->ini; cursorOrig <= palabra->fin; cursorOrig++)
            *cursorOrig = AMayuscula(*cursorOrig);

        if (numCar == palabra->contCar)
        {
            *cursorOrig = *sec->caracterSeparador;
            sec->cursor++;
        }

    }
    else ///INDICA EL NOMBRE
    {
        *palabra->ini = AMayuscula(*palabra->ini);

        for(char* cursorOrig = palabra->ini + 1; cursorOrig <= palabra->fin; cursorOrig++)
            *cursorOrig = AMinuscula(*cursorOrig);
    }
}

void formatearPalApynPalabra(Palabra* palabra, int cantPal, SecuenciaPal* sec)
{
    char* cursorOrig;

    if(cantPal >= palabra->numpal) ///INDICA EL APELLIDO
    {
        for(cursorOrig = palabra->ini; cursorOrig <= palabra->fin; cursorOrig++)
            *cursorOrig = AMayuscula(*cursorOrig);

        if (cantPal == palabra->numpal)
        {
            *cursorOrig = *sec->caracterSeparador;
            sec->cursor++;
        }
    }

    else ///INDICA EL NOMBRE
    {
        *palabra->ini = AMayuscula(*palabra->ini);

        for(cursorOrig = palabra->ini + 1; cursorOrig <= palabra->fin; cursorOrig++)
            *cursorOrig = AMinuscula(*cursorOrig);
    }
}

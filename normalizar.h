#ifndef NORMALIZAR_H_INCLUDED
#define NORMALIZAR_H_INCLUDED

typedef struct
{
    char* cursor;
    int finSecuencia;
    char* inicioVec;
    int cvpc; //Cantidad de caracteres validos previos al caracter separador
    char* caracterSeparador;

}SecuenciaPal;

typedef struct
{
    char* ini;
    char* fin;
    int contCar; //Contador de caracteres
    int numpal; //Contador de palabras

}Palabra;


char* normalizar (const char* cadenaOrigen, char* cadenaDestino);

Palabra* escribirPalabra(SecuenciaPal* sec, Palabra* palabra, Palabra* palabraDest);
Palabra* leerPalabra(SecuenciaPal* sec, Palabra* palabra);
void crearSecuencia(SecuenciaPal* sec, char* cad, char* car);
void formatearPalabra(Palabra* palabra);
void escribirCaracter(SecuenciaPal* sec, char car);
int reposicionarCursor(SecuenciaPal* secDest, int offset);
int finSecuencia(const SecuenciaPal* sec);

Palabra* escribirPalabraApyn(SecuenciaPal* sec, Palabra* palabraOrig, Palabra* palabraDest);
Palabra* leerPalabraApyn(SecuenciaPal* sec, Palabra* palabra);
char* normalizarApyn(const char* cadenaOrigen, char* cadenaDestino, char carSeparador, int cantPalPorDefecto);
void crearPalabra(Palabra* palabra);
void formatearPalApynCaracteres(Palabra* palabra, int numCar, SecuenciaPal* sec);
void formatearPalApynPalabra(Palabra* palabra, int cantPal, SecuenciaPal* sec);
int buscarCaracter(SecuenciaPal* sec);
int cantCar(SecuenciaPal* sec);

int esLetra (char car);
char AMayuscula (char car);
char AMinuscula (char car);

#endif // NORMALIZAR_H_INCLUDED

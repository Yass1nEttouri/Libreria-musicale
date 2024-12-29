#ifndef LIB_MUSIC_H 
#define LIB_MUSIC_H

#include <stdbool.h>

//capacità massima della libreria musicale
#define CAPACITY 100

//definizione tipo di dato personalizzato per il campo durata
typedef float minutes;

//definizione tipo di dato rating per la valutazione di una canzone
typedef unsigned int rating;

//definizione struttura dati per una canzone
typedef struct song canzone;
struct song{
    char titolo[40];
    char autore[40];
    char genere[30];
    rating valutazione;
    minutes durata;
};

canzone* add_new_song(canzone* libreria,unsigned int* size); // OK
canzone *delete_song(canzone* libreria,unsigned int* size, const char *title); // fix logica
canzone* rate_song(canzone* libreria, unsigned int size, const char *title); // OK
bool import_library(canzone* libreria, unsigned int* size, const char* file_name); // fix logica
bool export_library(canzone* libreria, unsigned int size,const char* file_name);
void print_songs(canzone* libreria, unsigned int size); //OK
int find_song(canzone* libreria, unsigned int size, const char *title); // OK
void trim(char* str); // understand more
void intro(); // OK

//funzione per applicare un filtro alla visualizzazione della libreria
//filtro per: titolo,autore,genere,valutazione(crescente-decrescente)

#endif

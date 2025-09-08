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
    bool (*ptr_check_favorite)(char*); // make it work
    rating valutazione;
    minutes durata;
};

//to do
//add a list to contain favorite songs
// data structure : linked list? queue?

/* 
Comments about functions implemented

libreria : array of songs representing a library
size: size of array starting from 0
 */

/* 
func used to add a new song to the library 
size : current size of libreria + 1 -> index of the next song which needs to be added
 */
canzone* add_new_song(canzone* libreria,unsigned int* size); // OK

canzone* delete_song(canzone* libreria,unsigned int* size, const char *title); // OK

/* 
func used to rate a specific song in libreria given the title of the song
title: title of the song to add a rating on
 */
canzone* rate_song(canzone* libreria, unsigned int size, const char *title); // OK

bool import_library(canzone* libreria, unsigned int* size, const char* file_name); // OK
bool export_library(canzone* libreria, unsigned int size,const char* file_name); // OK

/* 
simple func to print the array of songs in addition of the rating
 */
void print_songs(canzone* libreria, unsigned int size); //OK

/* 
func to print a good looking rating using stars
rate: the actual rate of a song,a number between 1 and 5
 */
void print_rate(unsigned int rate); // OK

int find_song(canzone* libreria, unsigned int size, const char *title); // OK

/* 
func trim used to clean a string from useless spaces
str : input string
 */
void trim(char* str);

/* 
intro func to help the user to use this library
 */
void intro(); // OK

//to do
//funzione per applicare un filtro alla visualizzazione della libreria
//filtro per: titolo,autore,genere,valutazione(crescente-decrescente)

//implementazione di una funzione per ordinare la libreria in base a un criterio scelto dall'utente indipendentemente dal tipo del parametro passaato alla funzione
//criteri: titolo,autore,genere,valutazione,durata
void sort_library(canzone* libreria, unsigned int size, int criterio, char* asc_desc);

/* 
Comments about list of favorite songs
.....
 */

#endif

#ifndef LIB_MUSIC_H 
#define LIB_MUSIC_H

#include <stdbool.h>

//maximum capacity of a file pathname
#define PATH_MAX 200

//maximum number of characters in a line
#define LINE_MAX 400

//maximum capacity of the music library
#define CAPACITY 100

//definition of a custom data type for the duration field
typedef float minutes;

//definition of the rating data type for evaluating a song
typedef unsigned int rating;

//definition of the data structure for a song
typedef struct song canzone;
struct song{
    char titolo[40];
    char autore[40];
    char genere[20];
    rating valutazione;
    minutes durata;
};


/* 
Comments about functions implemented

libreria : array of songs representing a library
size: size of array starting from 0
 */

void intro();

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

/* 
Functions used to import and export a list of songs from a txt file
*/
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


//Implementation of a function to sort the library based on a criterion chosen by the user.
// Criteria: title, author, genre, rating, duration
void sort_library(canzone* libreria, unsigned int size, int criterio, char* asc_desc);

/*
func to edit song information given song index and field number
*/
bool edit_song_info(canzone* libreria, unsigned int songIndex, unsigned int field);



#endif

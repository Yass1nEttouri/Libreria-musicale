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

//todo:
//aggiungere le playlist


/* 
Comments about functions implemented

libreria : array of songs representing a library
size: size of array starting from 0
 */

void intro();

const char* get_song_name(canzone* libreria, unsigned int index);

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

/* Here are some useful expansions for your music library project:

1. **Playlist Management**
    - Create playlists containing multiple songs
    - Add/remove songs from playlists
    - Export/import playlists

2. **Search & Filter Features**
    - Search songs by artist, genre, or year
    - Filter by rating range or duration
    - Full-text search in song metadata

3. **Statistics & Analytics**
    - Total library duration
    - Average rating per genre
    - Most/least rated songs
    - Genre distribution

4. **Enhanced Data**
    - Add release year, album name
    - Track play count
    - Add favorite/bookmark functionality
    - User-defined tags or categories

5. **User Management**
    - Multiple user profiles with separate libraries
    - Personalized ratings and favorites
    - Export user preferences

6. **Sorting & Organization**
    - By multiple criteria simultaneously
    - Grouped by genre/artist
    - Recently added/modified

7. **Data Persistence**
    - Database integration (SQLite)
    - Automatic backup functionality
    - Configuration file for app settings

8. **Recommendations**
    - Suggest similar songs by genre/artist
    - Top-rated recommendations

I'd recommend starting with **search/filter features** and **statistics** as they add value with moderate complexity, then move to **playlist management** for a more feature-rich experience. */
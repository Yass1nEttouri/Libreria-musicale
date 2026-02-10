#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"
#include "music_library.h"
#include "globals.h"



void intro_playlist(){
    printf("Azioni su Playlist\n");
    printf("10. Visualizza tutte le playlist\n");
    printf("11. Visualizza una playlist\n");
    printf("12. Crea una nuova playlist\n");
    printf("13. Aggiungi una canzone ad una playlist\n");
    printf("14. Elimina una canzone da una playlist\n");
    printf("15. Esci\n");
}

const char* get_song_name(canzone* libreria, unsigned int index) {
    if (libreria == NULL || index >= currentSize) {
        return NULL;
    }

    return libreria[index].titolo;
}

playlistmng* create_playlist_manager(unsigned int capacity){
    playlistmng* m = malloc(sizeof(playlistmng));
    if(!m) return NULL;

    m->playlists = malloc(capacity * sizeof(playlist));
    if(!m->playlists){
        free(m);
        return NULL;
    }
    m->size = 0;

    return m;
}

playlist* create_playlist(const char* playlistName){

    playlist* p = malloc(sizeof(playlist));
    if (p == NULL) return NULL;

    strncpy(p->name, playlistName, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';

    p->capacity = PLAYLIST_CAPACITY;
    p->size = 0;
    p->song_indices = malloc(p->capacity * sizeof(unsigned int));
    if (p->song_indices == NULL) {
        free(p);
        return NULL;
    }

    return p;
}

int add_playlist_to_manager(playlistmng* mng, playlist* p){
    if(!mng || !p) return -1;

    mng->playlists[mng->size] = *p; 
    mng->size++;

    return 1;
}

int delete_playlist(playlistmng* mng, const char* playlistName){
    if(!mng || !playlistName) return 0;

    for(unsigned int i = 0; i < mng->size; i++){
        if(strcmp(mng->playlists[i].name, playlistName) == 0){

            free(mng->playlists[i].song_indices);
            for(unsigned int j = i; j < mng->size - 1; j++){
                mng->playlists[j] = mng->playlists[j + 1];
            }
            mng->size--;

            return 1; 
        }
    }
    return 0; 
}

void print_playlist(playlistmng* mng, const char* playlistName){
    if(!mng || !playlistName){
        printf("\nThere is no Playlist available or Playlist name is not valid!\n");
    }

    for(unsigned int i=0; i<mng->size; i++){
        if(strcmp(mng->playlists[i].name, playlistName) == 0){
            printf("Playlist: %s\n",mng->playlists[i].name);
            printf("Numero canzoni: %d\n",mng->playlists[i].size);
            printf("Elenco canzoni: \n");
            for(unsigned int j = 0; j < mng->playlists[i].size; j++){
                const char *song_name = get_song_name(libreria, mng->playlists[i].song_indices[j]);
                printf("    %d %s",mng->playlists[i].song_indices[j], song_name);
            }
        }
    }
    printf("\nThere is no such a Playlist with that input name!\n");
    return;
}

void show_all_playlists(playlistmng* mng){
    if(!mng){
        printf("There is no Playlists created yet!\n");
        return;
    }
    printf("All Playlists: \n");
    for(unsigned int i=0; i<mng->size; i++){
        printf("    %s\n",mng->playlists[i].name);    
    }
}